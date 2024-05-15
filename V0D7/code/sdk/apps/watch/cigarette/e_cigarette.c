#include "system/includes.h"
#include "e_cigarette.h"
#include "app_task.h"
#include "key_event_deal.h"
#include "asm\mcpwm.h"
#include "ui/ui_api.h"
#include "ui/ui_style.h"

static u16 l_u16SmokingTimerID = 0;

uint16_t d_u16Vbat = 0;
bool     d_bMicDetectFlag = FALSE;
uint8_t  d_u8DisplayPowerMode = 2;
uint8_t  d_u8RealPowerMode    = 2;

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

static void get_e_cigarette_mic_state(void)
{
    if(gpio_read(MIC_GPIO)){
        printf("-----MIC_GPIO HIGH-----\n");
        d_bMicDetectFlag = true;
    }
    else{
        printf("-----MIC_GPIO LOW-----\n");
        d_bMicDetectFlag = false;
    }
}

static void ta_tb_pwm_init(void)
{
    struct pwm_platform_data pwm_p_data;

    printf("----ta_tb_pwm_init----\n");
    pwm_p_data.pwm_aligned_mode = pwm_edge_aligned;         //边沿对齐
    pwm_p_data.pwm_ch_num = PWM_CH_TA;                      //通道号
    pwm_p_data.frequency = 200;                           //40KHz
    pwm_p_data.duty = 0;                                    //占空比00%
    pwm_p_data.h_pin = TA_GPIO;                             //任意引脚
    pwm_p_data.l_pin = -1;                                  //任意引脚,不需要就填-1
    pwm_p_data.complementary_en = 0;                        //两个引脚的波形, 0: 同步,  1: 互补，互补波形的占空比体现在H引脚上
    mcpwm_init(&pwm_p_data);

    pwm_p_data.pwm_aligned_mode = pwm_edge_aligned;         //边沿对齐
    pwm_p_data.pwm_ch_num = PWM_CH_TB;                      //通道号
    pwm_p_data.frequency = 200;                           //40KHz
    pwm_p_data.duty = 0;                                    //占空比0%
    pwm_p_data.h_pin = TB_GPIO;                             //任意引脚 
    pwm_p_data.l_pin = -1;                                  //任意引脚,不需要就填-1
    pwm_p_data.complementary_en = 1;                        //两个引脚的波形, 0: 同步,  1: 互补，互补波形的占空比体现在H引脚上
    mcpwm_init(&pwm_p_data);
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
	
	d_u8RealPowerMode = d_u8DisplayPowerMode; 
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
	
	d_u8RealPowerMode = d_u8DisplayPowerMode; 
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
        
                l_u8State = 1;
                l_bRsSupersedeFlag = !l_bRsSupersedeFlag;
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
                printf("Vbat:%d\n",d_u16Vbat);
            }
    		else{
    		    l_u8TempTaPwm = 0;
    		    l_u8TempTbPwm = 0;
    		    l_u8State = 0;
    		}
    		break;
        default:
            break;
    }

    //双芯一起工作
    ta_set_duty(l_u8TempTaPwm);
    tb_set_duty(l_u8TempTbPwm);		    
}

// static int e_cigatette_sys_event_handler(struct sys_event *event)
// {
//     int ret = false;
//     switch (event->type) {
//     case SYS_KEY_EVENT:
//         ret = e_cigarette_key_event_handler(event);
//         break;
//     return ret;
//     }
// }

// void get_event_msg(void)
// {
//     int msg[32];

//     app_task_get_msg(msg, ARRAY_SIZE(msg), 0);
//     switch (msg[0]) {
//     case APP_MSG_SYS_EVENT:
//         if (e_cigatette_sys_event_handler((struct sys_event *)(msg + 1)) == false) {
//             app_default_event_deal((struct sys_event *)(&msg[1]));
//         }
//         app_task_clear_key_msg();
//         break;
//     default:
//         break;
//     }
// }

void AddDisplayPowerMode(void)
{
    if(1 == d_u8DisplayPowerMode){
        d_u8DisplayPowerMode = 2;
    }
    else if(2 == d_u8DisplayPowerMode){
        d_u8DisplayPowerMode = 3;
    }
    else{
        d_u8DisplayPowerMode = 1;
    }
    printf("d_u8DisplayPowerMode: %d\n",d_u8DisplayPowerMode);
}

uint8_t GetDisplayPowerMode(void)
{
    return d_u8DisplayPowerMode;
}

void SmokingDet(void *parm)
{
    static uint8_t l_u8MicDisableCount = 0;
    d_u16Vbat = adc_get_voltage(AD_CH_VBAT) * 4 / 10;
    get_e_cigarette_mic_state();

    if(!d_bMicDetectFlag){
        printf("----SmokingDet:1----\n");
        l_u8MicDisableCount++;
        printf("l_u8MicDisableCount = %d\n",l_u8MicDisableCount);
        if(l_u8MicDisableCount >= 3){
            printf("----SmokingDet:2----\n");
            l_u8MicDisableCount = 0;
            if(0 != l_u16SmokingTimerID){
                sys_timer_del(l_u16SmokingTimerID);
                l_u16SmokingTimerID = 0;
                UI_HIDE_CURR_WINDOW();
                UI_SHOW_WINDOW(ID_WINDOW_CLOCK);
                printf("2.l_u16SmokingTimerID = %d\n",l_u16SmokingTimerID);
            }
        }
    }
    else{
        printf("----SmokingDet:3----\n");
        l_u8MicDisableCount = 0;
    }

    fire_tA_tb();
}

void OpenSmokingTimer(void)
{
    if(l_u16SmokingTimerID == 0){
        ta_tb_pwm_init();
        l_u16SmokingTimerID = sys_timer_add(NULL, SmokingDet, 10);
        printf("1.l_u16SmokingTimerID = %d\n",l_u16SmokingTimerID);
    }
}