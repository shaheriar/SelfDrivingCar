#include  "fsl_device_registers.h"

static unsigned long leftmotor = 0x06;
static unsigned long rightmotor = 0x05;
static unsigned long straight = 0x07;

int main (void) {

	//**********************************************************************************
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;	/*Enable  Port  D  Clock  Gate  Control */
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;	/*Enable  Port  A  Clock  Gate  Control */
	SIM_SCGC3 |= SIM_SCGC3_FTM3_MASK;

	PORTC_PCR10 = 0x300;	//FTM CHANNEL 6		-	RIGHT
	PORTC_PCR9 = 0x300;		//FTM CHANNEL 5		-	LEFT
	FTM3_MODE = 0x5;
	FTM3_MOD = 0xFFFF;
	FTM3_SC = 0x0E;

	//**********************************************************************************
	//Port D Pins 0-7 for GPIO;
	PORTD_GPCLR = 0x00FF0100;
	//Port D Pins 0-7 for Output;
	GPIOD_PDDR |= 0x000000FF;

	//PTC9 LEFT
	//PTC10 RIGHT

	while(1) {
		FTM3_C6SC = 0x4;	//RIGHT
		FTM3_C5SC = 0x4;	//LEFT
		GPIOD_PDOR = straight;			//ROBOT WILL KEEP GOING STRAIGHT AS LONG AS BOTH CHANNELS ARE 1
		while (!(FTM3_C6SC & 0x80)) {	//IF CHANNEL 6 IS 0, THERE IS AN OBSTACLE ON THE RIGHT
			GPIOD_PDOR = rightmotor;
		}
		FTM3_C6SC &= 0;
		while(!(FTM3_C5SC & 0x80)) {	//IF CHANNEL 5 IS 0, THERE IS AN OBSTACLE ON THE LEFT
			GPIOD_PDOR = leftmotor;
		}
		FTM3_C5SC &= 0;
	}
}


