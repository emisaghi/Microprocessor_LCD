/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
© Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Microprocessor
Version : 
Date    : 6/6/2013
Author  : Ehsan Misaghi
Company : 8933002
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega16.h>

#include <delay.h>

// Alphanumeric LCD Module functions
#include <alcd.h>
#include <stdio.h>
#include <stdlib.h>
unsigned int step = 0x10;
#define ADC_VREF_TYPE 0x00

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}

void stepper(char a)
{
 switch (a){
 case '-':
 {
 lcd_gotoxy(0,1);
        if (TCCR1B<0x04)
        {
        TCCR1B=TCCR1B+1;
        }
        else
        {
        lcd_clear();
        lcd_gotoxy(0,1);
        lcd_puts("Minimum Speed!");
        };
        break;
 }
 case '+':  
 {
 lcd_gotoxy(0,1);
        if (TCCR1B>0x02)
        {
        TCCR1B=TCCR1B-1;  
        } 
        else
        {
        lcd_clear();
        lcd_gotoxy(0,1);
        lcd_puts("Maximum Speed!");
        };   
        break;
 }        
 };
 
}
 
// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
// Place your code here
PORTB=step;
step=step>>1;
if (PORTB.4==1)
{
step=0x80;
}; 
}


 // External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
// Place your code here
lcd_clear();
lcd_gotoxy(0,1);
//first column
        PORTC = 0xEF;   //1110 1111
        delay_ms(20);
        if (!(PINC & 0x01))
        {        
        lcd_puts("7 is pressed");
        delay_ms(500);
        };
        if (!(PINC & 0x02))
        {
        lcd_puts("4 is pressed");
        delay_ms(500);
        };
        if (!(PINC & 0x04))
        {
        lcd_puts("1 is pressed");
        delay_ms(500);
        };
        if (!(PINC & 0x08))
        {
        delay_ms(500);
        };
                              
        //second column
        PORTC =0xDF;   //1101 1111;
        delay_ms(20);
        if (!(PINC & 0x01))
        {
        lcd_puts("8 is pressed");
        delay_ms(500);
        };
        if (!(PINC & 0x02))
        {
        lcd_puts("5 is pressed");
        delay_ms(500);
        };
        if (!(PINC & 0x04))
        {
        lcd_puts("2 is pressed");
        delay_ms(500);
        };
        if (!(PINC & 0x08))
        {
        lcd_puts("0 is pressed");
        delay_ms(500);
        };
                               
        //third column
        PORTC = 0xBF;   //1011 1111;
        delay_ms(20);
        if (!(PINC & 0x01))
        {
        lcd_puts("9 is pressed");
        delay_ms(500);
        };
        if (!(PINC & 0x02))
        {
        lcd_puts("6 is pressed");
        delay_ms(500);
        };
        if (!(PINC & 0x04))
        {
        lcd_puts("3 is pressed");
        delay_ms(500);
        };
        if (!(PINC & 0x08))
        {
        lcd_puts("Not Used!");
        delay_ms(500);
        };

        //fourth column
        PORTC = 0x7F;    //0111 1111;
        delay_ms(20);
        if (!(PINC & 0x01))
        {
        lcd_puts("Not Used!");
        delay_ms(500);
        };
        if (!(PINC & 0x02))
        {
        lcd_puts("Not Used!");
        delay_ms(500);
        };
        if (!(PINC & 0x04))
        {
        stepper('-');
        delay_ms(250);
        };  
        if (!(PINC & 0x08))
        {
        stepper('+');
        delay_ms(250);
        };    
        PORTC=0x0F;  

}
// External Interrupt 2 service routine
interrupt [EXT_INT2] void ext_int2_isr(void)
{
// Place your code here
char str[20];
sprintf(str, " Ehsan Misaghi ");
lcd_clear();
lcd_gotoxy(0,0);
lcd_puts(str);
sprintf(str, "    8933002    ");
lcd_gotoxy(0,1);
lcd_puts(str);
delay_ms(4000);                        
}


// Declare your global variables here
unsigned int t=100;
void main(void)
{
// Declare your local variables here
char lcd[20];
// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=T State2=T State1=T State0=0 
PORTB=0x00;
DDRB=0xF1;

// Port C initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=In
// State7=0 State6=0 State5=0 State4=0 State3=P State2=P State1=P State0=P 
PORTC=0x0F;
DDRC=0xF0;

// Port D initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=In Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=P State2=0 State1=0 State0=0 
PORTD=0x08;
DDRD=0xF7;

//Stepper Motor Normal Speed (2.09712 seconds)

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 31.250 kHz
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x03;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;



// External Interrupt(s) initialization
// INT0: Off
// INT1: On
// INT1 Mode: Any change
// INT2: On
// INT2 Mode: Falling Edge
GICR|=0xA0;
MCUCR=0x04;
MCUCSR=0x00;
GIFR=0xA0;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x04;
              
// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC Clock frequency: 1000.000 kHz
// ADC Voltage Reference: AREF pin
// ADC Auto Trigger Source: ADC Stopped
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x83;


// Global enable interrupts
#asm("sei")

// Alphanumeric LCD initialization
// Connections specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTD Bit 0
// RD - PORTD Bit 1
// EN - PORTD Bit 2
// D4 - PORTD Bit 4
// D5 - PORTD Bit 5
// D6 - PORTD Bit 6
// D7 - PORTD Bit 7
// Characters/line: 16
lcd_init(16);
while (1)
      {
      // Place your code here        
      lcd_clear();
      lcd_gotoxy(0,1);            
      switch (TCCR1B){
      case 0x02:
      lcd_puts("Motor Speed: Max");
      break;
      case 0x03:
      lcd_puts("Motor Speed: Avg");
      break;
      case 0x04:
      lcd_puts("Motor Speed: Min");
      };     
      t=read_adc(0)/2.05;                 //(5*100/1023) = 2.05           
      sprintf(lcd,"Temp = %u \xdfC",t); 
      lcd_gotoxy(0,0);
      lcd_puts(lcd);
      if (t>100) {
      PORTB.0=1;
    }
      else  {
      PORTB.0=0;    
    };
      delay_ms(200);
      }
}