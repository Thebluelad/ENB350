/*
 * a01_setup.h
 * ENB350 - A01
 * n8890897 - Daniel Harrison
 * n9190325 - Matthew West
 * n9190007 - Jake Bradford
 * n8872970 - Drew Baker
 */


/* >>>>>>>>>> INCLUDES <<<<<<<<<< */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "inc/hw_memmap.h"
#include "inc/tm4c129xnczad.h"
#include "inc/hw_hibernate.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"

#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "driverlib/hibernate.h"

#include "utils/uartstdio.h"
#include "utils/ustdlib.h"

#include "grlib/grlib.h"
#include "grlib/widget.h"
#include "grlib/canvas.h"
#include "grlib/pushbutton.h"
#include "grlib/container.h"

#include "drivers/frame.h"
#include "drivers/kentec320x240x16_ssd2119.h"
#include "drivers/pinout.h"
#include "drivers/touch.h"

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <xdc/cfg/global.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Mailbox.h>

#include "qut_tiva.h"

/* >>>>>>>>>> The error routine that is called if the driver library encounters an error. <<<<<<<<<< */
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif


/* >>>>>>>>>> MACROS <<<<<<<<<< */
#define ADC_SEQ_NUM	0


//Output Button positons
#define OUTPUT_SPACING_Y	25
#define OUTPUT_HEIGHT 30
#define OUTPUT_WIDTH 62
#define LOC_X_OUTPUTS 	20
#define LOC_X_OUTPUTS_RIGHT (LOC_X_OUTPUTS + 48)
#define LOC_Y_OUTPUT0 	95
#define LOC_Y_OUTPUT1 	LOC_Y_OUTPUT0+OUTPUT_SPACING_Y
#define LOC_Y_OUTPUT2 	LOC_Y_OUTPUT1+OUTPUT_SPACING_Y
#define LOC_Y_OUTPUT3 	LOC_Y_OUTPUT2+OUTPUT_SPACING_Y

//Input display positions
#define INPUT_SPACING_Y	15
#define LOC_X_INPUTS 	170
#define LOC_Y_INPUT0 	130
#define LOC_Y_INPUT1 	LOC_Y_INPUT0+INPUT_SPACING_Y
#define LOC_Y_INPUT2 	LOC_Y_INPUT1+INPUT_SPACING_Y
#define LOC_Y_INPUT4 	LOC_Y_INPUT2+INPUT_SPACING_Y
#define LOC_Y_INPUT5 	LOC_Y_INPUT4+INPUT_SPACING_Y
#define LOC_Y_INPUT6 	LOC_Y_INPUT5+INPUT_SPACING_Y
#define LOC_Y_INPUT7 	LOC_Y_INPUT6+INPUT_SPACING_Y

//Workstation statistics positions
#define STATS_SPACING_Y 15
#define LOC_X_STATS 	20
#define LOC_X_STATS2 	170
#define LOC_Y_STATS0 	30
#define LOC_Y_STATS1 	LOC_Y_STATS0 + STATS_SPACING_Y
#define LOC_Y_STATS2 	LOC_Y_STATS1 + STATS_SPACING_Y
#define LOC_Y_STATS3 	LOC_Y_STATS0
#define LOC_Y_STATS4 	LOC_Y_STATS1
#define LOC_Y_STATS5 	LOC_Y_STATS2

/* >>>>>>>>>> Setup struct for counting workpieces <<<<<<<<<< */
typedef struct FestoStationTracker {
	uint8_t accepted, rejected, orange, black, metallic;
}FestoStationTracker;

FestoStationTracker FestoStation;


/* >>>>>>>>>> GLOBALS <<<<<<<<<< */

uint32_t ui32SysClock;
tContext sContext;

// if the safety light sensor is blocked or not.
bool stationIsClear = true;

// main loops checks if this is true, and then repaints. to stop flickering
bool repaintWidgets = false;

// if air slider is in use.. No pin read for this
bool isAirSliderInUse = false;

// if station is enabled or not
bool stationEnabled = false;

// if automation is enabled or not
bool automationEnabled = false;

