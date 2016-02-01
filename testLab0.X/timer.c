/* 
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>
#define PRESCALAR_256 3

void initTimer1(){
    TMR1=0;
    T1CONbits.TCKPS=PRESCALAR_256;
    PR1=39061;              //1 second period
    T1CONbits.ON=1;          //turn timer on
    IFS0bits.T1IF=0;        //interrupt flag is down
    IEC0bits.T1IE=1;        //interrupt enabled
    IPC1bits.T1IP=7;        //priority is 7
 
}

initTimer2(){
    //TODO: Initialize Timer 2.
}

delayMs(int delay){
    //TODO: Using timer 2, create a delay
    // that is delay amount of ms.
}