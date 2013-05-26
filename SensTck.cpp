enum Sens_States {SENS_IDLE, SENS_SIDES_ON, SENS_SIDES_RD, SENS_FL_ON, SENS_FL_RD, SENS_FR_ON, SENS_FR_RD};
//Sens_Tck - 	controls the sensor modulation and assigns sensor values to memory.
//Writes To -	leftSensor 
//				rightSensor 
//				flSensor
//				frSensor
//				L_SENS_OUT
//				R_SENS_OUT
//				FL_SENS_OUT
//				FR_SENS_OUT
//Reads From -	L_SENS_RD
//				R_SENS_RD
//				FL_SENS_RD
//				FR_SENS_RD
//Complete? []
//Tested? []

/* declare sensor pins as DigitalOuts */
DigitalOut L_SENS_OUT(L_SENSOR_SUPPLY);
DigitalOut R_SENS_OUT(R_SENSOR_SUPPLY);
DigitalOut FL_SENS_OUT(FL_SENSOR_SUPPLY);
DigitalOut FR_SENS_OUT(FR_SENSOR_SUPPLY);

/* declare analog inputs from IR sensors */
AnalogIn L_SENS_RD(L_SENSOR_IN);
AnalogIn R_SENS_RD(R_SENSOR_IN);
AnalogIn FL_SENS_RD(FL_SENSOR_IN);
AnalogIn FR_SENS_RD(FR_SENSOR_IN);

int Sens_Tck(int state){
	switch (state){			//transitions
		case -1:
			state = SENS_IDLE;
			break;
		case SENS_IDLE:
			state = SENS_SIDES_ON;
			break;
		case SENS_SIDES_ON;
			state = SENS_SIDES_RD;
			break;
		case SENS_SIDES_RD:
			state = SENS_FL_ON;
			break;
		case SENS_FL_ON:
			state = SENS_FL_RD;
			break;
		case SENS_FL_RD;
			state = SENS_FR_ON;
			break;
		case SENS_FR_ON:
			state = SENS_FR_RD;
			break;
		case SENS_FR_RD:
			state = SENS_SIDES_ON;
			break;
		default:
			state = SENS_IDLE;
			break;
	}

	switch (state){			//actions
		case -1:
			break;
		case SENS_IDLE:
			break;
			
		case SENS_SIDES_ON:
			FR_SENS_OUT = 0;
			L_SENS_OUT = 1;
			R_SENS_OUT = 1;
			break;
		
		case SENS_SIDES_RD:
			leftSensor = L_SENS_RD;
			rightSensor = R_SENS_RD;
		break;
		
		case SENS_FL_ON:
			L_SENS_OUT = 0;
			R_SENS_OUT = 0;
			FL_SENS_OUT = 1;
		break;
		
		case SENS_FL_RD;
			flSensor = FL_SENS_RD;
		break;
		
		case SENS_FR_ON:
			FL_SENS_OUT = 0;
			FR_SENS_OUT = 1;
		break;
		
		case SENS_FR_RD:
			frSensor = FR_SENS_RD;
	
		default:
			break;
	}
	
	return state;
}