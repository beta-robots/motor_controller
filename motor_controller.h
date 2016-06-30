#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

//Arduino
#include "Arduino.h"

//constants motor state
#define STATE_STOP 0
#define STATE_STARTING 1
#define STATE_RUNNING 2
#define STATE_STOPPING 3

//constants motor start-up and stop ramp
#define CURVE_DURATION 0.5 //duration of start/stop curves [s]
#define CURVE_STEP_DURATION 0.01 //[s]
#define PWM_NUM_STEPS (int)(CURVE_DURATION/CURVE_STEP_DURATION)

//preset pwm level values found using scilab/motor_maxon_trajectory.sce
const int pwm_preset[PWM_NUM_STEPS] = {63,63,64,65,66,68,69,72,74,77,80,83,86,90,93,97,101,105, 
                                   110,114,118,123,128,132,137,142,146,151,156,160,165,169,174,178,
                                   182,186,190,194,197,201,204,207,209,212,214,216,217,218,219,220};

//class for motor controller
class MotorController
{
    protected: 
        //variables
        int state_; 
        int pin_pwm_; //where accel_y is attached
        int pin_turn_direction_; //where accel_y is attached
        int pwm_idx_; //in STARTING/STOPPING states, indicates at which index of the pwm_ramp_vector the motor is.
        int pwm_ramp_[PWM_NUM_STEPS]; //pwm levels to start up and stop the motor smoothly
        
    public: 
        //constructor with pins
        MotorController(int _pin_pwm, int _pin_turn_direction); 
        
        //destructor
        ~MotorController(); 
        
        //get state
        int getState(); 
        
        //set motor turn direction. _dir should be either HIGH or LOW
        void setTurnDirection(boolean _dir); 
        
        //start. No internal loop. Just set the state. 
        void start(); 
        
        //stop. Internal loop up to stop
        void stop(); 
        
        //run. Carry on and state transition
        void run(); 
        
};
#endif
