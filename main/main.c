/*
 * main.c
 * ENB350 - A01
 * n8890897 - Daniel Harrison
 * n9190325 - Matthew West
 * n9190007 - Jake Bradford
 * n8872970 - Drew Baker
 */


/* >>>>>>>>>> INCLUDES <<<<<<<<<< */
#include "a01_setup.h"
#include "a01_output_functions.h"
#include "a01_read_functions.h"
#include "a01_tasks.h"

/* >>>>>>>>>> main <<<<<<<<<< */
int main(void) {
	//Setup Tasks
	setup_tasks();
	setup_festoStationTracker();

	//Configure sys clock
	ui32SysClock = 120000000;

	// Configure the device pins.
	PinoutSet();

	//Configure GPIO OUT (BUTTON PRESS COMMANDS)
	GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_1);	//L1 - Lifting cylinder down	- Output0
	GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_0);	//L0 - Lifting cylinder up 	- Output1
	GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_2);	//L2 - Eject Cylinder Extend	- Output2
	GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_3);	//L3 - Air slider on 		- Output3
	GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_4);	//OUT 4 L4
	GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_5);	//OUT 5 L5
	GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_5);	//OUT 6 P5
	GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_4);	//P4 - Station occupied

	//Configure GPIO IN (SENSORS / DATA READ OUT)
	GPIOPinTypeGPIOInput (GPIO_PORTM_BASE, GPIO_PIN_3);	//M3 - Workpiece available
	GPIOPinTypeGPIOInput (GPIO_PORTM_BASE, GPIO_PIN_2);	//M2 - Workpiece not black
	GPIOPinTypeGPIOInput (GPIO_PORTM_BASE, GPIO_PIN_1);	//M1 - Safety Light Barrier
	GPIOPinTypeGPIOInput (GPIO_PORTM_BASE, GPIO_PIN_0);	//IN  3 M0
	GPIOPinTypeGPIOInput (GPIO_PORTN_BASE, GPIO_PIN_4);	//N4 - Lifting cylinder raised
	GPIOPinTypeGPIOInput (GPIO_PORTA_BASE, GPIO_PIN_7);	//A7 - Lifting cylinder lowered
	GPIOPinTypeGPIOInput (GPIO_PORTC_BASE, GPIO_PIN_6);	//C6 - Eject Cylinder retracted
	GPIOPinTypeGPIOInput (GPIO_PORTC_BASE, GPIO_PIN_5);	//C5 - Downstream station free

	//Configure USER LED
	GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_5);	//RED 	N5
	GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_7);	//GREEN Q7
	GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_4);	//BLUE 	Q4

	//Configure USER BUTTONS
	GPIOPinTypeGPIOInput(GPIO_PORTP_BASE, GPIO_PIN_1);	//SELECT P1
	GPIOPinTypeGPIOInput(GPIO_PORTN_BASE, GPIO_PIN_3);	//UP N3
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_5);	//DOWN E5

	//Initialize the UART and send initial message
	QUT_UART_Init( ui32SysClock );
	QUT_UART_Send( (uint8_t *)"FestoTester", 11 );

	//Initialize AIN0
	QUT_ADC0_Init();

	// Initialize the display driver.
	Kentec320x240x16_SSD2119Init(ui32SysClock);

	// Initialize the graphics context.
	GrContextInit(&sContext, &g_sKentec320x240x16_SSD2119);

	// Draw the application frame.
	FrameDraw(&sContext, "FestoTester");

	// Initialize the touch screen driver.
	TouchScreenInit(ui32SysClock);

	// Set the touch screen event handler.
	TouchScreenCallbackSet(/*TouchCallback*/WidgetPointerMessage);
	TouchScreenIntHandler();

	// Add the compile-time defined widgets to the widget tree.
	WidgetAdd(WIDGET_ROOT, (tWidget *)&screen_main);

	// Paint the widget tree to make sure they all appear on the display.
	WidgetPaint(WIDGET_ROOT);

	// Enable processor interrupts.
	IntMasterEnable();

	// Enable hibernate module
	SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_HIBERNATE)){}

	// Set default time and date
	initialise_time(25, 5, 2016, 5, 0, 0); // day, month, year, hour, min, second

	// Initialise time and date
	HibernateEnableExpClk(ui32SysClock);
	HibernateRTCEnable();
	HibernateCounterMode(HIBERNATE_COUNTER_24HR);
	HibernateCalendarSet(&sTime);
	HibernateCalendarGet(&sTime);

	//Turn on red LED and set stationEnabled = false
	GPIO_PORTN_DATA_R |= 0x20; // red led, turn on
	GPIO_PORTQ_DATA_R &= ~(0x80); // green led, turn off
	stationEnabled = false;

	updateInputDisplay();

	BIOS_start();

	return 0;
}

