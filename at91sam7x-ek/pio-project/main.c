/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------*/

#include <board.h>
#include <pio/pio.h>


//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------

 /// Pushbutton \#1 pin instance.
const Pin pinPB1 = PIN_PUSHBUTTON_1;

/// Pushbutton \#1 pin instance.
const Pin pinPB2 = PIN_PUSHBUTTON_2;

// LED
const Pin pinLED[]={PINS_LEDS};

#define bilink    0
#define on        1
#define off       2

/// Indicates the current state (on or off) for each LED.
unsigned char pLedStates[2] = {1, 1};

void delay_ms(unsigned long b){
unsigned long y=0;	
unsigned long e=0;
do{
for (e=0;e<3686;e++);
y++;
} while(y<b);
y=0;
}

//------------------------------------------------------------------------------
/// Application entry point. Configures the LEDs and buttons
/// and makes LED\#1 blink in its infinite loop, using the Wait function.
/// \return Unused (ANSI-C compatibility).
//------------------------------------------------------------------------------
int main(void)
{
	unsigned char state;
	PIO_Configure(pinLED,PIO_LISTSIZE(pinLED));
	PIO_Configure(&pinPB1,1);
	PIO_Configure(&pinPB2,1);
    
    // Main loop
    while (1) {
	  switch (state){
			//-------------led bilink
    case bilink:			
    PIO_Set(&pinLED[0]);
		delay_ms(500);
    PIO_Clear(&pinLED[0]);
		delay_ms(500);
		break;
		//---------------led on
		case on:
     PIO_Set(pinLED);
     break;		
		//---------------led off
		case off:
		 PIO_Clear(pinLED);
		 break;
    		
	    }//end of switch
			
			
		if(PIO_Get(&pinPB1)){
    state=on;
		 }	

		if(PIO_Get(&pinPB2)){
    state=off;
		 }
		 
    }
}

