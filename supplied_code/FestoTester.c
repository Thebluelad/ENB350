//*****************************************************************************
//
// FestoTester.c
//
// Copyright (c) 2013 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.0.1.11577 of the DK-TM4C129X Firmware Package.
//
//*****************************************************************************

#define ADC_SEQ_NUM	0

//Drawing defines
#define SPACING_X	38

#define LOC_X_0	27
#define LOC_X_1	LOC_X_0+SPACING_X
#define LOC_X_2	LOC_X_1+SPACING_X
#define LOC_X_3	LOC_X_2+SPACING_X
#define LOC_X_4	LOC_X_3+SPACING_X
#define LOC_X_5	LOC_X_4+SPACING_X
#define LOC_X_6	LOC_X_5+SPACING_X
#define LOC_X_7	LOC_X_6+SPACING_X

#define LOC_Y_0UTPUTS	 80
#define LOC_Y_INPUTS	160
#define LOC_Y_ANALOG	220

#define INPUT_STATUS_IS_ONE	1


#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/tm4c129xnczad.h"

#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

#include "utils/uartstdio.h"

#include "grlib/grlib.h"
#include "grlib/widget.h"
#include "grlib/canvas.h"
#include "grlib/pushbutton.h"

#include "drivers/frame.h"
#include "drivers/kentec320x240x16_ssd2119.h"
#include "drivers/pinout.h"
#include "drivers/touch.h"


#include "qut_tiva.h"



uint32_t input_status[8];

uint32_t adc0_read;
uint32_t num_analog_pixels = 0;

//*****************************************************************************
//
// Forward reference to various widget structures.
//
//*****************************************************************************
extern tCanvasWidget g_sBackground;
extern tPushButtonWidget g_sPushBtn_0;
extern tPushButtonWidget g_sPushBtn_1;
extern tPushButtonWidget g_sPushBtn_2;
extern tPushButtonWidget g_sPushBtn_3;
extern tPushButtonWidget g_sPushBtn_4;
extern tPushButtonWidget g_sPushBtn_5;
extern tPushButtonWidget g_sPushBtn_6;
extern tPushButtonWidget g_sPushBtn_7;

//*****************************************************************************
//
// Forward declarations for the globals required to define the widgets at
// compile-time.
//
//*****************************************************************************
void OnIntroPaint(tWidget *psWidget, tContext *psContext);

//*****************************************************************************
//
// Forward reference to the button press handler.
//
//*****************************************************************************
void OnButtonPress_0	(tWidget *psWidget);
void OnButtonPress_1	(tWidget *psWidget);
void OnButtonPress_2	(tWidget *psWidget);
void OnButtonPress_3	(tWidget *psWidget);
void OnButtonPress_4	(tWidget *psWidget);
void OnButtonPress_5	(tWidget *psWidget);
void OnButtonPress_6	(tWidget *psWidget);
void OnButtonPress_7	(tWidget *psWidget);

//*****************************************************************************
//
// The canvas widget acting as the background to the display.
//
//*****************************************************************************
Canvas(g_sBackground, WIDGET_ROOT, 0, 0,//&g_sPushBtn_0,
       &g_sKentec320x240x16_SSD2119, 10, 25, 300, (240 - 25 -10),
       CANVAS_STYLE_APP_DRAWN, 0, 0, 0, 0, 0, 0, OnIntroPaint);


