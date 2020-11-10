/*
Program to flash LCD Display from default White to RED when PIR Motion
Detector goes from high to low. The GLOBAL VARIABLE motion_detected will
have a default value of 0.  The Interrupt Service routine will set the
variable motion_detected to 1. Every time through the loop in the mainline
it will check to see if motion_detected==1  . If it is it will make the
LCD SCREEN go red for 0.5 seconds, and reset motion_detected back to 0.
*/

// Include Section
#include "mbed.h"                           // include the mbed.h library
#include "Grove_LCD_RGB_Backlight.h"        // include Grove LCD library

// Hardware Definition Section
Grove_LCD_RGB_Backlight flash(D14,D15);     // flash represents the LCD connect
InterruptIn PIR(D6);                        // PIR represents the PIR connect

// Global Variables
short motion_detected=0;                    // motion_detected ==0, no motion

// Asynchronous Interrupt Service Routine
void LOW(void)
{
   motion_detected=1;                       // motion_detected ==1 motion
} 

int main(void)
{
    PIR.fall(&LOW);                         // connect code at LOW to IRQ
    flash.clear();
    flash.setRGB(0x00,0x00,0xff);           // set LCD to white
    for(;;)                                 // loop forever
    {
        flash.clear();
        flash.setRGB(0xff,0xff,0xff);       // set LCD to white
        if(motion_detected == 1)            // if motion detected
        {
            motion_detected=0;              // set variable to 0
            flash.setRGB(0xff,0x00,0x00);   // set lcd to red
            wait_ms(500);                   // hold red colour for 0.5 seconds
        }
    }     
}