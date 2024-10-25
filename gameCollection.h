#pragma once
/*
	This file contains the classes that store world objects
*/
#include "gameBuildings.h"
#include "constants.h"
#include <string>
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
		*/

	
		Node mapp[MAPLENGTH][MAPLENGTH];// the map that shows what is at a specific point
		Belt belt[2500];
		Cutter cutter[2500];
		//Averager averager[2500];
		//Porter porter[2500];
		Composer composer[250];
		//Rotator rotator[2500];
		//Miner miner[2500];
		int beltNum = 0, cutterNum = 0, averagerNum = 0, porterNum = 0, composerNum = 0;
		int rotatorNum = 0;

		void buildAt(int building, int x, int y, int direction);
		// build an empty building at x,y with direction

		std::string toString();
		/*
			outPut: a simplized visualized version of the world
			represent the buildings in symbols

			Only support the belt and cutter, others will be represented as numbers
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
		
		*/
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
		
		World world;
		void loadTestMap();
		//void generateMap();
	private:
};



#endif // !_gameCollection_h_
