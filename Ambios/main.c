#include <msp430.h>

#include "uart.h"

void uart_rx_isr(unsigned char c) {
	uart_putc(c);
	P1OUT ^= BIT0;		// toggle P1.0 (red led)
}

/**
 * Main routine
 */
int main(void)
{
    WDTCTL  = WDTPW + WDTHOLD; 	// Stop WDT
    if (CALBC1_16MHZ==0xFF)					// If calibration constant erased
    	{
    		while(1);                			// do not load, trap CPU!!
    	}


	BCSCTL1 = CALBC1_16MHZ;      // Set DCO
  	DCOCTL  = CALDCO_16MHZ;

	P1DIR  = BIT0 + BIT6; 		// P1.0 and P1.6 are the red+green LEDs
	P1OUT  = BIT0 + BIT6; 		// All LEDs off


    uart_init();
   //register ISR called when data was received
    uart_set_rx_isr_ptr(uart_rx_isr);

    // initialize LED strip
    initStrip();  // ***** HAVE YOU SET YOUR NUM_LEDS DEFINE IN WS2812.C? ******
	//fillStrip(  0x00, 0x00, 0xFF);
	//showStrip();

    __bis_SR_register(GIE);
}
