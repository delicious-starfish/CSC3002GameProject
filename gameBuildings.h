#pragma once
/*
	This file contains functions and classes dealing with building objects
*/
#include "gameItem.h"
#include <queue>
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

		bool isMoved;
		//For Animation
		//It is useless compare to isStuck, anyway. ---yyl

		bool isEmpty;
		// ���ʹ����Ƿ�����Ʒ
		bool isStuck;
		// ���ʹ��Ƿ�ס
		bool nxtStuck;
		// ��һ�����ʹ��Ƿ�ס

		int idBef[4];
		// idBef ������������ţ�ָ����һ�θ����лᴫ���ô��ʹ��Ĵ��ʹ�
		// idBef[0] ��������
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
		// ǰ�߶�ӦΪ�ڵ�ͼ�������顱���������������ǡ������顱��������
		// �������顱���������顱�Ķ������gameCollection.cpp��buildAt����

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
		//�������ֱ���ζ��OutputMain��OutputSubΪ�յ�

		int getSubx();
		int getSuby();
		/*
			Method:getSubx/getSuby
			Usage int xx = cutter.getSubx(),yy = cutter.getSuby();
			---------------------------------------------------
			�õ�cutter�ĸ����ģ�����һ������ڣ�������
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
	Item item;
	// The item to be rotated
	int pos[2];
	int dir;
};

class Miner {
	/*
		A Miner produce certain kind of item
	*/
public:
	int pos[2];
	int	dir;
	int produceStatus;
	//��Ϊminer����ÿһ�̶���������Ʒ

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
		���ÿ�����ÿMINERTICKCOST������������ʲô��Ʒ
		by Kan bo yi
	*/

	bool output(Belt& output);
	/*
		Method: outPut
		Usage: miner.outPut(belt)
		------------------------------
		�򴫵ݵĴ��ʹ���������������ʹ���ʱΪ�����߿�����������CD��û������ô����false
		����ɹ��򷵻�true

		�������false produceStatus = min(MINERTICKCOST, produceStatus + 1) (Ϊ�˴���������Բ�����)
		�������true produceStatus = 1
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
			����Ͱ��ɾ�����봫�ʹ��������Ʒ
			by kan bo yi

	*/
};
#endif 
