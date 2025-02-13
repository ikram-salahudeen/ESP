#include "mbed.h"

#define MOTOR_L_BIPOLAR PB_4
#define MOTOR_L_DIR PB_3
#define MOTOR_L_PWM PA_8
#define MOTOR_L_CUR_SENSE1 PA_9
#define MOTOR_L_CUR_SENSE2 PC_7
#define ENCODER_L_1 PA_1
#define ENCODER_L_2 PA_0
#define ENCODER_L_IDX NC

#define MOTOR_R_BIPOLAR PB_5
#define MOTOR_R_DIR PA_10
#define MOTOR_R_PWM PB_10
#define MOTOR_R_CUR_SENSE2 PA_7
#define MOTOR_R_CUR_SENSE1 PA_6
#define ENCODER_R_1 PC_1
#define ENCODER_R_2 PC_0  bv 
#define ENCODER_R_IDX NC

#define ENABLE PB_6