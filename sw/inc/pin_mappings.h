/*
 * pin_mappings.h
 *
 *  Created on: Jan 27, 2015
 *      Author: usenius
 *
 *  Defines keypad pin mappings for different pcb revisions used
 */

#ifndef UW_MB_SRC_PIN_MAPPINGS_H_
#define UW_MB_SRC_PIN_MAPPINGS_H_

#include <uv_gpio.h>
#include <uv_timer.h>
#include <uv_adc.h>
#include <uv_pwm.h>



#define DRIVE1_PWMA			PWM1_4
#define DRIVE1_PWMB			PWM0_1
#define DRIVE1_SENSE		ADC0_3

#define DRIVE2_PWMA			PWM0_4
#define DRIVE2_PWMB			PWM1_3
#define DRIVE2_SENSE		ADC0_8

#define D4WD_OUT			P0_24
#define D4WD_SENSE			ADC1_9

#define TELESCOPE_PWMA		PWM1_1
#define TELESCOPE_PWMB		PWM2_4
#define TELESCOPE_SENSE		ADC1_5


#endif /* UW_MB_SRC_PIN_MAPPINGS_H_ */
