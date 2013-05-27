enum FL_States {FL_IDLE, FL_POP, FL_PUSHADJ, FL_GETFACE};
//FL_Tck - 		controls the mapping of the maze for the first run. Also 
//				determines the direction of the next cell. 
//Writes To -	mapready_ack
//				next_direction_g
//				fl_stack
//Reads From -	mapready_req
//				mouse_x
//				mouse_y
//				fl_stack_size
//Complete? []
//Tested? []
int FL_tck(int state) {
	switch (state) {		//transitions
		case -1:
			state = FL_IDLE;
			break:
			
		case FL_IDLE:		//Mouse is not mapping
			if(!mapready_req)
				state = FL_IDLE;
			else if(mapready_req && cell_check(mouse_x, mouse_y)){	//If cell is 1+ min open neighbors get facing
				//mapready_ack = 1;
				state = FL_GETFACE;
			}
			else if(mapready_req && !cell_check(mouse_x, mouse_y)){
				//mapready_ack = true;
				fl_stack_size = 0;
				static uint8_t x_ind = mouse_x;
				static uint8_t y_ind = mouse_y;
				fl_push(x_ind, y_ind);
				state = FL_POP;
			}
			break;
			
		case FL_POP:		//Pop cell from stack
			if(cell_check(x_ind, y_ind) && fl_stack_size > 0)
				state = FL_POP;
			else if(!cell_check(x_ind, y_ind)){
				maze_map[x_ind][y_ind] = get_sides_min() + 1;
				state = FL_PUSHADJ;
			}
			else if(cell_check(x_ind, y_ind) && fl_stack_size == 0)
				state = FL_GETFACE;
			break;
			
		case FL_PUSHADJ;	//Push adjacent cells onto stack
			state = FL_POP;
			break;	
			
		case FL_GETFACE;	//Tell the mouse where to face next
			mapready_ack = 1;
			state = FL_IDLE;
			break;
			
		default
			state = FL_IDLE;
			break:
	}
	
	switch (state) {		//actions
		case -1:
			break:
		case FL_IDLE:		//Mouse is not mapping
			break;
		case FL_POP:		//Pop cell from stack
				static uint8_t cell_loc = fl_pop();
				x_ind = get_x(cell_loc);
				y_ind = get_y(cell_loc);
			break;
		case FL_PUSHADJ;	//Push adjacent cells onto stack
			fill_sides(x_ind, y_ind);
			fl_master_push(x_ind, y_ind);
			break;	
		case FL_GETFACE;	//Tell the mouse where to face next
			next_direction_g = get_next_direction();
			break;
		default
			break:
	}
	return state;
}
