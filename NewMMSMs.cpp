//new get wall config
void get_wall_config(){
	/*find out if there is a wall to the west*/
	/*if there is a wall to the west, there is a wall to the east of the cell to the west*/
}





/* MasterTck - determines whether the mouse is performing an initial run, exploring the maze
			   for the shortest route, performing a speed run, or returning from a speed run.
*/
bool R1_done_ack = 0;		//acknowleges completion of first run
enum MTck_States(init_run, explore_run, speed_run, speed_return) MSM_State;
int MasterTck(int state){
	switch (state) {	//transitions
		case -1:
			break:
		case init_run:
			break;
		case explore_run:
			break;
		case speed_run:
			break;
		case speed_return;
			break;		
	}
	
	switch (state) {	//actions
		case -1:
			break:
		case init_run:
			break;
		case explore_run:
			break;
		case speed_run:
			break;
		case speed_return;
			break;		
	}
	return state;
}

enum R1Tck_States(init, map, moving, turning, wait2move, wait2turn, finished_1, finished_2) R1Tck_State;

int R1Tck(int state) {
	switch(state) {							// transitions
		case -1:
			//state = stuf;
			break;
		case init:							// calibration state
			//remain for 2 seconds
			if (/*2 seconds done*/){
				state = wait2move;
				R1_mov_req = 1;
			}
			break;
		case map:							// mapping state
			if (R1_Map_Req)					//
				state = map;
			else if (mapVal[x][y] = 0)		//
				state = finished_1;
			break;
		case moving:						// moving forward
			if (!R1_Map_Ready_Req)			//  
				state = moving;
			else if (R1_Map_Ready_Req) 
				R1_Map_Ready_Ack = 1;	
			break;
		case turning:						// turning state
			if (!R1_Turn_Complete_Req)		// 
				state;
			else if (R1_Turn_Complete_Req)	//
				state = wait2move;
			break;
		case wait2move:						// waiting to move
			if (idealFacing == currentFacing && mapVal[x][y] != 0)	//
				R1_Move_Req = 1;
			//else if
			break;
		case wait2turn:						// waiting to turn
			if (!R1_Turn_Ack)				//
				state;
			else if (R1_Turn_Ack)			//
				state = turning;
			break;
		case finished_1:						// reached center
			if (!R1_Done_Ack)				//
				state;
			else if (R1_Done_Ack)			//		
				state = finished_2;
			break;
		case finished_2:						// wrap things up
			break;
		default:
			state = init;
			break;
	}
	
	switch (state) {	//actions
		case -1:
			//state = stuf;
			break;
		case init:
			break;
		case map:
			break;
		case moving:
			break;
		case turning:
			break;
		case wait2move:
			break;
		case wait2turn:
			break;
		case complete:
			break:
		case finished:
			break;
	}
	return state;
}

enum R1MOV_States(init, no_walls, right_wall, left_wall, both_walls, front_stop, done_1, done_2);

int R1MOV_Tck(int state) {
	switch (state) {
		case init:
			break;
		case no_walls:
			if (!frontWall && !cellComplete && !leftWall && !rightWall)
			//
			break;
		case right_wall:
			if (
			break;
		case left_wall:
			break;
		case both_walls:
			break;
		case front_stop:
			break;
		case done_1:
			break;
		case done_2:
			break;
