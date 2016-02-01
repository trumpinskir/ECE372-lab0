/* 
 * File:   led.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "led.h"

#define OUTPUT 0
#define ON 1
#define OFF 0
void initLEDs(){
    TRISDbits.TRISD0=OUTPUT;
    TRISDbits.TRISD1=OUTPUT;
    TRISDbits.TRISD2=OUTPUT;
    
    LATDbits.LATD0 = ON;
    LATDbits.LATD1 = OFF;
    LATDbits.LATD2 = OFF;
    
}

void turnOnLED(int led){
    
    //TODO: You may choose to write this function
    // as a matter of convenience
    
}