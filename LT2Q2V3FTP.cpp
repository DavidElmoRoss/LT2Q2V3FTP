// Include Section
#include "mbed.h"                           
#include "Grove_LCD_RGB_Backlight.h"        

// Hardware Definition Section
Grove_LCD_RGB_Backlight greg(D14,D15);     
InterruptIn merlin(D6);                        

// Global Variables
short motion_detected=0;                    

// Asynchronous Interrupt Service Routine
void flipper(void)
{
   motion_detected=1;                      
} 

int main(void)
{
                        // add code to activate interrupt on falling edge 
    greg.clear(); 
    greg.setRGB(0x00,0x00,0xff);     
    for(;;)                                 
    {
        greg.clear();
        greg.setRGB(0x00,0x00,0xff);       
        if(motion_detected == 1)            
        {
            motion_detected=0;              
            greg.setRGB(0xff,0x00,0x00);   
            wait_ms(500);                   
        }
    }     
}