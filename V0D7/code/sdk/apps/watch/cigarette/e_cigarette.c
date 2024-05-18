#include "system/includes.h"
#include "e_cigarette.h"
#include "app_task.h"
#include "key_event_deal.h"
#include "asm\mcpwm.h"
#include "ui/ui_api.h"
#include "ui/ui_style.h"

static u16 d_u16SmokingTimerID = 0;

// #define CFG_USER_DEFINE_BEGIN 1
// #define CFG_USER_DEFINE_END   49
#define  CFG_USER_OIL_QUANTITY 1

#define BAT_PERCENT_0   3500//350
#define BAT_PERCENT_100 4100//410

#define USAGE_POWER_100  247500000   

uint16_t d_u16Vbat = 430;
uint32_t d_u32VbatUpdateTimer = 0;

uint32_t d_u32UsedPower = 0x00;
//当前发热丝工作时间
uint32_t d_u32RsUsedTime = 0x00;

bool     d_bMicDetectFlag = FALSE;
uint8_t  d_bRsState = FALSE;
uint8_t  d_u8RealPowerMode    = 2;

static uint32_t d_u32LastSmokingTime = 0;

STRUCT_CIGARETTE_DISPLAY d_strCigaretteDis = {2,0};

void e_cigarette_init(void);
static void e_cigarette_mic_gpio_init(void);
static void ta_tb_pwm_init(void);
static void get_e_cigarette_mic_state(void);
static void ta_set_duty(uint16_t duty);
static void tb_set_duty(uint16_t duty);
static int e_cigarette_key_event_handler(struct sys_event *event);
// void app_e_cigarette_task(void);

void e_cigarette_init(void)
{
    //MIC已经作为中断唤醒引脚在board_devices_init函数中初始化了
    // e_cigarette_mic_gpio_init();
    ta_tb_pwm_init();
}

static void e_cigarette_mic_gpio_init(void)
{
    gpio_set_pull_up(MIC_GPIO,0);
    gpio_set_pull_down(MIC_GPIO,1);
    gpio_set_die(MIC_GPIO,1);
    gpio_set_direction(MIC_GPIO,1);
    delay(100);
}

uint8_t GetOilNum(void)
{
    return d_strCigaretteDis.OilNum;
}

uint16_t GetVbatValue(void)
{
    return d_strCigaretteDis.VbatValue;
}

uint8_t GetVbatPercent(void)
{
    return d_strCigaretteDis.VbatPercent;
}

static void get_e_cigarette_mic_state(void)
{
    static uint8_t l_u8State = 0;
    static uint8_t l_u8Count = 0;

    switch(l_u8State){
        case 0:
            if(gpio_read(MIC_GPIO)){
                d_bMicDetectFlag = true;
                l_u8State = 1;
                l_u8Count = 0;
            }
            else{
                d_bMicDetectFlag = false;
            }
            break;

        case 1:
            d_bMicDetectFlag = true;
            if(!gpio_read(MIC_GPIO)){
                l_u8Count++;
                if(l_u8Count >=3 ){
                    d_bMicDetectFlag = false;
                    l_u8Count = 0;
                    l_u8State = 0;
                }
            }
            break;
    }
}

uint8_t GetChgState(void)
{
    return false;
}

