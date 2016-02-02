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
    TMR2=0;
    //T2CONbits.TCKPS=7;  //timer 2 scale 256
    //PR1=39061;
    IFS0bits.T2IF=0;        //flag
}

delayMs(int delay){
    //TODO: Using timer 2, create a delay
    // that is delay amount of 10 ms.
    TMR2=0;
    T2CONbits.TCKPS=7;      //prescale of 256
    PR2=390;
    T2CONbits.ON=1;
    IFS0bits.T2IF=0;
    while(IFS0bits.T2IF==0)
    {
        
    }
    T2CONbits.ON=0;
    IFS0bits.T2IF=0;
}