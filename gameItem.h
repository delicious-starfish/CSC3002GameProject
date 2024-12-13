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
	* Constructor: Item
	* Usage Item item = item();
	* -------------------------
		create an Item object, this item is empty in shapeId (all zeros) and in colorId (all zeros)
	*/

	Item(int assignedShapeId, int assignedColorId);
	/*
	* Constructor: Item
	* Usage Item item = item(shapeId, colorId);
	* -----------------------------------------
	* create an Item with all the same shape, and a same color.
	* ������Ʒȫ����ͬ��ͼ�κ���ɫ����
		by kan bo yi
	*/

	bool operator == (Item& item);

	void rotate();

};
#endif // !_gameItem_h_