uint8_t UpdateBatPercent(void)
{
    #define FILTER_NUMBER 8
    static uint16_t  SmoothFilter[FILTER_NUMBER] = {0x00};
    static uint8_t   SmoothIndex = 0;
    static uint16_t  l_u32LastSum = 0x0;
    static uint8_t   l_bNumEnoughFlag = FALSE;
    static uint8_t   l_u8HighVoltTimes = 0;
    uint32_t l_sum = 0;
    uint8_t ret;
    uint8_t i;
	    
    d_u16Vbat = adc_get_voltage(AD_CH_VBAT) * 4;
    SmoothFilter[SmoothIndex] = d_u16Vbat;
    SmoothIndex++;
    if(FILTER_NUMBER == SmoothIndex){
        SmoothIndex = 0;
    	  l_bNumEnoughFlag = TRUE;
    }
    
    for(i = 0; i<FILTER_NUMBER; i++){
        l_sum += SmoothFilter[i];
    }
    l_sum = l_sum >> 3;

    if(l_bNumEnoughFlag){
        //瞬时大功率滤波
        if(l_sum > l_u32LastSum){
            l_u8HighVoltTimes++;
		        if((l_u8HighVoltTimes >= 60) && (GetChgState())){
				    l_u8HighVoltTimes = 0;
	                l_u32LastSum += 2;
			    }
			    if((l_sum > (l_u32LastSum + 1600)) && (l_u8HighVoltTimes >= 20)){
			        l_u8HighVoltTimes = 0;
	                l_u32LastSum = l_sum;
			    }
	    }
        else if((l_sum < l_u32LastSum) && (!GetChgState())){
		        l_u8HighVoltTimes = 0;

                //完全由电压决定
                l_u32LastSum -= 1;
        }
        else{
            l_u8HighVoltTimes = 0;
        }
    }
	
    if(l_u32LastSum < BAT_PERCENT_0){
        ret = 0;
    }
    else if(l_u32LastSum > BAT_PERCENT_100){
        ret = 100;
    }
    else{
        ret = (l_u32LastSum - BAT_PERCENT_0) / 6;
    }
    d_strCigaretteDis.VbatValue = l_u32LastSum / 10;
    return ret;
}

static void ta_tb_pwm_init(void)
{
    struct pwm_platform_data pwm_p_data;

    printf("----ta_tb_pwm_init----\n");
    pwm_p_data.pwm_aligned_mode = pwm_edge_aligned;         //边沿对齐
    pwm_p_data.pwm_ch_num = PWM_CH_TA;                      //通道号
    pwm_p_data.frequency = 500;                             //40KHz
    pwm_p_data.duty = 0;                                    //占空比00%
    pwm_p_data.h_pin = TA_GPIO;                             //任意引脚
    pwm_p_data.l_pin = -1;                                  //任意引脚,不需要就填-1
    pwm_p_data.complementary_en = 0;                        //两个引脚的波形, 0: 同步,  1: 互补，互补波形的占空比体现在H引脚上
    mcpwm_init(&pwm_p_data);

    pwm_p_data.pwm_aligned_mode = pwm_edge_aligned;         //边沿对齐
    pwm_p_data.pwm_ch_num = PWM_CH_TB;                      //通道号
    pwm_p_data.frequency = 500;                             //40KHz
    pwm_p_data.duty = 0;                                    //占空比0%
    pwm_p_data.h_pin = TB_GPIO;                             //任意引脚 
    pwm_p_data.l_pin = -1;                                  //任意引脚,不需要就填-1
    pwm_p_data.complementary_en = 1;                        //两个引脚的波形, 0: 同步,  1: 互补，互补波形的占空比体现在H引脚上
    mcpwm_init(&pwm_p_data);
}

uint32_t GetVbatUpdateTimerId(void)
{
    return d_u32VbatUpdateTimer;
}

void SetVbatUpdateTimerId(uint32_t id)
{
    d_u32VbatUpdateTimer = id;
}

