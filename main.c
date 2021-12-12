#include  "fsl_device_registers.h"

void software_delay (unsigned long delay)  {
	while (delay > 0)
		delay--;
}

static unsigned long leftmotor = 0x06;
static unsigned long rightmotor = 0x05;
static unsigned long straight = 0x07;

//turnleft = 00000110 = 0x06
//turnright = 00000101 = 0x05
//straight = 00000111 = 0x07

int main (void) {

	//**********************************************************************************
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;	/*Enable  Port  D  Clock  Gate  Control */
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;	/*Enable  Port  A  Clock  Gate  Control */

	//**********************************************************************************
	//Port D Pins 0-7 for GPIO;
	PORTD_GPCLR = 0x00FF0100;
	//Port D Pins 0-7 for Output;
	GPIOD_PDDR |= 0x000000FF;

	//Port A Pin 1 and 2 for GPIO;
	PORTA_GPCLR = 0x00060100;
	//Port A Pin 1 and 2 for Input;
	GPIOA_PDDR &= 0xFFFFFFF9;


	//**********************************************************************************
	while (1) {
		long leftsensor = (GPIOA_PDIR & 4UL);
		//printf('%d',leftsensor);
		long rightsensor =(GPIOA_PDIR & 2UL);
		//printf('%d',rightsensor);

		if (leftsensor == 4 && rightsensor != 2) {
			GPIOD_PDOR = rightmotor;		//TURN RIGHT
		} else if (leftsensor != 4 && rightsensor == 2) {
			GPIOD_PDOR = leftmotor;			//TURN LEFT
		} else {
			GPIOD_PDOR = straight;
		}
	}
}


