#ifndef _APP_AUDIO_H_
#define _APP_AUDIO_H_

#include "generic/typedef.h"
#include "board_config.h"
#include "asm/dac.h"

#if BT_SUPPORT_MUSIC_VOL_SYNC
#define TCFG_MAX_VOL_PROMPT						 0
#else
#define TCFG_MAX_VOL_PROMPT						 1
#endif

//*********************************************************************************//
//                               USB Audio配置                                     //
//*********************************************************************************//
/*usb mic的数据是否经过CVP,包括里面的回音消除(AEC)、非线性回音压制(NLP)、降噪(ANS)模块*/
#define TCFG_USB_MIC_CVP_ENABLE		                DISABLE_THIS_MOUDLE
#define TCFG_USB_MIC_CVP_MODE		                (ANS_EN | NLP_EN)

//*********************************************************************************//
//                               Audio CVP配置                                     //
//*********************************************************************************//
/*回音消除的参考数据通过adc 回采 dac的数据作为参考数据，
  默认打开的第一个mic是麦克风，第二和第三个mic是回采参考数据*/
#define TCFG_CVP_REF_IN_ADC_ENABLE		            DISABLE_THIS_MOUDLE
#define TCFG_CVP_REF_IN_ADC_CH                      (AUDIO_ADC_MIC_0 | AUDIO_ADC_MIC_3)

//麦克风阵列校准使能
#define TCFG_AUDIO_MIC_ARRAY_TRIM_ENABLE    0

//*********************************************************************************//
//                               Audio smart voice配置                              //
//*********************************************************************************//
/*播歌时语音识别做回音消除*/
#define TCFG_SMART_VOICE_USE_AEC 		    0
#define TCFG_A2DP_MUSIC_SAMPLE_FRAM         48000

/*
 *该配置适用于没有音量按键的产品，防止打开音量同步之后
 *连接支持音量同步的设备，将音量调小过后，连接不支持音
 *量同步的设备，音量没有恢复，导致音量小的问题
 */
#define TCFG_VOL_RESET_WHEN_NO_SUPPORT_VOL_SYNC	 0 //不支持音量同步的设备默认最大音量

#define MC_BIAS_ADJUST_DISABLE			0	//省电容mic偏置校准关闭
#define MC_BIAS_ADJUST_ONE			 	1	//省电容mic偏置只校准一次（跟dac trim一样）
#define MC_BIAS_ADJUST_POWER_ON		 	2	//省电容mic偏置每次上电复位都校准(Power_On_Reset)
#define MC_BIAS_ADJUST_ALWAYS		 	3	//省电容mic偏置每次开机都校准(包括上电复位和其他复位)
/*
 *省电容mic偏置电压自动调整(因为校准需要时间，所以有不同的方式)
 *1、烧完程序（完全更新，包括配置区）开机校准一次
 *2、上电复位的时候都校准,即断电重新上电就会校准是否有偏差(默认)
 *3、每次开机都校准，不管有没有断过电，即校准流程每次都跑
 */
#if TCFG_MIC_CAPLESS_ENABLE
#define TCFG_MC_BIAS_AUTO_ADJUST	MC_BIAS_ADJUST_POWER_ON
#else
#define TCFG_MC_BIAS_AUTO_ADJUST	MC_BIAS_ADJUST_DISABLE
#endif/*TCFG_MIC_CAPLESS_ENABLE*/
#define TCFG_MC_CONVERGE_PRE			1  //省电容mic预收敛
#define TCFG_MC_CONVERGE_TRACE			0  //省电容mic收敛值跟踪
/*
 *省电容mic收敛步进限制
 *0:自适应步进调整, >0:收敛步进最大值
 *注：当mic的模拟增益或者数字增益很大的时候，mic_capless模式收敛过程,
 *变化的电压放大后，可能会听到哒哒声，这个时候就可以限制住这个收敛步进
 *让收敛平缓进行(前提是预收敛成功的情况下)
 */
#define TCFG_MC_DTB_STEP_LIMIT			3  //最大收敛步进值
/*
 *省电容mic使用固定收敛值
 *可以用来测试默认偏置是否合理：设置固定收敛值7000左右，让mic的偏置维持在1.5v左右即为合理
 *正常使用应该设置为0,让程序动态收敛
 */
#define TCFG_MC_DTB_FIXED				0

#define TCFG_ESCO_PLC					1  	//通话丢包修复
#define TCFG_AEC_ENABLE					1	//通话回音消除使能
#define TCFG_AUDIO_CONFIG_TRACE			0	//音频模块配置跟踪查看
#define TCFG_DIG_PHASE_INVERTER_EN		0   //数字反相器，用来矫正DAC的输出相位(AC701N输出正相，默认关)

#define TCFG_ESCO_LIMITER			0  	//通话近端限幅器
#define TCFG_ESCO_NOISEGATE			0  	//通话近端底噪抑制

#if TCFG_USER_BLE_ENABLE
#define TCFG_AEC_SIMPLEX			0  //通话单工模式配置
#else
#define TCFG_AEC_SIMPLEX			0  //通话单工模式配置
#endif


#define MAX_ANA_VOL             (3)	//系统最大模拟音量 (0-3)
#define MAX_COM_VOL             (16)    // 具体数值应小于联合音量等级的数组大小 (combined_vol_list)
#define MAX_DIG_VOL             (16)

/*
    数字音量等级表生成参数(软件数字音量和硬件数字音量共用两个参数)
    修改 DIG_VOL_MAX_VALUE 也要留意一下 DIG_VOL_STEP 参数，避免在小音量等级时候音量太小。
*/

