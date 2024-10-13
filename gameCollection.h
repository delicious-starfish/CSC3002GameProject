#pragma once
/*
	This file contains the classes that store world objects
*/
#include "gameBuildings.h"
#ifndef _gameCollection_h_
#define _gameCollection_h_

class Node {
	public:
		/*
			Node object let the program know what is the type of building (or blank ground)
			is at a specific position
		*/
		Node();
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
		*/

	
		Node mapp[48][48];// the map that shows what is at a specific point
		Belt belt[2500];
		Cutter cutter[2500];
		Averager averager[2500];
		Porter porter[2500];
		Composer composer[2500];
		Rotator rotator[2500];
		Miner miner[2500];


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
	private:
};



#endif // !_gameCollection_h_
