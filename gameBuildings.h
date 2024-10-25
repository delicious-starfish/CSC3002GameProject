#pragma once
/*
	This file contains functions and classes dealing with building objects
*/
#include "gameItem.h"
#ifndef _gameBuildings_h_
#define _gameBuildings_h_

class Belt {
	public:
		Item itemNow,itemPre;
		// The item on the belt now, and the last item on the belt
		// itemPre was created for the animiations
		int dir;
		// the direction of the belt
		// 1 stand for up, 2 stand for down, 3 stand for left, 4 stand for right
		int pos[2];
		bool isEmpty;
		// 传送带上是否有物品
		Belt(int direction, int x, int y);
		/*
			Build an empty belt at (x,y), with dir = direction
		*/

		Belt();
		/*
			default building function for Belt
		*/
		void grantItem(Item item);
		/*
		* Method: gramtItem
		* Usage: belt.grantItem(item)
		* ---------------------------------
		  Give the belt the item, set the itemNow to the item you give
		*/
	private:

};

class Cutter {
	/*
		Cutter cut the item in it into half, the cutting line is vertical
	*/
	public:
		Item item;
		// the item to be cutted
		int dir;
		// same as that in Belt
		int pos[2];

		Cutter(int direction, int x, int y);
		/*
			Build an empty cutter at (x,y), with dir = direction
		*/

		Cutter();
		/*
			default building function for Cutter
		*/

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
		Item item;
		// the item to be shot
};

class Composer {
	/*
		A composer compose two item into one
		two halves of item into one item

	*/
	public:
		Item inputItemLeft, inputItemRight;
		// inputItemLeft would be at the Left of the product, so does the inputItemRight
		int pos[2];
		int dir;

		Composer(int direction, int x, int y);
		/*
			Build an empty Composer at (x,y), with dir = direction
		*/

		Composer();
		/*
			default building function for Composer
		*/

};

class Rotator {
	/*
		A Rotator rotate the item by 90 degrees clockwise
	*/
	Item item;
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
	Item item;
	// the item to be produced by it

};
#endif 
