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
			mapp[x][y] = Node(BELTID, beltNum, true);
			beltNum++;
			break;



		case CUTTERID:
			cutter[cutterNum] = Cutter(direction, x, y);

			mapp[x][y] = Node(CUTTERID, cutterNum, true);
			// Cutter length = 2, so two block will be set on mapp
			// However, only one of them would be a mainblock (isMain = true)
			switch (direction) {
				case UP:
					mapp[x][y + 1] = Node(CUTTERID, cutterNum, false);
					break;
				case DOWN:
					mapp[x][y - 1] = Node(CUTTERID, cutterNum, false);
					break;
				case LEFT:
					mapp[x - 1][y] = Node(CUTTERID, cutterNum, false);
					break;
				case RIGHT:
					mapp[x + 1][y] = Node(CUTTERID, cutterNum, false);
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

void World::putItemAt(Item item, int x, int y) {
	int buildingId = mapp[y][x].type;
	switch (buildingId) {
	case BELTID:
		int beltId = mapp[y][x].id; // The id that belt[id] represent the belt at (x,y)
		belt[beltId].grantItem(item);
		belt[beltId].isEmpty = false;
	}
}


string World::toString() {
	string output = "[";
	for (int i = 0; i < MAPLENGTH; i++) {

		for (int j = 0; j < MAPLENGTH; j++) {

			if (mapp[i][j].type == GROUNDID) output += "¡ö";
			else if (mapp[i][j].type == BELTID) {
				if (!belt[mapp[i][j].id].isEmpty) {
					output += "*";
					continue;
				}
				switch (belt[mapp[i][j].id].dir) {


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
			else if (mapp[i][j].type == CUTTERID) {
				switch (cutter[mapp[i][j].id].dir) {


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
				output += to_string(mapp[i][j].type);
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
	for (int i = 0; i < 12; i++) world.buildAt(BELTID, 12, i, RIGHT);
	world.buildAt(CUTTERID, 12, 12, RIGHT);
	for (int i = 13; i < 15; i++) world.buildAt(BELTID, 12, i, RIGHT);
	for (int i = 12; i < 15; i++) world.buildAt(BELTID, i, 15, DOWN);
	for (int i = 13; i < 16; i++) world.buildAt(BELTID, 15, i, LEFT);
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