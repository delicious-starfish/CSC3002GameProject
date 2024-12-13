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
		Composer composer[2500];
		Rotator * rotator;
		Miner miner[2500];

		// Added on 1207 for Acceptor, by Xin Cao:
		Acceptor acceptor[2500];
		std::stack<int> deletedAcceptorId;
		int acceptorNum = 0;
		int maxAcceptorId = 0;
		// Over

		std::stack<int> deletedBeltId,deletedCompId,deletedCutterId;
		std::stack<int> * deletedRotatorId;
		int beltNum = 0, cutterNum = 0, averagerNum = 0, porterNum = 0, composerNum = 0, minerNum = 0,rubbishBinNum = 0;
		int maxBeltId = 0,maxCutterId = 0, maxComposerId = 0, maxMinerId = 0, maxRubbishBinId = 0,maxRotatorId = 0;
		int rotatorNum = 0;

		void buildAt(int building, int x, int y, int direction,
		// for Acceptor
					int check1items = 0, int goalX = 0, int goalY = 0, int goalColor = 0,int goalShape = 0,
					int check2items = 0, int goalX2 = 0, int goalY2 = 0, int goalColor2 = 0, int goalShape2 = 0,
					int check3items = 0, int goalX3 = 0, int goalY3 = 0, int goalColor3 = 0, int goalShape3 = 0,
					int check4items = 0, int goalX4 = 0, int goalY4 = 0, int goalColor4 = 0, int goalShape4 = 0);
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
		在建造切割器/合成器的时候会附带建造两个传送带，现在在删除的时候也应当一并删去
		by kan bo yi
		删除相应的传送带也可以删去切割器/合成器
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
		在mapp和belt中添加完传送带之后，还需要刷新传送带的idNxt变量以便于更新.
		默认新添加的传送带就是belt[maxBeltId]

		by kan bo yi
		*/
	
	void deleteInArray(int buildingType, int id);
	/*
		Method: deleteInArray
		Usage: world.deleteInArray(BELTID,10);
		--------------------------
		在belt[],composer[],rubbishBin[],cutter[]等中删除目标建筑
		并且会把该建筑Id加入回收栈中。在下次建造时会优先使用回收栈中的建筑Id

		by kan bo yi
	*/

	void deleteInMapp(int buildingType, int id);
	/*
		Method: deleteInMapp
		Usage: world.deleteInMapp(BELTID,10);
		--------------------------
		在mapp中把该建筑占据的所有地方全部重新设置为地面

		by kan bo yi
	*/
	void deleteBeltLink(int id);
	/*
		Method: deleteBeltLink
		Usage: world.deleteBeltLink(10);
		--------------------------
		让该传送带周围的传送带与其全部脱钩

		by kan bo yi
	*/
	void clearGround(int building, int x, int y, int direction);
	/*
		Method: clearGround
		Usage: world.clearGround(BELTID,10,10,UP);
		--------------------------
		在你建造Id为building的id之前清空与之位置冲突的建筑
		目前仅仅支持传送带
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