//*****************************************************************************
//
// Handles paint requests for the introduction canvas widget.
//
//*****************************************************************************
void
OnIntroPaint(tWidget *psWidget, tContext *psContext)
{
	tRectangle sRect;

	//
    // Display the introduction text in the canvas.
    //
    GrContextFontSet		( psContext, g_psFontCm16);
    GrContextForegroundSet	( psContext, ClrSilver);

    GrStringDraw(psContext, "OUTPUTS", 	-1, 125, LOC_Y_0UTPUTS-50, 0);
    GrStringDraw(psContext, "0", 		-1, LOC_X_0-4, LOC_Y_0UTPUTS-35, 0);
    GrStringDraw(psContext, "1", 		-1, LOC_X_1-4, LOC_Y_0UTPUTS-35, 0);
    GrStringDraw(psContext, "2", 		-1, LOC_X_2-4, LOC_Y_0UTPUTS-35, 0);
    GrStringDraw(psContext, "3", 		-1, LOC_X_3-4, LOC_Y_0UTPUTS-35, 0);
    GrStringDraw(psContext, "4", 		-1, LOC_X_4-4, LOC_Y_0UTPUTS-35, 0);
    GrStringDraw(psContext, "5", 		-1, LOC_X_5-4, LOC_Y_0UTPUTS-35, 0);
    GrStringDraw(psContext, "6", 		-1, LOC_X_6-4, LOC_Y_0UTPUTS-35, 0);
    GrStringDraw(psContext, "7", 		-1, LOC_X_7-4, LOC_Y_0UTPUTS-35, 0);

    WidgetAdd((tWidget *)&g_sBackground, (tWidget *)&g_sPushBtn_0);
    WidgetAdd((tWidget *)&g_sBackground, (tWidget *)&g_sPushBtn_1);
    WidgetAdd((tWidget *)&g_sBackground, (tWidget *)&g_sPushBtn_2);
    WidgetAdd((tWidget *)&g_sBackground, (tWidget *)&g_sPushBtn_3);
    WidgetAdd((tWidget *)&g_sBackground, (tWidget *)&g_sPushBtn_4);
    WidgetAdd((tWidget *)&g_sBackground, (tWidget *)&g_sPushBtn_5);
    WidgetAdd((tWidget *)&g_sBackground, (tWidget *)&g_sPushBtn_6);
    WidgetAdd((tWidget *)&g_sBackground, (tWidget *)&g_sPushBtn_7);


	GrStringDraw(psContext, "INPUTS", 	-1, 130, LOC_Y_INPUTS-50, 0);
    GrStringDraw(psContext, "0", 		-1, LOC_X_0-4, LOC_Y_INPUTS-35, 0);
    GrStringDraw(psContext, "1", 		-1, LOC_X_1-4, LOC_Y_INPUTS-35, 0);
    GrStringDraw(psContext, "2", 		-1, LOC_X_2-4, LOC_Y_INPUTS-35, 0);
    GrStringDraw(psContext, "3", 		-1, LOC_X_3-4, LOC_Y_INPUTS-35, 0);
    GrStringDraw(psContext, "4", 		-1, LOC_X_4-4, LOC_Y_INPUTS-35, 0);
    GrStringDraw(psContext, "5", 		-1, LOC_X_5-4, LOC_Y_INPUTS-35, 0);
    GrStringDraw(psContext, "6", 		-1, LOC_X_6-4, LOC_Y_INPUTS-35, 0);
    GrStringDraw(psContext, "7", 		-1, LOC_X_7-4, LOC_Y_INPUTS-35, 0);

	//Draw all INPUT status circles
	//TBD Cant get a loop to work for this for some reason
	GrContextForegroundSet( psContext, ClrCyan);
    if ( input_status[0] == INPUT_STATUS_IS_ONE ){
    	GrContextForegroundSet( psContext, ClrRed);
    }
	GrCircleFill( psContext, LOC_X_0, LOC_Y_INPUTS, 15);

	GrContextForegroundSet( psContext, ClrCyan);
    if ( input_status[1] == INPUT_STATUS_IS_ONE ){
    	GrContextForegroundSet( psContext, ClrRed);
    }
	GrCircleFill( psContext, LOC_X_1, LOC_Y_INPUTS, 15);

	GrContextForegroundSet( psContext, ClrCyan);
    if ( input_status[2] == INPUT_STATUS_IS_ONE ){
    	GrContextForegroundSet( psContext, ClrRed);
    }
	GrCircleFill( psContext, LOC_X_2, LOC_Y_INPUTS, 15);

	GrContextForegroundSet( psContext, ClrCyan);
    if ( input_status[3] == INPUT_STATUS_IS_ONE ){
    	GrContextForegroundSet( psContext, ClrRed);
    }
	GrCircleFill( psContext, LOC_X_3, LOC_Y_INPUTS, 15);

	GrContextForegroundSet( psContext, ClrCyan);
    if ( input_status[4] == INPUT_STATUS_IS_ONE ){
    	GrContextForegroundSet( psContext, ClrRed);
    }
	GrCircleFill( psContext, LOC_X_4, LOC_Y_INPUTS, 15);

	GrContextForegroundSet( psContext, ClrCyan);
    if ( input_status[5] == INPUT_STATUS_IS_ONE ){
    	GrContextForegroundSet( psContext, ClrRed);
    }
	GrCircleFill( psContext, LOC_X_5, LOC_Y_INPUTS, 15);

	GrContextForegroundSet( psContext, ClrCyan);
    if ( input_status[6] == INPUT_STATUS_IS_ONE ){
    	GrContextForegroundSet( psContext, ClrRed);
    }
	GrCircleFill( psContext, LOC_X_6, LOC_Y_INPUTS, 15);

	GrContextForegroundSet( psContext, ClrCyan);
    if ( input_status[7] == INPUT_STATUS_IS_ONE ){
    	GrContextForegroundSet( psContext, ClrRed);
    }
	GrCircleFill( psContext, LOC_X_7, LOC_Y_INPUTS, 15);


	GrContextForegroundSet	( psContext, ClrSilver);
	GrStringDraw(psContext, "ANALOG", 	-1, 130, LOC_Y_ANALOG-30, 0);

	//Draw two rectangles, one filled left to right up to the analog value then an empty one to contain the information
    GrContextForegroundSet(psContext, ClrMidnightBlue);
    sRect.i16XMin = 20;
	sRect.i16XMax = 300;
	sRect.i16YMin = LOC_Y_ANALOG-10;
	sRect.i16YMax = LOC_Y_ANALOG+8;
    GrRectFill(psContext, &sRect);

    GrContextForegroundSet(psContext, ClrCyan);
	sRect.i16XMin = 20;
    sRect.i16XMax = num_analog_pixels + sRect.i16XMin;
	sRect.i16YMin = LOC_Y_ANALOG-10;
	sRect.i16YMax = LOC_Y_ANALOG+8;
    GrRectFill(psContext, &sRect);





}

