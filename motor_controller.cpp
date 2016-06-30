#include "motor_controller.h"

MotorController::MotorController(int _pin_pwm, int _pin_turn_direction)
{
    //init member variables
    state_ = STATE_STOP; 
    pin_pwm_ = _pin_pwm; 
    pin_turn_direction_ = _pin_turn_direction; 
    pwm_idx_ = 0;
    
    //init pwm values
    for (unsigned int ii=0; ii<PWM_NUM_STEPS; ii++)
    {
        pwm_ramp_[ii] = pwm_preset[ii]; //TODO with the proper curve
    }
    
    //sets pin_turn_direction_ as a digital output
    pinMode(pin_turn_direction_, OUTPUT);  
}

MotorController::~MotorController()
{
    
}

int MotorController::getState()
{
    return state_; 
}

void MotorController::setTurnDirection(boolean _dir)
{
    digitalWrite(pin_turn_direction_, _dir);   
}

void MotorController::start()
{
    state_ = STATE_STARTING; 
    pwm_idx_ = 1; 
}

void MotorController::stop()
{
    //state to stopping
    state_ = STATE_STOPPING;  
    
    //loops until the motor stops
    while (state_ != STATE_STOP) 
    {
        run(); 
        delay(CURVE_STEP_DURATION*1000);//in milliseconds 
    }
}

void MotorController::run()
{
    int pwm_level; 
    
    switch(state_)
    {
        case STATE_STOP:
            pwm_idx_ = 0; 
            break; 
            
        case STATE_STARTING:
            //check if in the ramp-up or already finished
            if (pwm_idx_ < PWM_NUM_STEPS) 
            {
                pwm_idx_ ++; 
            }
            else
            {
                pwm_idx_ = PWM_NUM_STEPS; 
                state_ = STATE_RUNNING; 
            }   
            break; 
        
        case STATE_RUNNING:  
            pwm_idx_ = PWM_NUM_STEPS; 
            break;    

        case STATE_STOPPING:
            //check if in the ramp-down or already finished
            if (pwm_idx_ > 0) 
            {
                pwm_idx_ --; 
            }
            else
            {
                pwm_idx_ = 0; 
                state_ = STATE_STOP; 
            }   
            break; 

        default:  
            pwm_idx_ = 0; //stop
            break; 
    }
    
    //set pwm level to the pin where the motor is attached
    pwm_level = pwm_ramp_[pwm_idx_]; 
    analogWrite(pin_pwm_, pwm_level);   
}
