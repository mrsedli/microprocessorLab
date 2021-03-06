/*******************************************************
Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 12.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>

// Declare your global variables here
static unsigned int time_count;
int active = -1; 
int dir = 0;

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    TCNT0 = 0x8B;
    ++time_count;           
    
    if (time_count == 50){
        PORTC.0 = !PORTC.0;
        
        if (dir!=0){
            if (dir==1 && active>=7)
                dir = -1;
            else if (dir==-1 && active<0)
                dir = 0;
        
            active += dir;
                                                   
            PORTB = (active<8 && active>=0)?(1 << active):0;   
        }
        
        time_count = 0;
    }
}

void main(void)
{

DDRA= 0;
DDRB= 0xFF;
DDRC= 1;

TCCR0= 5 ;
TCNT0= 0x8B;

TIMSK= 1;

#asm("sei")

while (1)
      {
        if (PINA.0)
            dir = 1;
      }
}
