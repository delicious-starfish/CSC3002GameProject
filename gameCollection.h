#pragma once
/*
	This file contains the classes that store world objects
*/
#include "gameBuildings.h"
#include "constants.h"
#include <string>
#include <stack>
#ifndef _gameCollection_h_
#define _gameCollection_h_


class Node {
	public:
		/*
			Node object let the program know what is the type of building (or blank ground)
			is at a specific position
		*/
		Node();
		Node(int buildingType, int dataId, bool isMainBlock);
		/*
			the Init function for the class Node
			input nothing and return the Node class variable
			by kan bo yi
		*/
		int type;
		//0 ground, 1 belt, 2 cutter, 3 averager, 4 porter, 5 composer, 6 rotator, 
		//7 miner
		int id;
		// id 
		bool isMain;
		// if the building occupy n blocks, than n - 1 nodes will be assigned with isMain = false
		// only one node will be assigned with isMain = true
};	

class World {
	public:
		World();
		/*
			the Init function for the class World
			input nothing and return the World class variable
			fill mapp with empty nodes
			by kan bo yi
		*/

	
		Node mapp[MAPLENGTH][MAPLENGTH];// the map that shows what is at a specific point
		Belt belt[2500];
		Cutter cutter[2500];
		RubbishBin rubbishBin[2500];
		//Averager averager[2500];
		//Porter porter[2500];
		Composer composer[250];
		//Rotator rotator[2500];
		Miner miner[2500];
		std::stack<int> deletedBeltId,deletedCompId,deletedCutterId;
		int beltNum = 0, cutterNum = 0, averagerNum = 0, porterNum = 0, composerNum = 0, minerNum = 0,rubbishBinNum = 0;
		int maxBeltId = 0,maxCutterId = 0, maxComposerId = 0, maxMinerId = 0, maxRubbishBinId = 0;
		int rotatorNum = 0;

		void buildAt(int building, int x, int y, int direction);
		// build an empty building at x,y with direction
		// by kan bo yi

		void destoryAt(int x, int y);
		/*
			Method: destroyAt
			Usage: world.destroyAt(0,10);
			--------------------------------
			Destroy the building at the position.
			If the building occupies multiple blocks on the mapp. We can destroy the whole building if you execute it on any of the position
			the building occupy
			
			by Kan Bo Yi
		*/

		void destroyAppendix(int x, int y);
		/*
		Method: deleteAppendix
		Usage: world.deleteAppendix(COMPOSERID,10);
		--------------------------
		�ڽ����и���/�ϳ�����ʱ��ḽ�������������ʹ���������ɾ����ʱ��ҲӦ��һ��ɾȥ
		by kan bo yi
		ɾ����Ӧ�Ĵ��ʹ�Ҳ����ɾȥ�и���/�ϳ���
		When using it, first destroy Appendix, and then destroy building itself
		by Yilin Yao
		*/

		std::string toString();
		/*
			outPut: a simplized visualized version of the world
			represent the buildings in symbols

			Only support the belt and cutter, others will be represented as numbers
			by kan bo yi
		*/
		
		void putItemAt(Item item, int x, int y);
		/*
		Method: putItemAt
		Usage: world.putItemAt(item, x, y);
		--------------------------
		put an item at (x,y) in the map. if there is a building at (x,y), then the item will be 
		attached as its property.
		If there is no building at (x,y) nothing would happen

		Not finished, only support adding item to belts
		by kan bo yi
		*/
private:
	void refreshBeltAt(int x, int y, int direction);
	/*
		Method: refreshBeltAt
		Usage: world.refreshBeltAt(1,0,LEFT,4);
		--------------------------
		��mapp��belt������괫�ʹ�֮�󣬻���Ҫˢ�´��ʹ���idNxt�����Ա��ڸ���.
		Ĭ������ӵĴ��ʹ�����belt[maxBeltId]

		by kan bo yi
		*/
	
	void deleteInArray(int buildingType, int id);
	/*
		Method: deleteInArray
		Usage: world.deleteInArray(BELTID,10);
		--------------------------
		��belt[],composer[],rubbishBin[],cutter[]����ɾ��Ŀ�꽨��
		���һ�Ѹý���Id�������ջ�С����´ν���ʱ������ʹ�û���ջ�еĽ���Id

		by kan bo yi
	*/

	void deleteInMapp(int buildingType, int id);
	/*
		Method: deleteInMapp
		Usage: world.deleteInMapp(BELTID,10);
		--------------------------
		��mapp�аѸý���ռ�ݵ����еط�ȫ����������Ϊ����

		by kan bo yi
	*/
	void deleteBeltLink(int id);
	/*
		Method: deleteBeltLink
		Usage: world.deleteBeltLink(10);
		--------------------------
		�øô��ʹ���Χ�Ĵ��ʹ�����ȫ���ѹ�

		by kan bo yi
	*/
	void clearGround(int building, int x, int y, int direction);
	/*
		Method: clearGround
		Usage: world.clearGround(BELTID,10,10,UP);
		--------------------------
		���㽨��IdΪbuilding��id֮ǰ�����֮λ�ó�ͻ�Ľ���
		Ŀǰ����֧�ִ��ʹ�
		by kan bo yi
	*/
	//void deleteAppendix(int building, int id);
	//   Not Used, Moved to destroyAppendix(int x,int y);
};

class Game {
	public:
		Game();
		/*
		*		the Init function for class Game
				input: Nothing, output an Game class variable
				-------
				function: setup the data of world, generate the map...
		*/
		
		World * world;
		void loadTestMap();
		//void generateMap();
	private:
};



#endif // !_gameCollection_h_