void vbat_update_timer(void *priv)
{
    //上电还没有检测过电量
    static uint8_t l_u8PowerOnFirstDet = true;
    uint32_t l_u32CurrentTime = 0;
    static uint8_t l_u8Count = 0;
    static uint8_t l_u8State = 0;

    l_u32CurrentTime = OSGetTime();
    //上次抽烟时间大于当前时间，说明时间戳溢出了，那么更新上一次抽烟时间
    if(d_u32LastSmokingTime > l_u32CurrentTime){
        d_u32LastSmokingTime = l_u32CurrentTime;
    }
    
    switch(l_u8State){
        case 0:
            if((l_u32CurrentTime - d_u32LastSmokingTime >= TIME_25_SECOND) ||
               (l_u8PowerOnFirstDet)){
                l_u8State = 1;
                l_u8Count = 0;
            }
            break;

        case 1:
            if((l_u32CurrentTime - d_u32LastSmokingTime >= TIME_25_SECOND) || 
               (l_u8PowerOnFirstDet)){
                d_strCigaretteDis.VbatPercent = UpdateBatPercent();
                l_u8Count++;
                if(l_u8Count > 50){
                    l_u8PowerOnFirstDet = 0;
                    sys_timer_del(d_u32VbatUpdateTimer);
                    d_u32VbatUpdateTimer = 0;
                    l_u8State = 0;
                    printf("d_u8VbatPercent = %d\n",d_strCigaretteDis.VbatPercent);
                    printf("d_strCigaretteDis.VbatValue = %d\n",d_strCigaretteDis.VbatValue);
                }
            }
            else{
                l_u8State = 0;
            }
            break;
        
        default:
            break;
    }
}

static void ta_set_duty(uint16_t duty)
{
    printf("l_u8TempTaPwm: %d\n",duty);
    mcpwm_set_duty(PWM_CH_TA, duty*100);    
}

static void tb_set_duty(uint16_t duty)
{
    printf("l_u8TempTbPwm: %d\n",duty);
    mcpwm_set_duty(PWM_CH_TB, duty*100);    
}

/*
*******************************************************************************
 *Function:     ta_pwm_output_duty
 *Description:  发热丝1的PWM调节
 *Calls:       
 *Called By:   
 *Input:       
 *Output:      
 *Return:      
 *Others:       M18的3个挡位对应电压值：3.2V+3.2V
 *                                      3.4V+3.4V
 *                                      3.6V+3.6V
*******************************************************************************
*/
static uint8_t ta_pwm_output_duty(void)
{
	uint8_t ret = 0;
	
	d_u8RealPowerMode = d_strCigaretteDis.DisplayGearPosition; 
	switch(d_u8RealPowerMode){
	    case 1:
	        if(d_u16Vbat <= 210){
	            ret = 100;
	        }
	        else{
              ret = (uint8_t)(21000 / d_u16Vbat);
	        }
	        break;
			
		case 2:
	        if(d_u16Vbat <= 280){
	            ret = 100;
	        }
	        else{
              ret = (uint8_t)(28000 / d_u16Vbat);
	        }
		    break;
			
		case 3:
	        if(d_u16Vbat <= 350){
	            ret = 100;
	        }
	        else{
               ret = (uint8_t)(35000 / d_u16Vbat);
	        }
		    break;
	}
	return ret;
}

/*
*******************************************************************************
 *Function:     TbPwmOutputDuty
 *Description:  发热丝2的PWM调节
 *Calls:       
 *Called By:   
 *Input:       
 *Output:      
 *Return:      
 *Others:       
*******************************************************************************
*/
static uint8_t tb_pwm_output_duty(void)
{
	uint8_t ret = 0;
	
	d_u8RealPowerMode = d_strCigaretteDis.DisplayGearPosition; 
	switch(d_u8RealPowerMode){
	    case 1:
	        if(d_u16Vbat <= 210){
	            ret = 100;
	        }
	        else{
               ret = (uint8_t)(21000 / d_u16Vbat);
	        }
		    break;
			
		case 2:
	        if(d_u16Vbat <= 240){
	            ret = 100;
	        }
	        else{
               ret = (uint8_t)(24000 / d_u16Vbat);
	        }
		    break;
			
		case 3:
	        if(d_u16Vbat <= 270){
	            ret = 100;
	        }
	        else{
               ret = (uint8_t)(27000 / d_u16Vbat);
	        }
		    break;
	}
	return ret;
}