#if (TCFG_AUDIO_DAC_MODE == DAC_MODE_L_DIFF)
#define DIG_VOL_MAX_VALUE       (-5.0f)  // 数字音量最大值(单位:dB)
#elif (TCFG_AUDIO_DAC_MODE == DAC_MODE_H1_DIFF)
#define DIG_VOL_MAX_VALUE       (-8.0f)  // 数字音量最大值(单位:dB)
#else
#define DIG_VOL_MAX_VALUE       (0.0f)  // 数字音量最大值(单位:dB)
#endif

#define DIG_VOL_STEP            (3.0f)  // 逐级递减差值(单位:dB)

/*
 *软件数字音量表自定义
 * 0:使用软件数字音量文件中的默认数组
 * 1:按上面设置的参数重新生成
 */
#define SW_DIG_VOL_TAB_USER_DEFINED		0

#if ((SYS_VOL_TYPE == VOL_TYPE_DIGITAL) || (SYS_VOL_TYPE == VOL_TYPE_DIGITAL_HW))
#define SYS_MAX_VOL             MAX_DIG_VOL
#define SYS_DEFAULT_VOL         0//SYS_MAX_VOL
#define SYS_DEFAULT_TONE_VOL    8
#define SYS_DEFAULT_SIN_VOL    	6

#elif (SYS_VOL_TYPE == VOL_TYPE_AD)
#define SYS_MAX_VOL             MAX_COM_VOL
#define SYS_DEFAULT_VOL         SYS_MAX_VOL
#define SYS_DEFAULT_TONE_VOL    14
#define SYS_DEFAULT_SIN_VOL    	8
#else
#error "SYS_VOL_TYPE define error"
#endif



/*数字音量最大值定义*/
#define DEFAULT_DIGITAL_VOLUME   16384


#define BT_MUSIC_VOL_LEAVE_MAX	16		/*高级音频音量等级*/
#define BT_MUSIC_VOL_STEP		(-3.0f)	/*高级音频音量等级衰减步进*/
#define BT_CALL_VOL_LEAVE_MAX	15		/*通话音量等级*/
#define BT_CALL_VOL_STEP		(-2.0f)	/*通话音量等级衰减步进*/


/*
 *audio state define
 */
#define APP_AUDIO_STATE_IDLE        0
#define APP_AUDIO_STATE_MUSIC       1
#define APP_AUDIO_STATE_CALL        2
#define APP_AUDIO_STATE_WTONE       3
#define APP_AUDIO_STATE_LINEIN      4
#define APP_AUDIO_CURRENT_STATE     5

#define APP_AUDIO_MAX_STATE    (APP_AUDIO_CURRENT_STATE + 1)


#if TCFG_USER_EMITTER_ENABLE
#define AUDIO_OUTPUT_INCLUDE_BT 	((defined(AUDIO_OUTPUT_WAY)) && (AUDIO_OUTPUT_WAY == AUDIO_OUTPUT_WAY_BT)) \
    						    || ((defined(AUDIO_OUT_WAY_TYPE)) && (AUDIO_OUT_WAY_TYPE & AUDIO_WAY_TYPE_BT))
#else
#define AUDIO_OUTPUT_INCLUDE_BT     0
#endif


#define AUDIO_OUTPUT_INCLUDE_FM 	((defined(AUDIO_OUTPUT_WAY)) && (AUDIO_OUTPUT_WAY == AUDIO_OUTPUT_WAY_FM)) \
    						    || ((defined(AUDIO_OUT_WAY_TYPE)) && (AUDIO_OUT_WAY_TYPE & AUDIO_WAY_TYPE_FM))




u8 get_max_sys_vol(void);
u8 get_tone_vol(void);

s8 app_audio_get_volume(u8 state);
s8 app_audio_get_volume_r(u8 state);
void app_audio_set_volume(u8 state, s8 volume, u8 fade);
void app_audio_set_volume_each_channel(u8 state, s8 volume_l, s8 volume_r, u8 fade);
void app_audio_volume_up(u8 value);
void app_audio_volume_down(u8 value);
void app_audio_volume_set(u8 value);
void app_audio_state_switch(u8 state, s16 max_volume);
void app_audio_mute(u8 value);
s16 app_audio_get_max_volume(void);
void app_audio_state_switch(u8 state, s16 max_volume);
void app_audio_state_exit(u8 state);
void app_audio_set_max_volume(u8 state, s16 max_volume);
u8 app_audio_get_state(void);
void volume_up_down_direct(s8 value);
void app_audio_set_mix_volume(u8 front_volume, u8 back_volume);
void app_audio_set_digital_volume(s16 volume);

void app_set_sys_vol(s16 vol_l, s16  vol_r);
void app_set_max_vol(s16 vol);
void audio_volume_list_init(u8 cfg_en);

u32 phone_call_eq_open();
int eq_mode_sw();
int mic_test_start();
int mic_test_stop();

void dac_power_on(void);
void dac_power_off(void);

/*打印audio模块的数字模拟增益：DAC/ADC*/
void audio_gain_dump();
void audio_adda_dump(void); //打印所有的dac,adc寄存器

void app_audio_volume_init(void);
void app_audio_output_init(void);
int app_audio_output_mode_set(u8 output);
int app_audio_output_mode_get(void);
int app_audio_output_channel_get(void);
int app_audio_output_channel_set(u8 channel);
int app_audio_output_write(void *buf, int len);
int app_audio_output_samplerate_select(u32 sample_rate, u8 high);
int app_audio_output_samplerate_set(int sample_rate);
int app_audio_output_samplerate_get(void);
int app_audio_output_start(void);
int app_audio_output_stop(void);
int audio_dac_trim_value_check(struct audio_dac_trim *dac_trim);


#endif/*_APP_AUDIO_H_*/
