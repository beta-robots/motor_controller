//testing ADXL335

//standard library
#include "Arduino.h"

//ADXL335 library
#include "motor_controller.h"

//pin assignement & constants
int PIN_LED = 13; 
int PIN_MOTOR_PWM = 3; 
int PIN_MOTOR_DIRECTION = 2; 
int SERIAL_BAUD_RATE = 9600;

//motor controller object
MotorController motor(PIN_MOTOR_PWM, PIN_MOTOR_DIRECTION);

//global variables
int ii = 0;
int jj = 1; 

//setup
void setup() 
{
    //sets pin_led as a digital output
    pinMode(PIN_LED, OUTPUT);
    
    //opens serial port, sets data rate to 9600 bps, Useful for debugging
    Serial.begin(SERIAL_BAUD_RATE);     
}
 
//main loop
void loop() 
{    
    
    // turn the LED on/off
    digitalWrite(PIN_LED, boolean(jj%2));   
    
    //In case motor is stopped, start up it
    if ( motor.getState() == STATE_STOP )
    {
        //sets turn direction
        motor.setTurnDirection(boolean(jj%2));
        
        //sets the motor to start state
        motor.start();
        
        //turn direction counter
        jj++; 
    }
    
    //run the motor
    motor.run(); 
    
    //stop motor after a while
    if (ii%(PWM_NUM_STEPS+10) == 0) motor.stop(); 
    ii++; 

    //relax
    delay(50); 
}