static void fire_tA_tb(void)
{
    static uint8_t  l_u8State = 0;
    //发热丝交替工作
    static uint8_t l_bRsSupersedeFlag = FALSE;
    uint8_t        l_u8TempTaPwm = 0;
    uint8_t        l_u8TempTbPwm = 0;

    switch(l_u8State){
        case 0:
    	    if(d_bMicDetectFlag){
                d_bMicDetectFlag = FALSE;
        
                if(0 == d_strCigaretteDis.VbatPercent){
                    printf("Low battery, unable to smoke\n");
                }
                else{
                    l_u8State = 1;
                    d_bRsState = TRUE;
                    d_u32RsUsedTime = OSGetTime();
                    l_bRsSupersedeFlag = !l_bRsSupersedeFlag;
                }
            }
    		break;
    		
        case 1:
    	    if(d_bMicDetectFlag){				
                d_bMicDetectFlag = FALSE;
                if(l_bRsSupersedeFlag){
                    l_u8TempTaPwm = ta_pwm_output_duty();
                    l_u8TempTbPwm = tb_pwm_output_duty();
                }
                else{
                    l_u8TempTbPwm = ta_pwm_output_duty();
                    l_u8TempTaPwm = tb_pwm_output_duty();
                }
                d_u32LastSmokingTime = OSGetTime();
            }
    		else{
    		    l_u8TempTaPwm = 0;
    		    l_u8TempTbPwm = 0;
    		    l_u8State = 0;

    			d_bRsState = FALSE;
                d_u32RsUsedTime = OSGetTime() - d_u32RsUsedTime;
    		}
    		break;
        default:
            break;
    }

    //双芯一起工作
    ta_set_duty(l_u8TempTaPwm);
    tb_set_duty(l_u8TempTbPwm);		    
}

void AddDisplayPowerMode(void)
{
    if(1 == d_strCigaretteDis.DisplayGearPosition){
        d_strCigaretteDis.DisplayGearPosition = 2;
    }
    else if(2 == d_strCigaretteDis.DisplayGearPosition){
        d_strCigaretteDis.DisplayGearPosition = 3;
    }
    else{
        d_strCigaretteDis.DisplayGearPosition = 1;
    }
    printf("d_strCigaretteDis.DisplayGearPosition: %d\n",d_strCigaretteDis.DisplayGearPosition);
}

uint8_t GetDisplayGearPosition(void)
{
    if(1 == d_strCigaretteDis.DisplayGearPosition){
        return 12;
    }
    else if(2 == d_strCigaretteDis.DisplayGearPosition){
        return 18;
    }
    else if(3 == d_strCigaretteDis.DisplayGearPosition){
        return 24;
    }
    return 18;
}

/*
*******************************************************************************
 *Function:     SetUsedOilQuantity
 *Description:  将油量数据写入Flash中
 *Calls:       
 *Called By:   
 *Input:       
 *Output:      
 *Return:      
 *Others:       
*******************************************************************************
*/
void SetUsedOilQuantity(void)
{
    int ret;
    
    do{
        ret = syscfg_write(CFG_USER_OIL_QUANTITY,&d_u32UsedPower,4);
    }while(ret != 4);
}

/*
*******************************************************************************
 *Function:     GetUsedOilQuantity
 *Description:  从flash中读出油量数据
 *Calls:       
 *Called By:   
 *Input:       
 *Output:      
 *Return:      
 *Others:       
*******************************************************************************
*/
void GetUsedOilQuantity(void)
{
    int ret;

    ret = syscfg_read(CFG_USER_OIL_QUANTITY,&d_u32UsedPower,4);
    if(ret != 4){
        //内存中没有数据，将初始数据写入内存
        d_u32UsedPower = 0;
        do{
            ret = syscfg_write(CFG_USER_OIL_QUANTITY,&d_u32UsedPower,4);
        }while(ret != 4);
    }
}

