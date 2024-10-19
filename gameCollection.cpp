#include "gameCollection.h"
#include "constants.h"
#include "gameBuildings.h"
#include <string>

using namespace std;

World::World() {

	for (int i = 0; i < MAPLENGTH; i++)
		for (int j = 0; j < MAPLENGTH; j++)
			mapp[i][j] = Node(GROUNDID, 0, false);
}


void World::buildAt(int building, int x, int y, int direction) {
	switch (building) {
		case BELTID:
			belt[beltNum] = Belt(direction, x, y);
			mapp[y][x] = Node(BELTID, beltNum, true);
			beltNum++;
			break;



		case CUTTERID:
			cutter[cutterNum] = Cutter(direction, x, y);

			mapp[y][x] = Node(CUTTERID, cutterNum, true);
			// Cutter length = 2, so two block will be set on mapp
			// However, only one of them would be a mainblock (isMain = true)
			switch (direction) {
				case UP:
					mapp[y][x + 1] = Node(CUTTERID, cutterNum, false);
					break;
				case DOWN:
					mapp[y][x - 1] = Node(CUTTERID, cutterNum, false);
					break;
				case LEFT:
					mapp[y - 1][x] = Node(CUTTERID, cutterNum, false);
					break;
				case RIGHT:
					mapp[y + 1][x] = Node(CUTTERID, cutterNum, false);
					break;
			}
			cutterNum++;
			break;



		case COMPOSERID:
			composer[composerNum] = Composer(direction, x, y);

			mapp[y][x] = Node(COMPOSERID, cutterNum, true);
			// Cutter length = 2, so two block will be set on mapp
			// However, only one of them would be a mainblock (isMain = true)
			switch (direction) {
			case UP:
				mapp[y][x + 1] = Node(COMPOSERID, cutterNum, false);
				break;
			case DOWN:
				mapp[y][x - 1] = Node(COMPOSERID, cutterNum, false);
				break;
			case LEFT:
				mapp[y + 1][x] = Node(COMPOSERID, cutterNum, false);
				break;
			case RIGHT:
				mapp[y - 1][x] = Node(COMPOSERID, cutterNum, false);
				break;
			}
			composerNum++;
			break;
	}
}

string World::toString() {
	string output = "[";
	for (int y = 0; y < MAPLENGTH; y++) {

		for (int x = 0; x < MAPLENGTH; x++) {

			if (mapp[y][x].type == GROUNDID) output += "¡ö";
			else if (mapp[y][x].type == BELTID) {
				switch (belt[mapp[y][x].id].dir) {


				case UP:
					output += "¡ü";
					break;
				case DOWN:
					output += "¡ý";
					break;
				case LEFT:
					output += "¡û";
					break;
				case RIGHT:
					output += "¡ú";
					break;
				}


			}
			else if (mapp[y][x].type == CUTTERID) {
				switch (cutter[mapp[y][x].id].dir) {


				case UP:
					output += "=";
					break;
				case DOWN:
					output += "=";
					break;
				case LEFT:
					output += "¡¬";
					break;
				case RIGHT:
					output += "¡¬";
					break;
				}
			}
			else {
				output += to_string(mapp[y][x].type);
			}

		}

		output += "\n";
	}
	output += "]";
	return output;
}

Game::Game() {

	world = World();
}


void Game::loadTestMap() {
	for (int i = 0; i < 12; i++) world.buildAt(BELTID, i, 12, RIGHT);
	world.buildAt(CUTTERID, 12, 12, RIGHT);
	for (int i = 13; i < 15; i++) world.buildAt(BELTID, i, 12, RIGHT);
	for (int i = 12; i < 15; i++) world.buildAt(BELTID, 15, i, DOWN);
	for (int i = 13; i < 16; i++) world.buildAt(BELTID, i, 15, LEFT);
}

Node::Node(int buildingType, int dataId, bool isMainBlock) {
	type = buildingType;
	id = dataId;
	isMain = isMainBlock;
}

Node::Node() {
	type = -1;
	id = -1;
	isMain = false;
}