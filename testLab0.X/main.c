/* 
 * File:   main.c
 * Author: gvanhoy
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "switch.h"
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config2.h"

#define OUTPUT 0
#define INPUT 1
#define ON 1
#define OFF 0
#define LED1 LATDbits.LATD0 
#define LED2 LATDbits.LATD1 
#define LED3 LATDbits.LATD2 

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    led1, led2, led3, wait, wait2, debouncePress, debounceRelease, debounceRelease2
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile int state=led2;
int main() {
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    initSwitch1();
    initLEDs();
    initTimer1();
    //initTimer2();
       
    while(1)
    {
        switch(state){
              case  led1:
                    LED1=ON;
                    LED2=OFF;
                    LED3=OFF;
                    break;
               case led2:
                    LED1=OFF;
                    LED2=ON;
                    LED3=OFF;
                    break;
               case led3:
                    LED1=OFF;
                    LED2=OFF;
                    LED3=ON;
                    break;
        }
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt()
{
            IFS1bits.CNDIF=0;
            PORTD;
            
            if(PORTDbits.RD6==1)
            {
                LATDbits.LATD0=1;
            }
            else
            {
                LATDbits.LATD0=0;
            }
}

void __ISR(_TIMER_1_VECTOR, IPL7SRS) __T1Interupt()
{
    IFS0bits.T1IF=0;        //set flag back down
    if(state==led1)
    {
        state=led2;
    }
    else if(state==led2)
    {
        state=led3;
    }
    else if(state==led3)
    {
        state=led1;
    }
}