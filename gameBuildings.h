#pragma once
/*
	This file contains functions and classes dealing with building objects
*/
#include "gameItem.h"
#include "constants.h"
#include <queue>
#ifndef _gameBuildings_h_
#define _gameBuildings_h_

extern int totalScore;

class Belt {
	public:
		Item itemNow,itemPre;
		// The item on the belt now, and the last item on the belt
		// itemPre was created for the animiations
		int dir;
		// the direction of the belt
		// 1 stand for up, 2 stand for down, 3 stand for left, 4 stand for right
		int pos[2];

		bool isMoved;
		//For Animation
		//It is useless compare to isStuck, anyway. ---yyl

		bool isEmpty;
		// 传送带上是否有物品
		bool isStuck;
		// 传送带是否卡住
		bool nxtStuck;
		// 下一个传送带是否卡住

		int idBef[4];
		// idBef 内最多存三个编号，指代在一次更新中会传给该传送带的传送带
		// idBef[0] 描述长度
		Belt(int direction, int x, int y);
		/*
			Build an empty belt at (x,y), with dir = direction
			by kan bo yi
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
		  by kan bo yi
		*/

		bool exist();
		/*
			Method exist
			Usage bool a = Belt.exist()
			-------------------------
			Tell client whether this belt has been built. If it has just been initialized, or have been deleted
			,than this function will return false.
			by kan bo yi

		*/
	private:

};

class Cutter {
	/*
		Cutter cut the item in it into half, the cutting line is vertical
	*/
	public:
		Item OutputMain,OutputSub;
		// 前者对应为在地图“主方块”上面的输出，后者是“副方块”上面的输出
		// “主方块”，“副方块”的定义详见gameCollection.cpp的buildAt函数

		Item OutputMainPre, OutputSubPre;
		//For Animation
		bool isOperated;
		//To stop the building for 1 step, mainly for animation
		bool isMovedMain, isMovedSub;
		//For Animation

		int dir;
		// same as that in Belt
		int pos[2];
		bool isEmptyMain,isEmptySub;
		//这两个分别意味着OutputMain与OutputSub为空的

		int getSubx();
		int getSuby();
		/*
			Method:getSubx/getSuby
			Usage int xx = cutter.getSubx(),yy = cutter.getSuby();
			---------------------------------------------------
			得到cutter的副中心（即另一个输出口）的坐标
			by Kan bo yi
		*/

		Cutter(int direction, int x, int y);
		/*
			Build an empty cutter at (x,y), with dir = direction
			by kan bo yi
		*/

		Cutter();
		/*
			default building function for Cutter
		*/

		bool input(Belt & input);
		/*
			Method: input
			Usage: bool flag = cutter.input(belt);
			--------------------------------------
			the cutter will try to extract the item from the belt. If the cutter is not available(its output haven't been carried away by the belts),
			it will return false and do nothing, otherwise it will return true and change the value of OutputMain,OutputSub,isEmptyMain,isEmptySub;
			It will also remove the item from the belt

			it will cut the input into two and store it into the OutputMain,OutputSub
			and turn isEmptyMain,isEmptySub from false to true
			by kan bo yi
		
		*/

		bool outputMain(Belt& output);
		/*
			Method: input
			Usage: bool flag = cutter.outputMain(belt);
			--------------------------------------
			the cutter will try to output the item stored in OutputMain to the belt. If the cutter is not available(its OutputMain is empty),
			If the belt has item on it, it will also return false and do nothing, otherwise it will return true and change the value of OutputMain,isEmptyMain;

			turn isEmptyMain from false into true
			by kan bo yi

		*/

		bool outputSub(Belt& output);
		/*
			Method: input
			Usage: bool flag = cutter.outputSub(belt);
			--------------------------------------
			the cutter will try to output the item stored in OutputSub to the belt. If the cutter is not available(its OutputSub is empty),
			If the belt has item on it, it will also return false and do nothing, otherwise it will return true and change the value of OutputSub,isEmptySub;

			turn isEmptySub from false into true
			by kan bo yi

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
		Item Output;
		// inputItemLeft would be at the Left of the product, so does the inputItemRight
		int pos[2];
		int dir;
		bool OutisEmpty;

		Item OutputPre;
		//For Animation
		bool isOperated;
		//To stop the building for 1 step, mainly for animation
		bool isMoved;
		//For Animation

		Composer(int direction, int x, int y);
		/*
			Build an empty Composer at (x,y), with dir = direction
			by kan bo yi
		*/

