#include <stm32f10x.h>

/* ADC programming steps
	1. Enable clock for ADC and GPIO pins
	2. Make this analog input pin
	3. Turn on ADC
	4. Select proper sample time
	5. Wait for 1 us
	6. Start conversion
	7. Wait for the conversion to complete
	8. Read digital sample value
	9. Repeat step 6 for another reading
*/

void init_adc1_pin(void){
	//ADC1 enable
	RCC->APB2ENR |= (1 << 9);
	//PA1=ADC1 input with pullup
	GPIOA->CRL &= ~((1 << 5)|(1 << 4));//input reset
	GPIOA->CRL &= ~((1 << 7)|(1 << 6));//input analog
}

void init_adc1(void){
	ADC1->CR2 |= (1 << 0); //Turn on
	ADC1->SMPR2 |= (1 << 3); //SMP1 = 001 Set sample time to 7.5
	ADC1->SQR3 |= 1; //channel 1 in regular sequence register 3
}

uint16_t adc1_read(void)
{
    ADC1->CR2 |= (1 << 22); // SWSTART
    while (!(ADC1->SR & (1 << 1))); // Wait for end of conversion
    return (uint16_t)ADC1->DR;
}