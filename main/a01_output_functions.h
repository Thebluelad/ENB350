/* 
 * a01_output_functions.h
 * ENB350 - A01
 * n8890897 - Daniel Harrison
 * n9190325 - Matthew West
 * n9190007 - Jake Bradford
 * n8872970 - Drew Baker
 */

/* >>>>>>>>>> Move cyl platform down.  Once down, turn off air <<<<<<<<<< */
void output_cylDown(void){
	if(stationIsClear && stationEnabled){
		//Read port A, Pin 7 - Lift cyl lowered
		int32_t pinread = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_7);

		//Move down
		if(!pinread>0){
			//Move platform down
			qut_set_gpio(0, 1);
			PushButtonFillColorSet(&button_cylDown, ClrOrange);
			PushButtonFillColorPressedSet(&button_cylDown, ClrDarkOrange);
			repaintWidgets = true;
		}

		//Check if platform is down.. then turn off air.
		pinread = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_7);
		while(!pinread>0){
			pinread = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_7);
			if(pinread>0) break;
		}

		//Stop lowering
		qut_set_gpio(0, 0);
		PushButtonFillColorSet(&button_cylDown, ClrGray);
		PushButtonFillColorPressedSet(&button_cylDown, ClrDarkGray);
		repaintWidgets = true;
	}
}


/* >>>>>>>>>> Move cyl platform up.  Once up, turn off air <<<<<<<<<< */
void output_cylUp(void){
	if(stationIsClear && stationEnabled){
		//Read port A, Pin 7 - Lift cyl lowered
		int32_t pinread = GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_4);

		//Move Up
		if(!pinread>0){
			//Move platform Up
			qut_set_gpio(1, 1);
			PushButtonFillColorSet(&button_cylUp, ClrOrange);
			PushButtonFillColorPressedSet(&button_cylUp, ClrDarkOrange);
			repaintWidgets = true;
		}

		//Check if platform is Up.. then turn off air.
		pinread = GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_4);
		while(!pinread>0){
			pinread = GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_4);
			if(pinread>0) break;
		}

		//Stop going up
		qut_set_gpio(1, 0);
		PushButtonFillColorSet(&button_cylUp, ClrGray);
		PushButtonFillColorPressedSet(&button_cylUp, ClrDarkGray);
		repaintWidgets = true;
	}
}


/* >>>>>>>>>> L1 : Lift cyl down : output0 <<<<<<<<<< */
void buttonPress_cylDown(tWidget *psWidget) {
	output_cylDown();
}


/* >>>>>>>>>> L1 : Lift cyl up : output1 <<<<<<<<<< */
void buttonPress_cylUp(tWidget *psWidget) {
	output_cylUp();
}


/* >>>>>>>>>> L2 : Eject cylinder : output2 <<<<<<<<<< */
void buttonPress_cylEject(tWidget *psWidget) {
	if(stationIsClear && stationEnabled){
		//Read port C, Pin 6 - Is eject.  >0 = no
		int32_t pinread = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6);

		//Eject
		if(pinread>0){
			PushButtonFillColorSet(&button_cylEject, ClrOrange);
			PushButtonFillColorPressedSet(&button_cylEject, ClrDarkOrange);
			qut_set_gpio(2, 1);
		} else {
		//Stop eject
			PushButtonFillColorSet(&button_cylEject, ClrGray);
			PushButtonFillColorPressedSet(&button_cylEject, ClrDarkGray);
			qut_set_gpio(2, 0);
		}

		repaintWidgets = true;
	}
}


/* >>>>>>>>>> L0 : Lift cyl up : output1 <<<<<<<<<< */
void buttonPress_airSlider(tWidget *psWidget) {
	if(stationIsClear && stationEnabled){

		//Air
		if(!isAirSliderInUse){
			PushButtonFillColorSet(&button_airSlider, ClrOrange);
			PushButtonFillColorPressedSet(&button_airSlider, ClrDarkOrange);
			qut_set_gpio(3, 1);
			isAirSliderInUse = true;
		} else {
		//Stop air
			PushButtonFillColorSet(&button_airSlider, ClrGray);
			PushButtonFillColorPressedSet(&button_airSlider, ClrDarkGray);
			qut_set_gpio(3, 0);
			isAirSliderInUse = false;
		}

		repaintWidgets = true;
	}
}

/* >>>>>>>>>> Enable / disable station <<<<<<<<<< */
void buttonPress_enableStation(tWidget *psWidget) {

	if(stationEnabled) {
		GPIO_PORTN_DATA_R |= 0x20; // red led, turn on
		GPIO_PORTQ_DATA_R &= ~(0x80); // green led, turn off
		stationEnabled = false;

		//set button_enableStation to green
		PushButtonTextSet(&button_enableStation, "Enable Station");
		PushButtonFillColorSet(&button_enableStation, ClrGreen);
		PushButtonFillColorPressedSet(&button_enableStation, ClrDarkGreen);

		disableAutomation();
	} else {
		GPIO_PORTN_DATA_R &= ~(0x20); // red led, turn off
		GPIO_PORTQ_DATA_R |= 0x80; // green led, turn on
		stationEnabled = true;

		//set button_enableStation to red
		PushButtonTextSet(&button_enableStation, "Disable Station");
		PushButtonFillColorSet(&button_enableStation, ClrRed);
		PushButtonFillColorPressedSet(&button_enableStation, ClrRed);

		pendingAutomation();
	}

	repaintWidgets = true;
}