//*****************************************************************************
//
// Define the buttons that trigger the OUTPUTS
//
//*****************************************************************************
CircularButton	(	g_sPushBtn_0, &g_sBackground, 0, 0, &g_sKentec320x240x16_SSD2119,
					LOC_X_0, LOC_Y_0UTPUTS, 15,																//x,y,radius
					(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT |
					PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
					ClrDarkBlue, ClrBlue, ClrWhite, ClrWhite,
					g_psFontCmss22b, "0", 0, 0, 0, 0, OnButtonPress_0 );

CircularButton	(	g_sPushBtn_1, &g_sBackground, 0, 0, &g_sKentec320x240x16_SSD2119,
					LOC_X_1, LOC_Y_0UTPUTS, 15,																//x,y,radius
					(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT |
					PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
					ClrDarkBlue, ClrBlue, ClrWhite, ClrWhite,
					g_psFontCmss22b, "0", 0, 0, 0, 0, OnButtonPress_1 );

CircularButton	(	g_sPushBtn_2, &g_sBackground, 0, 0, &g_sKentec320x240x16_SSD2119,
					LOC_X_2, LOC_Y_0UTPUTS, 15,															//x,y,radius
					(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT |
					PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
					ClrDarkBlue, ClrBlue, ClrWhite, ClrWhite,
					g_psFontCmss22b, "0", 0, 0, 0, 0, OnButtonPress_2 );

CircularButton	(	g_sPushBtn_3, &g_sBackground, 0, 0, &g_sKentec320x240x16_SSD2119,
					LOC_X_3, LOC_Y_0UTPUTS, 15,															//x,y,radius
					(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT |
					PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
					ClrDarkBlue, ClrBlue, ClrWhite, ClrWhite,
					g_psFontCmss22b, "0", 0, 0, 0, 0, OnButtonPress_3 );

CircularButton	(	g_sPushBtn_4, &g_sBackground, 0, 0, &g_sKentec320x240x16_SSD2119,
					LOC_X_4, LOC_Y_0UTPUTS, 15,															//x,y,radius
					(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT |
					PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
					ClrDarkBlue, ClrBlue, ClrWhite, ClrWhite,
					g_psFontCmss22b, "0", 0, 0, 0, 0, OnButtonPress_4 );

CircularButton	(	g_sPushBtn_5, &g_sBackground, 0, 0, &g_sKentec320x240x16_SSD2119,
					LOC_X_5, LOC_Y_0UTPUTS, 15,															//x,y,radius
					(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT |
					PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
					ClrDarkBlue, ClrBlue, ClrWhite, ClrWhite,
					g_psFontCmss22b, "0", 0, 0, 0, 0, OnButtonPress_5 );

CircularButton	(	g_sPushBtn_6, &g_sBackground, 0, 0, &g_sKentec320x240x16_SSD2119,
					LOC_X_6, LOC_Y_0UTPUTS, 15,															//x,y,radius
					(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT |
					PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
					ClrDarkBlue, ClrBlue, ClrWhite, ClrWhite,
					g_psFontCmss22b, "0", 0, 0, 0, 0, OnButtonPress_6 );

CircularButton	(	g_sPushBtn_7, &g_sBackground, 0, 0, &g_sKentec320x240x16_SSD2119,
					LOC_X_7, LOC_Y_0UTPUTS, 15,															//x,y,radius
					(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT |
					PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
					ClrDarkBlue, ClrBlue, ClrWhite, ClrWhite,
					g_psFontCmss22b, "0", 0, 0, 0, 0, OnButtonPress_7 );



//*****************************************************************************
//
// A global we use to keep track of whether or not the OUTPUT is enabled or not
//
//*****************************************************************************
bool g_bHelloVisible_0 	= false;
bool g_bHelloVisible_1 	= false;
bool g_bHelloVisible_2 	= false;
bool g_bHelloVisible_3 	= false;
bool g_bHelloVisible_4 	= false;
bool g_bHelloVisible_5 	= false;
bool g_bHelloVisible_6 	= false;
bool g_bHelloVisible_7 	= false;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
//
// Function call when OUTPUT buttons are pressed
//
//*****************************************************************************
void OnButtonPress_0(tWidget *psWidget)
{
    g_bHelloVisible_0 = !g_bHelloVisible_0;

    if(g_bHelloVisible_0)
    {
        PushButtonTextSet(&g_sPushBtn_0, "1");
        WidgetPaint(WIDGET_ROOT);
		qut_set_gpio( 0, 1 );
    }
    else
    {
		PushButtonTextSet(&g_sPushBtn_0, "0");
        WidgetPaint(WIDGET_ROOT);
		qut_set_gpio( 0, 0 );
    }
}

void OnButtonPress_1 (tWidget *psWidget)
{
    g_bHelloVisible_1 = !g_bHelloVisible_1;

    if(g_bHelloVisible_1)
    {
        PushButtonTextSet(&g_sPushBtn_1, "1");

        WidgetPaint(WIDGET_ROOT);

		qut_set_gpio( 1, 1 );
    }
    else
    {
        PushButtonTextSet(&g_sPushBtn_1, "0");

        WidgetPaint(WIDGET_ROOT);

		qut_set_gpio( 1, 0 );
    }
}

void OnButtonPress_2 (tWidget *psWidget)
{
    g_bHelloVisible_2 = !g_bHelloVisible_2;

    if(g_bHelloVisible_2)
    {
        PushButtonTextSet(&g_sPushBtn_2, "1");

        WidgetPaint(WIDGET_ROOT);

		qut_set_gpio( 2, 1 );
    }
    else
    {
        PushButtonTextSet(&g_sPushBtn_2, "0");

        WidgetPaint(WIDGET_ROOT);

		qut_set_gpio( 2, 0 );
    }
}

void OnButtonPress_3 (tWidget *psWidget)
{
    g_bHelloVisible_3 = !g_bHelloVisible_3;

    if(g_bHelloVisible_3)
    {
        PushButtonTextSet(&g_sPushBtn_3, "1");

        WidgetPaint(WIDGET_ROOT);

		qut_set_gpio( 3, 1 );
    }
    else
    {
        PushButtonTextSet(&g_sPushBtn_3, "0");

        WidgetPaint(WIDGET_ROOT);

		qut_set_gpio( 3, 0 );
    }
}
void OnButtonPress_4(tWidget *psWidget)
{
    g_bHelloVisible_4 = !g_bHelloVisible_4;

    if(g_bHelloVisible_4)
    {
        PushButtonTextSet(&g_sPushBtn_4, "1");
        WidgetPaint(WIDGET_ROOT);
		qut_set_gpio( 4, 1 );
    }
    else
    {
		PushButtonTextSet(&g_sPushBtn_4, "0");
        WidgetPaint(WIDGET_ROOT);
		qut_set_gpio( 4, 0 );
    }
}

void OnButtonPress_5 (tWidget *psWidget)
{
    g_bHelloVisible_5 = !g_bHelloVisible_5;

    if(g_bHelloVisible_5)
    {
        PushButtonTextSet(&g_sPushBtn_5, "1");

        WidgetPaint(WIDGET_ROOT);

		qut_set_gpio( 5, 1 );
    }
    else
    {
        PushButtonTextSet(&g_sPushBtn_5, "0");

        WidgetPaint(WIDGET_ROOT);

		qut_set_gpio( 5, 0 );
    }
}

void OnButtonPress_6 (tWidget *psWidget)
{
    g_bHelloVisible_6 = !g_bHelloVisible_6;

    if(g_bHelloVisible_6)
    {
        PushButtonTextSet(&g_sPushBtn_6, "1");

        WidgetPaint(WIDGET_ROOT);

		qut_set_gpio( 6, 1 );
    }
    else
    {
        PushButtonTextSet(&g_sPushBtn_6, "0");

        WidgetPaint(WIDGET_ROOT);

		qut_set_gpio( 6, 0 );
    }
}

void OnButtonPress_7 (tWidget *psWidget)
{
    g_bHelloVisible_7 = !g_bHelloVisible_7;

    if(g_bHelloVisible_7)
    {
        PushButtonTextSet(&g_sPushBtn_7, "1");

        WidgetPaint(WIDGET_ROOT);

		qut_set_gpio( 7, 1 );
    }
    else
    {
        PushButtonTextSet(&g_sPushBtn_7, "0");

        WidgetPaint(WIDGET_ROOT);

		qut_set_gpio( 7, 0 );
    }
}

//*****************************************************************************
//
// Print "Hello World!" to the display on the Intelligent Display Module.
//
//*****************************************************************************
int
main(void)
{
    tContext 	sContext;
    uint32_t 	ui32SysClock;
    uint32_t 	i;
    uint32_t 	reg_read;

    //
    // Run from the PLL at 120 MHz.
    //
/*
    ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                       SYSCTL_SYSDIV_10  |		//Needed for ADC
                                       SYSCTL_OSC_MAIN   |
                                       SYSCTL_USE_PLL    |
                                       SYSCTL_CFG_VCO_480), 120000000);
*/

    ui32SysClock = SysCtlClockFreqSet(( SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_25MHZ), 120000000);


    //
    // Configure the device pins.
    //
    PinoutSet();

    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_1);	//OUT 0 L1
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_0);	//OUT 1 L0
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_2);	//OUT 2 L2
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_3);	//OUT 3 L3
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_4);	//OUT 4 L4
    GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, GPIO_PIN_5);	//OUT 5 L5
    GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_5);	//OUT 6 P5
    GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE, GPIO_PIN_4);	//OUT 7 P4

    GPIOPinTypeGPIOInput (GPIO_PORTM_BASE, GPIO_PIN_3);	//IN  0 M3
    GPIOPinTypeGPIOInput (GPIO_PORTM_BASE, GPIO_PIN_2);	//IN  1 M2
    GPIOPinTypeGPIOInput (GPIO_PORTM_BASE, GPIO_PIN_1);	//IN  2 M1
    GPIOPinTypeGPIOInput (GPIO_PORTM_BASE, GPIO_PIN_0);	//IN  3 M0
    GPIOPinTypeGPIOInput (GPIO_PORTN_BASE, GPIO_PIN_4);	//IN  4 N4
    GPIOPinTypeGPIOInput (GPIO_PORTA_BASE, GPIO_PIN_7);	//IN  5 A7
    GPIOPinTypeGPIOInput (GPIO_PORTC_BASE, GPIO_PIN_6);	//IN  6 C6
    GPIOPinTypeGPIOInput (GPIO_PORTC_BASE, GPIO_PIN_5);	//IN  7 C5

    //RGB LED
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_5);	//RED 	N5
    GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_7);	//GREEN Q7
    GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE, GPIO_PIN_4);	//BLUE 	Q4

    //Initialize the UART
    	QUT_UART_Init( ui32SysClock );


    //Initialize AIN0
    	QUT_ADC0_Init();


    //
    // Initialize the display driver.
    //
    Kentec320x240x16_SSD2119Init(ui32SysClock);

    //
    // Initialize the graphics context.
    //
    GrContextInit(&sContext, &g_sKentec320x240x16_SSD2119);

    //
    // Draw the application frame.
    //
    FrameDraw(&sContext, "FestoTester");

    //
    // Initialize the touch screen driver.
    //
    TouchScreenInit(ui32SysClock);

    //
    // Set the touch screen event handler.
    //
    TouchScreenCallbackSet(WidgetPointerMessage);

    //
    // Add the compile-time defined widgets to the widget tree.
    //
    WidgetAdd(WIDGET_ROOT, (tWidget *)&g_sBackground);

    //
    // Paint the widget tree to make sure they all appear on the display.
    //
    WidgetPaint(WIDGET_ROOT);

    QUT_UART_Send( (uint8_t *)"FestoTester", 11 );

    //
    // Loop forever, processing widget messages.
    //
    while(1)
    {
        //
        // Process any messages from or for the widgets.
        //
        WidgetMessageQueueProcess();


        //Turn on RED LED
        GPIO_PORTN_DATA_R |= 0x20;

    	//Check GPIO Inputs
    	for( i = 0; i < 8; i++ )
    	{
    		input_status[i] = 0;
    		reg_read		= qut_get_gpio( i );

			if ( reg_read != 0 ){
				input_status[i] = INPUT_STATUS_IS_ONE;
			}
    	}


    	//Read the ADC0
    	adc0_read = QUT_ADC0_Read();

        QUT_UART_Send( (uint8_t *)"\n\radc0_read=", 12 );
        QUT_UART_Send_uint32_t( adc0_read );

        //Relimit the ADC read from 0 to 4096 into a pixel limit from 0 to 280
        num_analog_pixels = (adc0_read * 280 ) / 4096;





        //UARTprintf("num_analog_pixels = %4d\r", num_analog_pixels );

        //QUT_UART_Send( (uint8_t *)"\rnum_analog_pixels=", 19 );
        //QUT_UART_Send_uint32_t( num_analog_pixels );



		//qut_delay_secs(1);


		//Repaint the screen
    	WidgetPaint(WIDGET_ROOT);
    }
}
