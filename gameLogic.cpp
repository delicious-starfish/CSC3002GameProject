#include "gameLogic.h"
#include "gameCollection.h"
#include "constants.h"
#include "gameBuildings.h"
#include "gameItem.h"
#include <iostream>

void logicTick(World& world) {
	buildingLogic(world);

	beltLogic(world);
}

void beltLogic(World& world) {
	bool * book = new bool[world.maxBeltId];
	// book means whether this belt has been updated
	for (int i = 0; i < world.maxBeltId; i++) book[i] = false;

	for (int i = 0; i < world.maxBeltId; i++) {

		if (!world.belt[i].exist()) continue;

		if (book[i]) continue;
		//This belt has been updated

		if(world.belt[i].idNxt != -1 && world.belt[world.belt[i].idNxt].exist()) 
			belt_FindEndAndUpdate(world, book, i);
	}


	delete [] book;
}

void buildingLogic(World & world) {
	return;
}


void belt_FindEndAndUpdate(World& world, bool footprint[], int nowId) {

	if (footprint[nowId]) return;

	footprint[nowId] = true;
	int nxtId = world.belt[nowId].idNxt;

	if (nxtId == -1) return;
	if (!world.belt[nxtId].exist()) return;

	belt_FindEndAndUpdate(world, footprint, nxtId);

	if (world.belt[nxtId].isEmpty) {
		if (world.belt[nowId].isEmpty) return;
		
		for(int i = 0;i < 2;i ++)
			for (int j = 0; j < 2; j++) 
				for (int k = 0; k < 2; k++) {
					world.belt[nxtId].itemNow.colorId[i][j][k] = world.belt[nowId].itemNow.colorId[i][j][k];
					world.belt[nowId].itemNow.colorId[i][j][k] = 0;
					world.belt[nxtId].itemNow.shapeId[i][j][k] = world.belt[nowId].itemNow.shapeId[i][j][k];
					world.belt[nowId].itemNow.shapeId[i][j][k] = 0;
				}
		world.belt[nxtId].isEmpty = false;
		world.belt[nowId].isEmpty = true;
	}
}