/* >>>>>>>>>> Enable / disable automation <<<<<<<<<< */
void buttonPress_enableAutomation(tWidget *psWidget) {
	/* >> Button colour states <<
	 * Red: 	Station is disabled. 	Automation cannot be enabled.
	 * Orange: 	Station is enabled. 	Automation is awaiting to be enabled.
	 * Green: 	Station is enabled. 	Automation is enabled.
	 */

	if (stationEnabled) {
		if(!automationEnabled && thresholdsSet) {
			enableAutomation();
		} else {
			pendingAutomation();
		}
	}

	repaintWidgets = true;
}

/* >>>>>>>>>> Start automation <<<<<<<<<< */
void enableAutomation() {
	automationEnabled = true;

	//set button_enableAutomation to green
	PushButtonTextSet(&button_enableAutomation, "Running");
	PushButtonFillColorSet(&button_enableAutomation, ClrGreen);
	PushButtonFillColorPressedSet(&button_enableAutomation, ClrDarkGreen);
}

/* >>>>>>>>>> Fully disable automation but leave station enabled <<<<<<<<<< */
void disableAutomation() {
	automationEnabled = false;

	//set button_enableAutomation to red
	PushButtonTextSet(&button_enableAutomation, "Locked");
	PushButtonFillColorSet(&button_enableAutomation, ClrRed);
	PushButtonFillColorPressedSet(&button_enableAutomation, ClrRed);
}

/* >>>>>>>>>> Set automation into awaiting-enable mode <<<<<<<<<< */
void pendingAutomation() {
	automationEnabled = false;
	//set button_enableAutomation to orange
	PushButtonTextSet(&button_enableAutomation, "Pending");
	PushButtonFillColorSet(&button_enableAutomation, ClrOrange);
	PushButtonFillColorPressedSet(&button_enableAutomation, ClrOrangeRed);
}

/* >>>>>>>>>> Button press - Return station to initial position <<<<<<<<<< */
void buttonPress_returnToInitialPosition(tWidget *psWidget) {
	output_returnToInitialPosition(true);
}

/* >>>>>>>>>> Semi-automate the threshold measurements <<<<<<<<<< */
void buttonPress_thresholdMeasure(tWidget *psWidget) {
	if (stationEnabled && stationIsClear && !thresholdsSet) {
		output_measurePiecesThreshold();
	}
}

/* >>>>>>>>>> Return station to initial position <<<<<<<<<< */
void output_returnToInitialPosition(bool disableStation) {

	//Turn off air slider
	if(isAirSliderInUse){
		PushButtonFillColorSet(&button_airSlider, ClrGray);
		PushButtonFillColorPressedSet(&button_airSlider, ClrDarkGray);
		qut_set_gpio(3, 0);
		isAirSliderInUse = false;
	}

	//Retract ejector
	int32_t pinread = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6);
	//
	if(!pinread>0){
		qut_set_gpio(2, 0);
		while(pinread>0){
			pinread = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6);
		}
	}
	PushButtonFillColorSet(&button_cylEject, ClrGray);
	PushButtonFillColorPressedSet(&button_cylEject, ClrDarkGray);

	//Move cyl down
	output_cylDown();

	if(disableStation){
		//Disable station.
		GPIO_PORTN_DATA_R |= 0x20; // red led, turn on
		GPIO_PORTQ_DATA_R &= ~(0x80); // green led, turn off
		stationEnabled = false;
		//set button_enableStation to green
		PushButtonTextSet(&button_enableStation, "Enable Station");
		PushButtonFillColorSet(&button_enableStation, ClrGreen);
		PushButtonFillColorPressedSet(&button_enableStation, ClrDarkGreen);
	}

	repaintWidgets = true;

}

/* >>>>>>>>>> Measures the thresholds of the workpieces <<<<<<<<<< */
void output_measurePiecesThreshold() {
	// Wait until small piece is placed
	int32_t pinread = 0;
	while (!(pinread > 0)) {
		 pinread = GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_3);
		 Task_sleep(20);
	}


	// Wait for station to be clear & move piece up
	while (!stationIsClear) {Task_sleep(20);}
	output_cylUp();

	// Measure piece
	Task_sleep(1500);
	lowerThreshold = adcRead();

	// Move piece down
	output_cylDown();

	// Eject piece
	output_ejectAndRetractCylinder();

	// Wait until piece is removed
	//pinread = GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_3);
	//while (pinread > 0) {
	//	 pinread = GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_3);
	//}

	// Wait until large piece is placed
	pinread = 0;
	while (!(pinread > 0)) {
		 pinread = GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_3);
		 Task_sleep(20);
	}

	// Wait for station to be clear & move piece up
	while (!stationIsClear) {Task_sleep(20);}
	output_cylUp();

	// Measure piece
	upperThreshold = adcRead();
	Task_sleep(1500);

	// Move piece down
	output_cylDown();

	// Eject piece
	output_ejectAndRetractCylinder();

	// finish up
	thresholdsSet = true;
	PushButtonTextSet(&button_thresholdMeasure, "Done");
	repaintWidgets = true;
	pendingAutomation();
}



void output_ejectAndRetractCylinder() {
	//eject cylinder
	qut_set_gpio(2, 1);
	int32_t pinread = pinread = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6);
	//Wait until ejector is all the way out
	while(pinread>0){
		pinread = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6);
		if(!pinread>0) break;
	}

	Task_sleep(500);

	//Retract cylinder
	qut_set_gpio(2, 0);
	pinread = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6);
	while(!pinread>0){
		pinread = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6);
		if(pinread>0) break;
	}
}
