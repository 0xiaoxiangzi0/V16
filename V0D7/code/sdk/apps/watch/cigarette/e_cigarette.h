#ifndef _E_CIGARETTE_H_
#define _E_CIGARETTE_H_

#include "asm/gpio.h"

#define MIC_GPIO IO_PORTC_06
#define TA_GPIO IO_PORTA_01
#define TB_GPIO IO_PORTA_05

#define PWM_CH_TA pwm_ch0
#define PWM_CH_TB pwm_ch1

//OSGetTime()获取到的数字，相差1就是相差10ms
#define TIME_25_SECOND 2500

typedef struct{
    uint8_t DisplayGearPosition;
    uint8_t OilNum;
    uint16_t VbatValue;
    uint8_t VbatPercent;
}STRUCT_CIGARETTE_DISPLAY;

extern void e_cigarette_init(void);
extern void AddDisplayPowerMode(void);
extern uint8_t GetDisplayGearPosition(void);
extern void OpenSmokingTimer(void);

#endif