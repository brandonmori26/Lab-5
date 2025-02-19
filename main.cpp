#include "mbed.h"
#include "arm_book_lib.h"

#define PERIOD 0.02
#define DUTY_MIN 0.025
#define DUTY_MAX 0.115
#define DELAY_SECONDS 3000

PwmOut servo(PF_9); 

void PwmInit();
void PwmMax();
void PwmMin();

void PwmInit()
{
    servo.period(PERIOD);
    PwmMin();
}

void PwmMax()
{
    servo.write(DUTY_MAX);
}

void PwmMin()
{
    servo.write(DUTY_MIN);
}

int main() 
{
    PwmInit();  
    
    while(true) {
        PwmMin();                    // Set to minimum position
        wait_ms(DELAY_SECONDS);      
        
        PwmMax();                    // Set to maximum position
        wait_ms(DELAY_SECONDS);      
    }
}
