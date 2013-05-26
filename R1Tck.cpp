enum R1_States {R1_INIT, R1_INIT_SENSOR, R1_INIT_CENTER, 
				R1_FLOOD, R1_MOVE, R1_DONE} R1_State;
				
//R1Tck - 		Determines when to map and when to move during the first run
//
//Writes To -	movready_req		-	requests action from MoveTck
//				mapready_req		-	requests action from FloodTck	
//				init_sens_req		-	tells SensTck to calibrate sensors				
//				init_center_req		-	tells MoveTck to center mouse in starting cell
//
//Reads From -	movready_ack
//				mapready_ack
//				init_sens_ack
//				init_center_ack
//				mouse_x
//				mouse_y
//				
//Complete? []
//Tested? []


int R1Tck(int state) {
	switch state {			//transitions 	
		case -1:	
			state = R1_INIT;
			break;
		
		case R1_INIT:
			init_sens_req = 1;
			state = R1_INIT_SENSOR;
			break;
			
		case R1_INIT_SENSOR:
			if (!init_sens_ack)
				state = R1_INIT_SENSOR;
			else{
				init_sens_req = 0;
				init_center_req = 1;
				state = R1_INIT_CENTER;
				}
			break;
			
		case R1_INIT_CENTER:
			if (!init_center_ack)
				state = R1_INIT_CENTER;
			else{
				init_center_req = 0;
				mapready_req = 1;
				state = R1_FLOOD;
			break;
			
		case R1_FLOOD:
			if(!mapready_ack)
				state = R1_FLOOD;
			else if(mapready_ack && (mazemap[mouse_x, mouxe_y] == 0))
				mapready_req = 0;
				state = R1_DONE;
			else
				mapready_req = 0;
				movready_req = 1;
				state = R1_MOVE;
			break;
			
		case R1_MOVE:
			if (!movready_ack)
				state = R1_MOVE;
			else
				movready_req = 0;
				mapready_req = 1;
				state = R1_FLOOD;
			break;
			
		default:
			state = R1_INIT;
			break;			
	}
	
	switch state {			//actions	
		case -1:	
			break;		
		case R1_INIT:
			break;			
		case R1_INIT_SENSOR:
			break;			
		case R1_INIT_CENTER:
			break;			
		case R1_FLOOD:
			break;			
		case R1_MOVE:
			break;			
		default:
			break;			
	}
	
	return state;
}