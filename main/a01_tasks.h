/*
 * a01_tasks.h
 * ENB350 - A01
 * n8890897 - Daniel Harrison
 * n9190325 - Matthew West
 * n9190007 - Jake Bradford
 * n8872970 - Drew Baker
 */

/* >>>>>>>>>> Replaces the while loop in main() <<<<<<<<<< */
void task_loop(UArg a0, UArg a1) {
	while(1) {
		WidgetMessageQueueProcess();
		if(repaintWidgets){
			WidgetPaint(WIDGET_ROOT);
			repaintWidgets = false;
		}

		Task_sleep(50);
	}
}


/* >>>>>>>>>> Checks if station is clear. <<<<<<<<<< */
void task_isStationClear(UArg arg0, UArg arg1) {
	while(1){
		//Read port M, Pin 1
		int32_t pinread = GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_1);
		if(pinread!=0){
			stationIsClear = false;
			QUT_UART_Send( (uint8_t *)"OBSTRUCTION\r\n", 13 );

		} else stationIsClear = true;


		Task_sleep(10);
	}
}

/* >>>>>>>>>> Updates input display <<<<<<<<<< */
void task_updateInputDisplay(UArg arg0, UArg arg1) {
	while(1){
		updateInputDisplay();
		updateStatisticsDisplay();
		Task_sleep(300);
	}
}

/* >>>>>>>>>> Runs station automatically <<<<<<<<<< */
void task_automateStation(UArg arg0, UArg arg1) {
	while(true) {
		// Check station is enabled
		if(stationEnabled && stationIsClear && automationEnabled) {

			// Check a workpiece is available
			int32_t pinread = GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_3);

			// Workpiece is available
			if(pinread>0){

				// Check workpiece colour
				bool pieceCorrectColour = isPieceCorrectColour();
				bool pieceWithinThreshold = false;

				//If correct colour
				if(pieceCorrectColour) {
					// Lift up
					output_cylUp();
					Task_sleep(1500);

					// check workpiece size
					pieceWithinThreshold = isPieceWithinThreshold(adcRead());

					if (pieceWithinThreshold) {
						//eject cylinder
						qut_set_gpio(2, 1);
						pinread = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6);

						//Wait until ejector is all the way out
						while(pinread>0){
							pinread = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6);
							if(!pinread>0) break;
						}

						//Turn on air slider
						qut_set_gpio(3, 1);
						isAirSliderInUse = true;

						//Put delay here
						Task_sleep(1000);

						// Turn off air slider
						qut_set_gpio(3, 0);
						isAirSliderInUse = false;

						//Reset station
						output_returnToInitialPosition(false);

						FestoStation.accepted++;
					} else {
						output_cylDown();
						output_ejectAndRetractCylinder();

						FestoStation.rejected++;
					}

				} else {
					output_ejectAndRetractCylinder();
					FestoStation.rejected++;
				}

			}//workpiece available
		} //stationEnabled
		Task_sleep(500);
	}
}



