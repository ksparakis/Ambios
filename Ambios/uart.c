/*
 * This file is part of the MSP430 hardware UART example.
 *
 * Copyright (C) 2012 Stefan Wendler <sw@kaltpost.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/******************************************************************************
 * Hardware UART example for MSP430.
 *
 * Stefan Wendler
 * sw@kaltpost.de
 * http://gpio.kaltpost.de
 ******************************************************************************/

#include <msp430.h>

#include "ws2812.h"
#include "uart.h"

/**
 * Receive Data (RXD) at P1.1
 */
#define RXD		BIT1

/**
 * Transmit Data (TXD) at P1.2
 */
#define TXD		BIT2

/**
 * Callback handler for receive
 */
volatile unsigned int count =0;
volatile unsigned int ledCount =0;
volatile unsigned int stripCount =1;

void (*uart_rx_isr_ptr)(unsigned char c);

void uart_init(void)
{
	uart_set_rx_isr_ptr(0L);
	P1SEL  = RXD + TXD;
  	P1SEL2 = RXD + TXD;
  	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  	UCA0BR0 = 0x82;                            // 1MHz 9600
  	UCA0BR1 = 0x06;                              // 1MHz 9600
  	UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
  	UCA0CTL1 &= ~UCSWRST;                     // Initialize USCI state machine
  	IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
}

void uart_set_rx_isr_ptr(void (*isr_ptr)(unsigned char c))
{
	uart_rx_isr_ptr = isr_ptr;
}

unsigned char uart_getc()
{
    while (!(IFG2&UCA0RXIFG));// USCI_A0 RX buffer ready?
    /*
    if(UCA0RXBUF == 0xFF)
    {
    	//UCA0RXBUF
		count = 0;
		ledCount = 0;
		stripCount = 0;
		fillStrip(  0x00, 0x00, 0xFF);
	    showStrip();
    }
    else
    {
		 if (count == 0)
		{
			 fillStrip(  0x00, 0xFF, 0x00);
			 	showStrip();
			setRColor( ledCount, UCA0RXBUF);
			count ++;
		}
		else if (count == 1)
		{
			fillStrip(  0xFF, 0x00, 0x00);
				showStrip();
			setGColor( ledCount, UCA0RXBUF);
			count ++;
		}
		else if (count == 2)
		{
			fillStrip(  0xFF, 0x00, 0xFF);
				showStrip();
			setBColor( ledCount, UCA0RXBUF);
			count = 0;
			ledCount ++;
			if(ledCount == 5)
			{
				ledCount =0;
				stripCount ++;
				if(stripCount == 6)
				{
					//showStrip();
				}

			}
		}
    }
    */
    return UCA0RXBUF;
}

void uart_putc(unsigned char c)
{
	while (!(IFG2&UCA0TXIFG));              // USCI_A0 TX buffer ready?
	__bic_SR_register(GIE);
    if(c == 0xFF)
    {
		count = 0;
		stripCount = 0;
		//fillStrip(  0x00, 0x00, 0xFF);
	    //showStrip();
    }
    else
    {
		 if (count == 0)
		{
			setRColor( stripCount, c);
			count ++;
		}
		else if (count == 1)
		{
			setGColor( stripCount, c);
			count ++;
		}
		else if (count == 2)
		{
			setBColor(stripCount, c);

			stripCount++;
			if(stripCount == 6)
			{
				showStrip();
				stripCount=0;
			}

			count = 0;
		}
    }
    UCA0TXBUF = c;
    __bis_SR_register(GIE);
}

void uart_puts(const char *str)
{
     while(*str) uart_putc(*str++);
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	if(uart_rx_isr_ptr != 0L) {
		(uart_rx_isr_ptr)(UCA0RXBUF);
	}
}
