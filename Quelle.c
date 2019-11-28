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
	int freq_val[12] = { 4000, 3800, 3600, 3400, 3200, 3000, 2800, 2600, 2400, 2200, 2000, 1800 };
	uint16_t ADC_data = 0;
	uint16_t BaseNoise;
	uint16_t IDKwhatNAMEforCOUNTERvar = 0;

	BaseNoise = ADCReadChannel(0);
	
	

	init();


	while (1)
	{
		ADC_data = ADCReadChannel(0);

		if (ADC_data < BaseNoise)
		{
			if (IDKwhatNAMEforCOUNTERvar < 12)
			{
				IDKwhatNAMEforCOUNTERvar++;
			}
			else if(IDKwhatNAMEforCOUNTERvar == 12)
			{
				IDKwhatNAMEforCOUNTERvar = 0;
			}

			OCR1A = freq_val[IDKwhatNAMEforCOUNTERvar];

			TIMSK1 |= (1 << OCIE1A);

			WaitMs(2000);
			TIMSK1 &= ~(1 << OCIE1A);

		}

		printf("%i\n", ADC_data);

		WaitMs(100);


	}

	

}

void init()
{
	

	TCCR1A = 0;
	TCCR1B |= 1 << WGM12;
	TCCR1B |= 1 << CS11;
	TIMSK1 |= 1 << OCIE1A;

	OCR1A = 0;
	TIMSK1 &= ~(1 << OCIE1A);
	sei();

	USART(0, 9600, 1, 0, 1, 0);

}