// if thresholds have been set
bool thresholdsSet = false;

// lower threshold limit for pieces
uint32_t lowerThreshold = 0;

// upper threshold limit for pieces
uint32_t upperThreshold = 0;

// time structure
struct tm sTime;


/* >>>>>>>>>> Forward reference to various widgets. <<<<<<<<<< */
extern tCanvasWidget screen_main;
extern tPushButtonWidget button_cylDown; //cyl down
extern tPushButtonWidget button_cylUp; //cyl up
extern tPushButtonWidget button_cylEject; //cyl eject
extern tPushButtonWidget button_airSlider; // air slider
extern tPushButtonWidget button_enableStation; // enable / Disable station
extern tPushButtonWidget button_enableAutomation; // enable / Disable automation
extern tPushButtonWidget button_thresholdMeasure; // enable / Disable automation
extern tPushButtonWidget button_returnToInitialPosition; // enable / Disable station

extern tContainerWidget container_acceptedCount;
extern tContainerWidget container_rejectedCount;
extern tContainerWidget container_throughput;
extern tContainerWidget container_orangeCount;
extern tContainerWidget container_blackCount;
extern tContainerWidget container_metallicCount;


/* >>>>>>>>>> Setup buffers for GUI printing <<<<<<<<<< */
char acceptCountBuff[3];
char rejectCountBuff[3];
char throughputBuff[3];
char orangeCountBuff[3];
char blackCountBuff[3];
char metallicCountBuff[3];


/* >>>>>>>>>> Standard Functions <<<<<<<<<< */
void setup_screen_main(tWidget *psWidget, tContext *psContext);
void setup_tasks(void);
void initialise_time(uint8_t day, uint8_t mon, uint32_t year, uint8_t hour, uint8_t min, uint8_t sec);


/* >>>>>>>>>> Output functions <<<<<<<<<< */
void output_cylDown(void);
void output_cylUp(void);
void output_returnToInitialPosition(bool disableStation);
void output_measurePiecesThreshold();
void output_ejectAndRetractCylinder();


/* >>>>>>>>>> Automation helper methods <<<<<<<<<< */
bool isPieceWithinThreshold(uint32_t pieceSizeMM);
bool isPieceCorrectColour();
void enableAutomation();
void disableAutomation();
void pendingAutomation();


/* >>>>>>>>>> Button press methods <<<<<<<<<< */
void buttonPress_cylDown(tWidget *psWidget); //cyl down
void buttonPress_cylUp(tWidget *psWidget); //cyl up
void buttonPress_cylEject(tWidget *psWidget); //cyl eject
void buttonPress_airSlider(tWidget *psWidget); // air slider
void buttonPress_enableStation(tWidget *psWidget); // enable disable station
void buttonPress_enableAutomation(tWidget *psWidget); // enable disable automation
void buttonPress_thresholdMeasure(tWidget *psWidget); // run pieces threshold measurement
void buttonPress_returnToInitialPosition(tWidget *psWidget); // enable disable station


/* >>>>>>>>>> Read functions <<<<<<<<<< */
void updateInputDisplay();
void updateStatisticsDisplay();
uint32_t adcRead();


/* >>>>>>>>>> Tasks <<<<<<<<<< */
void task_loop(UArg a0, UArg a1);
void task_isStationClear(UArg a0, UArg a1);
void task_updateInputDisplay(UArg arg0, UArg arg1);
void task_automateStation(UArg arg0, UArg arg1);


/* >>>>>>>>>> Declare widgets <<<<<<<<<< */
//main screen canvas
Canvas (
	screen_main, WIDGET_ROOT, 0, 0,
	&g_sKentec320x240x16_SSD2119, 10, 25, 300, (240 - 25 -10),
	CANVAS_STYLE_APP_DRAWN, 0, 0, 0, 0, 0, 0, setup_screen_main
);

