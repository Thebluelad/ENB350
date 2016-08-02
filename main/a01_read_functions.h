/*
 * a01_read_functions.h
 * ENB350 - A01
 * n8890897 - Daniel Harrison
 * n9190325 - Matthew West
 * n9190007 - Jake Bradford
 * n8872970 - Drew Baker
 */

//Method headers
bool isBlack();
bool isMetallic();


uint32_t adc0_read;

/* >>>>>>>>>> Updates input graphics and flags <<<<<<<<<< */
void updateInputDisplay() {

	//M3 - Workpiece available
	int32_t pinread = GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_3);
	if(pinread>0){
		GrContextForegroundSet( &sContext, ClrGreen);
		GrCircleFill( &sContext, LOC_X_INPUTS, LOC_Y_INPUT0, 5);

		//M2 - Workpiece not black
		if(isBlack()){
			GrContextForegroundSet( &sContext, ClrGreen);
			GrCircleFill( &sContext, LOC_X_INPUTS, LOC_Y_INPUT1, 5);
		} else {
			GrContextForegroundSet( &sContext, ClrGray);
			GrCircleFill( &sContext, LOC_X_INPUTS, LOC_Y_INPUT1, 5);
		}

	} else {
		GrContextForegroundSet( &sContext, ClrGray);
		GrCircleFill( &sContext, LOC_X_INPUTS, LOC_Y_INPUT0, 5);
		GrCircleFill( &sContext, LOC_X_INPUTS, LOC_Y_INPUT1, 5); // workpiece not black
	}

	//Station is clear
	if(stationIsClear){
		GrContextForegroundSet( &sContext, ClrGreen);
		GrCircleFill( &sContext, LOC_X_INPUTS, LOC_Y_INPUT2, 5);
	} else {
		GrContextForegroundSet( &sContext, ClrGray);
		GrCircleFill( &sContext, LOC_X_INPUTS, LOC_Y_INPUT2, 5);
	}

	//Lift cyl raised
	pinread = GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_4);
	if(pinread>0){
		GrContextForegroundSet( &sContext, ClrGreen);
		GrCircleFill( &sContext, LOC_X_INPUTS, LOC_Y_INPUT4, 5);
	} else {
		GrContextForegroundSet( &sContext, ClrGray);
		GrCircleFill( &sContext, LOC_X_INPUTS, LOC_Y_INPUT4, 5);
	}

	//Lift cyl lowered
	pinread = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_7);
	if(pinread>0){
		GrContextForegroundSet( &sContext, ClrGreen);
		GrCircleFill( &sContext, LOC_X_INPUTS, LOC_Y_INPUT5, 5);
	} else {
		GrContextForegroundSet( &sContext, ClrGray);
		GrCircleFill( &sContext, LOC_X_INPUTS, LOC_Y_INPUT5, 5);
	}

	//Eject cyl retracted
	pinread = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6);
	if(pinread>0){
		GrContextForegroundSet( &sContext, ClrGreen);
		GrCircleFill( &sContext, LOC_X_INPUTS, LOC_Y_INPUT6, 5);
	} else {
		GrContextForegroundSet( &sContext, ClrGray);
		GrCircleFill( &sContext, LOC_X_INPUTS, LOC_Y_INPUT6, 5);
	}

	//Downstream station free
	GrContextForegroundSet( &sContext, ClrGray);
	GrCircleFill( &sContext, LOC_X_INPUTS, LOC_Y_INPUT7, 5);

	//Current date and time
	char time_buffer[50];
	HibernateCalendarGet(&sTime);
	sprintf(time_buffer, "%02d/%02d/%04d %02d:%02d:%02d", sTime.tm_mday, (sTime.tm_mon + 1), (sTime.tm_year + 1900), sTime.tm_hour, sTime.tm_min, sTime.tm_sec);
	GrStringDraw(&sContext, time_buffer, -1, 165, 105, 1);

	//Repaint
	repaintWidgets = true;

}

/* >>>>>>>>>> Updates stats display for workstation/workpiece info <<<<<<<<<< */
void updateStatisticsDisplay() {
	// Update buffers
	sprintf(acceptCountBuff, 	"%d", FestoStation.accepted);
	sprintf(rejectCountBuff, 	"%d", FestoStation.rejected);
	sprintf(throughputBuff, 	"%d", 0);
	sprintf(orangeCountBuff, 	"%d", FestoStation.orange);
	sprintf(blackCountBuff, 	"%d", FestoStation.black);
	sprintf(metallicCountBuff, 	"%d", FestoStation.metallic);

	repaintWidgets = true;
}

/* >>>>>>>>>> Indicates whether a workpiece is available <<<<<<<<<< */
bool workpieceAvailable() {
	int32_t pinread = GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_3);
	if(pinread>0) {
		return true;
	}
	return false;
}

bool isBlack() {
	int32_t pinread = GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_2);
	if (pinread >= 1) {
		FestoStation.black++;
		return true;
	}
	FestoStation.orange++;
	return false;
}

//Haven't implemented this yet either because not sure on the canvas objects to be implemented
bool isMetallic() {
	int32_t pinread = GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_0);
	if (pinread > 0) {
		FestoStation.metallic++;
		return true;
	}
	return false;
}

uint32_t adcRead() {
	uint32_t adc0_read = QUT_ADC0_Read();
	uint32_t adcReadmm = adc0_read / 78;
	//Small pieces range from about 1700-1800
	//Medium pieces range from about 1900-2000
	//Large pieces range from about 2100-2200
	return adcReadmm;
}

bool isPieceWithinThreshold(uint32_t pieceSizeMM) {
	// Check within threshold
	if (pieceSizeMM > lowerThreshold && pieceSizeMM < upperThreshold) {
		return true;
	}
	return false;
}

bool isPieceCorrectColour() {
	// check colour
	if (!isBlack() && !isMetallic()) {
		return true;
	}
	return false;
}
