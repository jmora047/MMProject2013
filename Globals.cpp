/*============================== Identifiers ===============================*/
#define NORTH 0                             //numbers representing direction
#define EAST 1
#define SOUTH 2
#define WEST 3
/*============================ End Identifiers =============================*/

/*============================ Global Variables ============================*/

//The map holding the values used for the flood-fill algorithm
uint8_t mazeMap[16][16] = {
{14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14},  
{13,12,11,10,9,8,7,6,6,7,8,9,10,11,12,13},
{12,11,10,9,8,7,6,5,5,6,7,8,9,10,11,12},
{11,10,9,8,7,6,5,4,4,5,6,7,8,9,10,11},
{10,9,8,7,6,5,4,3,3,4,5,6,7,8,9,10},
{9,8,7,6,5,4,3,2,2,3,4,5,6,7,8,9},
{8,7,6,5,4,3,2,1,1,2,3,4,5,6,7,8},
{7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7},
{7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7},
{8,7,6,5,4,3,2,1,1,2,3,4,5,6,7,8},
{9,8,7,6,5,4,3,2,2,3,4,5,6,7,8,9},
{10,9,8,7,6,5,4,3,3,4,5,6,7,8,9,10},
{11,10,9,8,7,6,5,4,4,5,6,7,8,9,10,11},
{12,11,10,9,8,7,6,5,5,6,7,8,9,10,11,12},
{13,12,11,10,9,8,7,6,6,7,8,9,10,11,12,13},
{14,13,12,11,10,9,8,7,7,8,9,10,11,12,13,14}};

//1 represents a wall, 0 represents an open path. Each nibble represents
//a column of the maze, each row represents a row in the maze. The values
//of one nibble represent the wall configuration of each cell.
uint32_t walls[2][16] = {
{0xB1111111,0x11111113},  
{0x80000000,0x00000002},
{0x80000000,0x00000002},
{0x80000000,0x00000002},
{0x80000000,0x00000002},
{0x80000000,0x00000002},
{0x80000000,0x00000002},
{0x80000000,0x00000002},
{0x80000000,0x00000002},
{0x80000000,0x00000002},
{0x80000000,0x00000002},
{0x80000000,0x00000002},
{0x80000000,0x00000002},
{0x80000000,0x00000002},
{0x80000000,0x00000002},
{0xC4444444,0x44444446}};

//sides - holds the flood values of open adjacent cells. The value of any
//adjacent cell blocked off by a wall is assigned to 255. direction of the
//cell is specified by the index of the array.
//e.g. The sides array looking from cell 0,0 at the start of the maze will be
//	   {255, 13, 255, 255}
uint8_t sides[4] = {255, 255, 255, 255};

uint8_t fl_stack[255];				//The stack holding flood-fill coordinates
uint8_t fl_stack_size = 0;			//The size of the flood-fill stack



/*========================== Direction and Location =========================*/

uint8_t current_facing = 1;		//the direction the mouse is facing
uint8_t mouse_x = 0;			//the mouse's current x position
uint8_t mouse_y = 0;			//the mouse's current y position

/*======================== End Direction and Location =======================*/

/*========================== Handshaking Variables ==========================*/

bool r1_done_req = 0;
bool r1_done_ack = 0;

bool mapready_req = 0;
bool mapready_ack = 0;

bool turncomplete_req = 0;
bool turncomplete_ack = 0;

bool move_req = 0;
bool move_ack = 0;

/*======================== End Handshaking Variables ========================*/