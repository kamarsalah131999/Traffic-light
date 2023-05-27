/*
 * trafic light.c
 *
 * Created: 5/27/2023 4:04:34 AM
 * Author : kamar salah
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"
#include "LCD driver.h"
#include "led.h"
#define F_CPU 8000000UL
#include <util/delay.h>

volatile unsigned char counter=0;
 unsigned char counter_green=10;
 unsigned char counter_yellow=5; 
 unsigned char counter_red=7;

int main(void)
{
	led_vinit ('D', 0 );                                                //green led
	led_vinit ('D', 1 );                                               //yellow led
	led_vinit ('D', 2 );                                              //red led
	LCD_vinit ();
	timer_CTC_vinit_interrupt();
    
    while (1) 
    {
	   counter_green=10;
       counter_yellow=5; 
       counter_red=7;
	   LCD_vclear_screen ();
	   LCD_vsend_sring ("remaning 10 sec");
	   led_vturnon ('D', 0);
	   
	   while (counter_green>0)
	   {
		   if (counter>=100)                                    
		   {
			   counter=0;
			   counter_green--;
			   LCD_vmove_cursor (1,11);
			   LCD_vsend_char (' ');
			   LCD_vsend_char (counter_green+48);
		   }
	   }
	   
	   _delay_ms(500);
	   led_vturnoff ('D', 0);
	   led_vturnon ('D', 1);
	   LCD_vclear_screen ();
	   LCD_vsend_sring ("remaning 5 sec");
	   while (counter_yellow>0)
	   {
		   if (counter>=100)                                    
		   {
			   counter=0;
			   counter_yellow--;
			   LCD_vmove_cursor (1,11);
			   LCD_vsend_char (' ');
			   LCD_vsend_char (counter_yellow+48);
		   }
	   }
	   
	   _delay_ms(500);
	   led_vturnoff ('D', 1);
	   led_vturnon ('D', 2);
	   LCD_vclear_screen ();
	   LCD_vsend_sring ("remaning 7 sec");
	   while (counter_red>0)
	   {
		   if (counter>=100)                                    
		   {
			   counter=0;
			   counter_red--;
			   LCD_vmove_cursor (1,11);
			   LCD_vsend_char (' ');
			   LCD_vsend_char (counter_red+48);
		   }
	   }
	   
	   
  }
}

ISR(TIMER0_COMP_vect)
{
	counter++;
}

