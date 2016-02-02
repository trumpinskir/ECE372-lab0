/* 
 * File:   switch.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:12 PM
 */

#include <xc.h>

void initSwitch1(){
    TRISDbits.TRISD6=1;
    CNPUDbits.CNPUD6=1;
    CNCONDbits.ON=0;        //turn on CN for port D
}