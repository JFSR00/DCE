/*
 * motors.h
 *
 * Created: 24/05/2021 12:17:48
 *  Author: Juan Francisco Santos Relinque
 */ 


#ifndef MOTORS_H_
#define MOTORS_H_

#define BACKWARD 0
#define FORWARD 1

void motor_init();

void motor_turnLeft(uint8_t spd, uint8_t dir);

void motor_turnRigth(uint8_t spd, uint8_t dir);

void motor_forward(uint8_t spd);

void motor_backward(uint8_t spd);

void motor_setVelocity(uint8_t spd, uint8_t dir);

void motor_setDirection(uint8_t dir);

void motor_stop();

#endif /* MOTORS_H_ */