/*
*******************************************************************************
 *Function:     RecordUsagePower
 *Description:  记录使用的功率
 *Calls:       
 *Called By:   
 *Input:       
 *Output:      
 *Return:      
 *Others:       
*******************************************************************************
*/
void RecordUsagePower(void)
{
    static uint32_t l_u32FirstTimesGetUsedPower = 0;
    static uint8_t l_bLastRsState = FALSE;
    uint32_t l_u32CurrentUsedPower = 0;
    uint32_t l_u32Temp = 0;

    uint32_t l_u32GradePower[3] = {110, 130, 150};
		
		//首次上电，获取已消耗的功率
    if(!l_u32FirstTimesGetUsedPower){
        l_u32FirstTimesGetUsedPower = TRUE;

        GetUsedOilQuantity();
        if(d_u32UsedPower > USAGE_POWER_100){
            d_strCigaretteDis.OilNum = 0;
        }
        else{
            l_u32Temp = USAGE_POWER_100 / 101;
            d_strCigaretteDis.OilNum = (USAGE_POWER_100 - d_u32UsedPower) / l_u32Temp;
            if(d_strCigaretteDis.OilNum > 100){
                d_strCigaretteDis.OilNum = 100;
            }
        }
        // printf("1.d_u32UsedPower = %d",d_u32UsedPower);
        // printf("1.OilNum = %d",d_strCigaretteDis.OilNum);
    }
    else{
        if(l_bLastRsState && (!d_bRsState)){
            //油量已经抽完了，不需要再累计了
            if(d_u32UsedPower > USAGE_POWER_100){
                d_strCigaretteDis.OilNum = 0;
            }
            else{
                l_u32CurrentUsedPower = d_u32RsUsedTime * 10 * l_u32GradePower[d_u8RealPowerMode - 1];		
                d_u32UsedPower += l_u32CurrentUsedPower;
                SetUsedOilQuantity();
                if(d_u32UsedPower > USAGE_POWER_100){
                    d_strCigaretteDis.OilNum = 0;
                }
                else{
                    l_u32Temp = USAGE_POWER_100 / 101;
                    d_strCigaretteDis.OilNum = (USAGE_POWER_100 - d_u32UsedPower) / l_u32Temp;
                    if(d_strCigaretteDis.OilNum > 100){
                            d_strCigaretteDis.OilNum = 100;
                    }
                }
            }
            // printf("2.d_u32UsedPower = %d",d_u32UsedPower);
            // printf("2.OilNum = %d",d_strCigaretteDis.OilNum);

            // //一次抽烟已经完成，可以退出抽烟界面了
            // if(0 != d_u16SmokingTimerID){	    
            //     sys_timer_del(d_u16SmokingTimerID);
            //     d_u16SmokingTimerID = 0;
            //     UI_HIDE_CURR_WINDOW();
            //     UI_SHOW_WINDOW(ID_WINDOW_CLOCK);
            // }
        }
    }
    l_bLastRsState = d_bRsState;
}

void SmokingDet(void *parm)
{
    static uint8_t l_u8MicDisableCount = 0;
    d_u16Vbat = adc_get_voltage(AD_CH_VBAT) * 4 / 10;
    get_e_cigarette_mic_state();

    if(!d_bMicDetectFlag){
        l_u8MicDisableCount++;
        if(l_u8MicDisableCount >= 10){
            l_u8MicDisableCount = 0;
            if(0 != d_u16SmokingTimerID){
                sys_timer_del(d_u16SmokingTimerID);
                d_u16SmokingTimerID = 0;
                UI_HIDE_CURR_WINDOW();
                UI_SHOW_WINDOW(ID_WINDOW_CLOCK);
            }
        }
    }
    else{
        l_u8MicDisableCount = 0;
    }

    fire_tA_tb();
    RecordUsagePower();
}

void OpenSmokingTimer(void)
{
    if(d_u16SmokingTimerID == 0){
        ta_tb_pwm_init();
        d_u16SmokingTimerID = sys_timer_add(NULL, SmokingDet, 10);
    }
}