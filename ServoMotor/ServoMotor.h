/*
 * ServoMotor.h
 *
 *  Created on: 16 de out de 2018
 *      Author: Suzi
 */

#ifndef SERVOMOTOR_SERVOMOTOR_H_
#define SERVOMOTOR_SERVOMOTOR_H

#define MOTOR_PORT GPIO_B
void timer1_pwm_hardware_init();
void set_DutyCycle(uint16_t duty);
FILE* configure_LCD_Motor();
void Motor_control(FILE *lcd_stream);

#endif /* SERVOMOTOR_SERVOMOTOR_H_ */