//button_cylDown - Lifting cylinder down
RectangularButton	(
	button_cylDown, &screen_main, 0, 0, &g_sKentec320x240x16_SSD2119,
	LOC_X_OUTPUTS, LOC_Y_OUTPUT0, OUTPUT_WIDTH, OUTPUT_HEIGHT, //x,y, width, height
	(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
	ClrGray, ClrDarkGray, ClrWhite, ClrWhite,
	g_psFontCmss12b, "Down", 0, 0, 0, 0, buttonPress_cylDown
);

//button_cylUp - Lifting cylinder up
RectangularButton	(
	button_cylUp, &screen_main, 0, 0, &g_sKentec320x240x16_SSD2119,
	LOC_X_OUTPUTS + LOC_X_OUTPUTS_RIGHT, LOC_Y_OUTPUT0, OUTPUT_WIDTH, OUTPUT_HEIGHT, //x,y, width, height
	(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
	ClrGray, ClrDarkGray, ClrWhite, ClrWhite,
	g_psFontCmss12b, "Up", 0, 0, 0, 0, buttonPress_cylUp
);

//button_cylEject - Eject cylinder
RectangularButton	(
	button_cylEject, &screen_main, 0, 0, &g_sKentec320x240x16_SSD2119,
	LOC_X_OUTPUTS, LOC_Y_OUTPUT0+35, OUTPUT_WIDTH, OUTPUT_HEIGHT, //x,y, width, height
	(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
	ClrGray, ClrDarkGray, ClrWhite, ClrWhite,
	g_psFontCmss12b, "Eject", 0, 0, 0, 0, buttonPress_cylEject
);

//button_airSlider - Air slider
RectangularButton	(
	button_airSlider, &screen_main, 0, 0, &g_sKentec320x240x16_SSD2119,
	LOC_X_OUTPUTS + LOC_X_OUTPUTS_RIGHT, LOC_Y_OUTPUT0+35, OUTPUT_WIDTH, OUTPUT_HEIGHT, //x,y, width, height
	(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
	ClrGray, ClrDarkGray, ClrWhite, ClrWhite,
	g_psFontCmss12b, "Air", 0, 0, 0, 0, buttonPress_airSlider
);

//Return to initial position
CircularButton	(
	button_returnToInitialPosition, &screen_main, 0, 0, &g_sKentec320x240x16_SSD2119,
	296, 37, 13, //x,y,radius (screen resolution: 320x240)
	(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
	ClrGray, ClrDarkGray, ClrWhite, ClrWhite,
	g_psFontCmss16b, "R", 0, 0, 0, 0, buttonPress_returnToInitialPosition
);

//Enable disable station
RectangularButton	(
	button_enableStation, &screen_main, 0, 0, &g_sKentec320x240x16_SSD2119,
	LOC_X_OUTPUTS, LOC_Y_OUTPUT0+70, 130, OUTPUT_HEIGHT, //x,y, width, height
	(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
	ClrGreen, ClrDarkGreen, ClrWhite, ClrWhite,
	g_psFontCmss16b, "Enable Station", 0, 0, 0, 0, buttonPress_enableStation
);

//Enable disable automation
RectangularButton	(
	button_enableAutomation, &screen_main, 0, 0, &g_sKentec320x240x16_SSD2119,
	LOC_X_OUTPUTS, LOC_Y_OUTPUT0+105, 62, OUTPUT_HEIGHT, //x,y, width, height
	(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
	ClrRed, ClrRed, ClrWhite, ClrWhite,
	g_psFontCmss16b, "Locked", 0, 0, 0, 0, buttonPress_enableAutomation
);

//Run threshold measurement
RectangularButton	(
	button_thresholdMeasure, &screen_main, 0, 0, &g_sKentec320x240x16_SSD2119,
	LOC_X_OUTPUTS + 67, LOC_Y_OUTPUT0+105, 62, OUTPUT_HEIGHT, //x,y, width, height
	(PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY),
	ClrGreen, ClrDarkGreen, ClrWhite, ClrWhite,
	g_psFontCmss12b, "Calibrate", 0, 0, 0, 0, buttonPress_thresholdMeasure
);

Container			(container_acceptedCount, &screen_main, 0, 0, &g_sKentec320x240x16_SSD2119, LOC_X_STATS + 90, LOC_Y_STATS0,
        20, 20, (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY), ClrBlack,
		ClrBlack, ClrWhite, g_psFontCm12, acceptCountBuff);

Container			(container_rejectedCount, &screen_main, 0, 0, &g_sKentec320x240x16_SSD2119, LOC_X_STATS + 90, LOC_Y_STATS1,
        20, 20, (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY), ClrBlack,
		ClrBlack, ClrWhite, g_psFontCm12, rejectCountBuff);

Container			(container_throughput, &screen_main, 0, 0, &g_sKentec320x240x16_SSD2119, LOC_X_STATS + 90, LOC_Y_STATS2,
        20, 20, (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY), ClrBlack,
		ClrBlack, ClrWhite, g_psFontCm12, throughputBuff);

Container			(container_orangeCount, &screen_main, 0, 0, &g_sKentec320x240x16_SSD2119, LOC_X_STATS2 + 80, LOC_Y_STATS3,
        20, 20, (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY), ClrBlack,
		ClrBlack, ClrWhite, g_psFontCm12, orangeCountBuff);

Container			(container_blackCount, &screen_main, 0, 0, &g_sKentec320x240x16_SSD2119, LOC_X_STATS2 + 80, LOC_Y_STATS4,
        20, 20, (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY), ClrBlack,
		ClrBlack, ClrWhite, g_psFontCm12, blackCountBuff);

Container			(container_metallicCount, &screen_main, 0, 0, &g_sKentec320x240x16_SSD2119, LOC_X_STATS2 + 80, LOC_Y_STATS5,
        20, 20, (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_STYLE_FILL | PB_STYLE_RELEASE_NOTIFY), ClrBlack,
		ClrBlack, ClrWhite, g_psFontCm12, metallicCountBuff);

/* >>>>>>>>>> Setup functions <<<<<<<<<< */

//Setup the main screen
void setup_screen_main(tWidget *psWidget, tContext *psContext) {

	GrContextFontSet( psContext, g_psFontCm16);
	GrContextForegroundSet( psContext, ClrSilver);

	//Add widgets to screen main
	WidgetAdd((tWidget *)&screen_main, (tWidget *)&button_cylDown);
	WidgetAdd((tWidget *)&screen_main, (tWidget *)&button_cylUp);
	WidgetAdd((tWidget *)&screen_main, (tWidget *)&button_cylEject);
	WidgetAdd((tWidget *)&screen_main, (tWidget *)&button_airSlider);
	WidgetAdd((tWidget *)&screen_main, (tWidget *)&button_enableStation);
	WidgetAdd((tWidget *)&screen_main, (tWidget *)&button_enableAutomation);
	WidgetAdd((tWidget *)&screen_main, (tWidget *)&button_thresholdMeasure);
	WidgetAdd((tWidget *)&screen_main, (tWidget *)&button_returnToInitialPosition);

	WidgetAdd((tWidget *)&screen_main, (tWidget *)&container_acceptedCount);
	WidgetAdd((tWidget *)&screen_main, (tWidget *)&container_rejectedCount);
	WidgetAdd((tWidget *)&screen_main, (tWidget *)&container_throughput);
	WidgetAdd((tWidget *)&screen_main, (tWidget *)&container_orangeCount);
	WidgetAdd((tWidget *)&screen_main, (tWidget *)&container_blackCount);
	WidgetAdd((tWidget *)&screen_main, (tWidget *)&container_metallicCount);


	GrContextForegroundSet( psContext, ClrWhite);
	GrContextFontSet( psContext, g_psFontCm12);
	GrStringDraw(psContext, "Workpiece available", 			-1, LOC_X_INPUTS+15, LOC_Y_INPUT0-5, 0);
	GrStringDraw(psContext, "Workpiece not black", 			-1, LOC_X_INPUTS+15, LOC_Y_INPUT1-5, 0);
	GrStringDraw(psContext, "Station is clear", 			-1, LOC_X_INPUTS+15, LOC_Y_INPUT2-5, 0);
	GrStringDraw(psContext, "Lift cyl raised", 				-1, LOC_X_INPUTS+15, LOC_Y_INPUT4-5, 0);
	GrStringDraw(psContext, "Lift cyl lowered", 			-1, LOC_X_INPUTS+15, LOC_Y_INPUT5-5, 0);
	GrStringDraw(psContext, "Eject cyl retracted", 			-1, LOC_X_INPUTS+15, LOC_Y_INPUT6-5, 0);
	GrStringDraw(psContext, "Downstream st free", 			-1, LOC_X_INPUTS+15, LOC_Y_INPUT7-5, 0);

	// Display workpiece statistics
	GrStringDraw(psContext, "Accepted pieces", 				-1, LOC_X_STATS, LOC_Y_STATS0, 0);
	GrStringDraw(psContext, "Rejected pieces", 				-1, LOC_X_STATS, LOC_Y_STATS1, 0);
	GrStringDraw(psContext, "Throughput", 					-1, LOC_X_STATS, LOC_Y_STATS2, 0);
	GrStringDraw(psContext, "Orange pieces", 				-1, LOC_X_STATS2, LOC_Y_STATS3, 0);
	GrStringDraw(psContext, "Black pieces", 				-1, LOC_X_STATS2, LOC_Y_STATS4, 0);
	GrStringDraw(psContext, "Metallic", 					-1, LOC_X_STATS2, LOC_Y_STATS5, 0);
}

// Setup tasks
void setup_tasks(void) {

	Error_Block eb;

	//setup task_loop
	Task_Handle tLoop;
	Error_init(&eb);
	Task_Params tLoop_params;
	Task_Params_init(&tLoop_params);
	tLoop_params.priority = 2; //needs to take precedance above all else
	tLoop = Task_create(task_loop, NULL, &eb);
	if (tLoop == NULL) {
		System_printf("Task_create() failed!\n");
		BIOS_exit(0);
	}

	//setup task isStationClear
	Task_Handle tStationClear;
	Task_Params tStationClear_params;
	Task_Params_init(&tStationClear_params);
	tStationClear_params.priority = 1; //needs to take precedance above all else
	Error_init(&eb);
	tStationClear = Task_create(task_isStationClear, &tStationClear_params, &eb);
	if (tStationClear == NULL) {
		QUT_UART_Send( (uint8_t *)"TASK_FAILED\r\n", 15 );
		BIOS_exit(0);
	}

	//setup task UpdateInputDisplay
	Task_Handle tUpdateInputDisplay;
	Task_Params tUpdateInputDisplay_params;
	Task_Params_init(&tUpdateInputDisplay_params);
	tUpdateInputDisplay_params.priority = 3; //needs to take precedance above all else
	Error_init(&eb);
	tUpdateInputDisplay = Task_create(task_updateInputDisplay, &tUpdateInputDisplay_params, &eb);
	if (tUpdateInputDisplay == NULL) {
		QUT_UART_Send( (uint8_t *)"TASK_FAILED\r\n", 15 );
		BIOS_exit(0);
	}

	//setup task AutomateStation
	Task_Handle tAutomateStation;
	Task_Params tAutomateStation_params;
	Task_Params_init(&tAutomateStation_params);
	tAutomateStation_params.priority = 4; //needs to take precedance above all else
	Error_init(&eb);
	tAutomateStation = Task_create(task_automateStation, &tAutomateStation_params, &eb);
	if (tAutomateStation == NULL) {
		QUT_UART_Send( (uint8_t *)"TASK_FAILED\r\n", 15 );
		BIOS_exit(0);
	}

}

// Setup workpiece tracking
void setup_festoStationTracker() {
	FestoStation.accepted = 0;
	FestoStation.rejected = 0;
	FestoStation.orange = 0;
	FestoStation.black = 0;
	FestoStation.metallic = 0;
}

// Initialise default time
void initialise_time(uint8_t day, uint8_t mon, uint32_t year, uint8_t hour, uint8_t min, uint8_t sec) {
	sTime.tm_mday = day;
	sTime.tm_mon = mon - 1;
	sTime.tm_year = year - 1900;
	sTime.tm_hour = hour;
	sTime.tm_min = min;
	sTime.tm_sec = sec;
}
