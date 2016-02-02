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
volatile int state=led1;
volatile int longerthan=0;
int main() {
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    initSwitch1();
    initLEDs();
    initTimer1();
    initTimer2();
     int PrevState=0;  
    while(1)
    {
            switch(state){
              case  led1:
                    LED1=ON;
                    LED2=OFF;
                    LED3=OFF;
                    PrevState=1;
                  if(PORTDbits.RD6==0)
                  {
                      state=debouncePress;
                  }
                    break;
               case led2:
                    LED1=OFF;
                    LED2=ON;
                    LED3=OFF;
                    PrevState=2;
                 if(PORTDbits.RD6==0)
                  {
                      state=debouncePress;
                  }
                    break;
               case led3:
                    LED1=OFF;
                    LED2=OFF;
                    LED3=ON;
                    PrevState=3;
                if(PORTDbits.RD6==0)
                  {
                      state=debouncePress;
                  }
                    break;
     
              case debouncePress:
                  delayMs(10);
                  state=wait;
                  break;
    
              case debounceRelease:
                  delayMs(10);
                  state=wait2;
                  break;
   
                case wait:
                    if(PORTDbits.RD6==0)
                    {
                        state=wait;
                    }
                    else
                    {
                        state=debounceRelease;
                    }
                    break;
                case wait2:
                    if (longerthan==1)
                    {
                        if(PrevState==1)
                        {
                            longerthan=0;
                            state=led3;
                        }
                        else if(PrevState==2)
                        {
                            longerthan=0;
                            state=led1;
                        }
                        else if(PrevState==3)
                        {
                            longerthan=0;
                            state=led2;
                        }
                    }
                    else
                    {
                        if(PrevState==1)
                        {
                            state=led2;
                        }
                        else if(PrevState==2)
                        {
                            state=led3;
                        }
                        else if(PrevState==3)
                        {   
                            state=led1;
                        }
                    }
                    break;
            }
        }
    
    
    return 0;
}

void __ISR(_TIMER_1_VECTOR, IPL7SRS) __T1Interupt()
{
    IFS0bits.T1IF=0;        //set flag back down
    longerthan=1;
}
