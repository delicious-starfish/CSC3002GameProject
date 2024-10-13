#pragma once
/*
	This file contains functions and classes dealing with building objects
*/

#ifndef _gameBuildings_h_
#define _gameBuildings_h_

class Belt {
	public:
		int itemNow[2][2][2],itemPre[2][2][2];
		// The item on the belt now, and the last item on the belt
		// itemPre was created for the animiations
		int dir;
		// the direction of the belt
		// 1 stand for up, 2 stand for down, 3 stand for left, 4 stand for right
		int pos[2];
	private:

};

class Cutter {
	/*
		Cutter cut the item in it into half, the cutting line is vertical
	*/
	public:
		int timeCost;
		// time needed for the cutter to perform a cut
		int item[2][2][2];
		// the item to be cutted
		int dir;
		// same as that in Belt
		int pos[2];
	private:

};

class Averager {
	//TBA
};

class Porter {
	// Porter can shoot the item to 3 blocks away, 
	// if there is a belt at the position where the item falls, then the item will
	// be carried away by that belt
	public:
		int pos[2];
		int dir;
		int item[2][2][2];
		// the item to be shot
};

class Composer {
	/*
		A composer compose two item into one
		two halves of item into one item

	*/
	public:
		int inputItem1[2][2][2], inputItem2[2][2][2];
		// these two are ingredients
		int pos[2];
		int dir;
};

class Rotator {
	/*
		A Rotator rotate the item by 90 degrees clockwise
	*/
	int item[2][2][2];
	// The item to be rotated
	int pos[2];
	int dir;
};

class Miner {
	/*
		A Miner produce certain kind of item
	*/
	int pos[2];
	int	dir;
	int item[2][2][2];
	// the item to be produced by it

};
#endif 
