#pragma once
#ifndef _gameItem_h_
#define _gameItem_h_
/*
	Serves to store the items in the buildings and do item calculation

*/

class Item {
	/*
		collection of different parts
		ingredients and output of factories
	*/
	public:
	int shapeId[2][2][2];
	int colorId[2][2][2];

	Item();
	/*
		create an Item object, this item is empty in shapeId (all zeros) and in colorId (all zeros)
	*/


};
#endif // !_gameItem_h_

