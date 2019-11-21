//*******************************************************//
//Ein Klatschen soll detektiert werden je nach Lautstärke//
//des Klatschens soll dann für 3sec ein Ton ausgegeben   //
//werden. Der Ton soll umso höher sein, je lauter geklatscht wird.//


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include "C:\Users\geozu\source\DriverLibHW\USART.h"
#include "C:\Users\geozu\source\DriverLibHW\ADC.h"
#include "C:\Users\geozu\source\DriverLibHW\Wait.h"


ISR(TIMER1_COMPA_vect)
{
	PORTA ^= (1 << 4); //Toggle Pin4 on PortA Arduino Pin26
}

void init();

void main()
{
	
	uint16_t loud;
	loud = ADCReadChannel(0);
	
	init();

}

void init()
{
	

	TCCR1A = 0;
	TCCR1B |= 1 << WGM12;
	TCCR1B |= 1 << CS11;
	TIMSK1 |= 1 << OCIE1A;

	OCR1A = 30000;


	

}
