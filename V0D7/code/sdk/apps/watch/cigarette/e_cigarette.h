#ifndef _E_CIGARETTE_H_
#define _E_CIGARETTE_H_

#include "asm/gpio.h"

#define MIC_GPIO IO_PORTC_06
#define TA_GPIO IO_PORTA_01
#define TB_GPIO IO_PORTA_05

#define PWM_CH_TA pwm_ch0
#define PWM_CH_TB pwm_ch1

extern void e_cigarette_init(void);
extern void AddDisplayPowerMode(void);
extern uint8_t GetDisplayPowerMode(void);
extern void OpenSmokingTimer(void);

#endif