		Composer();
		/*
			default building function for Composer
		*/

		int getSubx();
		int getSuby();
		/*
			by Xu Zong Zhi
		*/
		bool output(Belt& output);
		bool input(Belt& leftinput, Belt& rightinput);
		/*
			by Xu Zong Zhi
		*/
};


class Rotator {
	/*
		A Rotator rotate the item by 90 degrees clockwise
	*/
public:
	Item Output;
	int pos[2];
	int dir;
	bool OutisEmpty;

	Item OutputPre;
	//For Animation
	bool isOperated;
	//To stop the building for 1 step, mainly for animation
	bool isMoved;
	//For Animation

	Rotator(int x, int y, int direction);

	Rotator();

	int getSubx();
	int getSuby();

	bool output(Belt& output);
	bool input(Belt& input);
	// The item to be rotated

};
class Miner {
	/*
		A Miner produce certain kind of item
	*/
public:
	int pos[2];
	int	dir;
	int produceStatus;
	//因为miner不是每一刻都在生产物品

	bool isMoved;
	//For Animation

	bool isEmpty;
	Item item;
	// the item to be produced by it

	Miner();
	Miner(int x, int y, int direction);

	void setProduct(Item product);
	/*
		Method: setProduct
		Usage: miner.setProduct(product);
		------------------------------
		设置开采器每MINERTICKCOST生产出来的是什么物品
		by Kan bo yi
	*/

	bool output(Belt& output);
	/*
		Method: outPut
		Usage: miner.outPut(belt)
		------------------------------
		向传递的传送带中输出产物，如果传送带此时为满或者开采器的生产CD还没过，那么返回false
		输出成果则返回true

		如果返回false produceStatus = min(MINERTICKCOST, produceStatus + 1) (为了处理堵塞所以才这样)
		如果返回true produceStatus = 1
		by Kan bo yi
	*/

};

class RubbishBin {
	/*
		A Rubbish bin delete the input item
	*/
public:
	int pos[2];
	RubbishBin();
	RubbishBin(int x, int y);
	bool input(Belt& input);
	/*
			Method: input
			Usage: bool flag = rubbishBin.input(belt);
			--------------------------------------
			垃圾桶会删除传入传送带上面的物品
			by kan bo yi

	*/
};

// DECLARE THE ACCEPTOR CLASS ...
class Acceptor {
public:
	int pos[2];

	// pos[0], pos[1] is the top-left corner of the 3x3 area.
	// The main block (isMain) cell is at (pos[0]+1, pos[1]+1).

	int check1items = 0, check2items = 0, check3items = 0, check4items = 0;
	int goalX = 0, goalY = 0, goalColor = 0, goalShape = 0;
	int goalX2 = 0, goalY2 = 0, goalColor2 = 0, goalShape2 = 0;
	int goalX3 = 0, goalY3 = 0, goalColor3 = 0, goalShape3 = 0;
	int goalX4 = 0, goalY4 = 0, goalColor4 = 0, goalShape4 = 0;

	// These are passed into the Acceptor when buiding, then passed to the input() function
	// mode=0 for classic accept only one item, mode=1 for swapping inputs
	// goalx2 ... goalshape2 arguments for swapping mode

	bool isEmpty;
	// True if no item currently stored. Once it accepts an item, set isEmpty = false.

	Item storedItem;
	// The last accepted item. After input, we have this item stored here for detection.

	Acceptor();
	Acceptor(int x, int y);
	bool input(Belt& input);

	/*
	  input: tries to take an item from a belt adjacent to its center cell.
	  If successful, it stores the item and clears the belt, returning true.
	  Otherwise returns false.
	*/
};

#endif 
