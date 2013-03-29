/*
tested[] - fill brackets with . if not tested, ! if tested
*/



/* Bit-Access Functions */
uint8_t setBit(uint8_t x, uint8_t k, uint8_t b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
uint8_t getBit(uint8_t x, uint8_t k) {
	return ((x & (0x01 << k)) != 0);
}

//getWallConfig - returns the wall configuration of the specified cell
//eg - getWallConfig(0,0) returns 00001011
//tested[.]
uint8_t getWallConfig(const uint8_t x, const uint8_t y){
	if (x < 8)					//if x is in the left half of the maze
		return ((walls[0][y] >> (4 * (7 - x))) && 0x0000000F);
	else
		return ((walls[1][y] >> (4 * (15 - x))) && 0x0000000F);
}

//checkCell - checks if cell is 1+ the minimum value of its open neighbors
//@param adjSides[] - a 4-array representing the values of the open cells adjacent to the cell specified by x and y
//@param x - the x position being referenced
//@param y - the y position being referenced
//@return - true if the cell's value is 1+ the minimum value of its open neighbors, else false
//precondition - adjSides[] must reference the sides adjacent to mazeMap[y][x]
boolean checkCell(uint8_t x, uint8_t y){
  unsigned char minimum = get_sides_min();
  return (mazeMap[x][y] == (minimum + 1));
}



//getValueFrom - gets the value of the cell to the north, east, south, or west of a specified cell
// NOTE - overloaded function allowing a reference point other than the mouses current position
//        I do not know if overloaded functions are supported in the arduino environment
//@param facing - the direction to look for the value, north, east, south, or west
//@param x - the x position of the cell to look from
//@param y - the y position of the cell to look from
//@return - the floodfill value of the referenced cell
//precondition - the wallconfig has already been found for the cell
//tested[.]
uint8_t getValueFrom(uint8_t facing, uint8_t x, uint8_t y) {
  unsigned char wallConfig = getWallConfig(x, y);
  switch (facing)
  {
    case NORTH:
      if(!getBit(wallConfig, NORTH)) return mazeMap[x][y - 1];
      else return 255;
      break;
    case EAST:
      if(!getBit(wallConfig, EAST)) return mazeMap[x + 1][y];
      else return 255;
      break;
    case SOUTH:
      if(!getBit(wallConfig, SOUTH)) return mazeMap[x][y + 1];
      else return 255;
      break;
    case WEST:
      if(!getBit(wallConfig, WEST)) return mazeMap[x - 1][y];
      else return 255;
      break;
  }
}

//getSidesMin - searches the sides array and returns the miminum value.
//@param sidesAr[] - a size-4 array (presumably a sides array)
//@return - the minimum value of the array
uint8_t getSidesMin() {
	/*keeps track of the minimum value, set to the first element by defalt*/
	uint8_t minimum = sides[NORTH];                   
	if (sides[EAST] < minimum) minimum = sides[EAST];       // Checks if values at the remaining positions in the array 
	if (sides[SOUTH] < minimum) minimum = sides[SOUTH];     // are less than the default minimum, updating the minimum accordingly
	if (sides[WEST] < minimum) minimum = sides[WEST];     
	return minimum;  
}

//shift_clockwise - returns the direction (numOfTimes * 90 degrees) clockwise
//					of the initial position
//@param numOfTimes - the amount of times you wish to look in terms of 
//					90 degree clockwise increments on the compass
//      example
//          shiftClockwise(1, NORTH) == EAST, shiftClockwise(2, SOUTH) == NORTH
//@param initPosition - position you are looking from. usually current_facing
//@return - the direction numOfTimes * 90degrees clockwise of the init position
uint8_t shift_clockwise(uint8_t initPosition, uint8_t numOfTimes) {
  uint8_t tmp = initPosition;
  for (uint8_t i = 0; i < numOfTimes; i++){
		if (tmp + 1 == 4){      //changed from 5 to 4
			tmp = 0x00;
		}
		else{
				++tmp;
			}
	}
	return tmp;
}

//isNorthWall - determines if there is a north wall from a cell's wall configuration
//@param wallConfig - a cell's wall configuration determined earlier by getWallConfig()
//@return - true if a north wall is present, else false
bool isNorthWall(uint8_t wallConfig){
  return getBit(~wallConfig, NORTH);
}
bool isEastWall(uint8_t wallConfig){
  return getBit(~wallConfig, EAST);
}
bool isSouthWall(uint8_t wallConfig){
  return getBit(~wallConfig, SOUTH);
}
bool isWestWall(uint8_t wallConfig){
  return getBit(~wallConfig, WEST);
}

/*=====================COORDINATE COMPRESSION FUNCTIONS=====================*/
//getX - returns the x value from a uint8_t holding the x and y values
uint8_t getX(uint8_t b){
  return (b & 0xF0) >> 4;
}
//getY - returns the y value from a uint8_t holding the x and y values
uint8_t getY(uint8_t b){
  return (b & 0x0F);
}
//setX - writes the x value to a uint8_t holding holding the x and y values
//@param &b - the uint8_t you wish to write a value to
//@param xValue - the value to write to the uint8_t
void setX(uint8_t &b, uint8_t xValue){
  b = (b & 0x0F) | xValue;
}
void setY(uint8_t &b, uint8_t yValue){
  b = (b & 0xF0) | (yValue << 4);
}
//takes an x coordinate and a y coordinate and compresses them into a uint8_t
uint8_t compressCoords(uint8_t x, uint8_t y){
    return ((x & 0x0F) << 4) | (y & 0x0F);
}
/*===================END COORDINATE COMPRESSION FUNCTIONS===================*/
===========STACK FUNCTIONS==============================*/
//pop - pops the coordinates from the fl_stack in their compressed form
uint8_t fl_pop(){ 
/*==================
  --fl_stack_size;
  return stack[fl_stack_size];
}
//push - pushes the compressed coordinates onto the fl_stack
void fl_push(const uint8_t x, const uint8_t y){
	uint8_t coords= compress_coord(x, y);
	fl_stack[fl_stack_size] = coords;
	++fl_stack_size;
}
//fl_master_push - pushes all open adjacent cells onto the fl_stack
void fl_master_push(uint8_t x, uint8_t y){
	if (sides[NORTH] != 255) fl_push(x, y - 1);
	if (sides[EAST] != 255) fl_push(x + 1, y);
	if (sides[SOUTH] != 255) fl_push(x, y + 1);
	if (sides[WEST] != 255) fl_push(x - 1, y); 
}
/*===========================END STACK FUNCTIONS============================*/

