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
			belt[maxBeltId] = Belt(direction, x, y);
			mapp[x][y] = Node(BELTID, maxBeltId, true);


			// update the idNxt that is prepared for update
			this->refreshBeltAt(x,y,direction);

			beltNum++;
			maxBeltId++;

			break;



		case CUTTERID:
			cutter[maxCutterId] = Cutter(direction, x, y);

			mapp[x][y] = Node(CUTTERID, maxCutterId, true);
			// Cutter length = 2, so two block will be set on mapp
			// However, only one of them would be a mainblock (isMain = true)
			switch (direction) {
				case UP:
					mapp[x][y + 1] = Node(CUTTERID, maxCutterId, false);
					break;
				case DOWN:
					mapp[x][y - 1] = Node(CUTTERID, maxCutterId, false);
					break;
				case LEFT:
					mapp[x - 1][y] = Node(CUTTERID, maxCutterId, false);
					break;
				case RIGHT:
					mapp[x + 1][y] = Node(CUTTERID, maxCutterId, false);
					break;
			}
			maxCutterId++;
			cutterNum++;
			break;



		case COMPOSERID:
			composer[maxComposerId] = Composer(direction, x, y);

			mapp[x][y] = Node(COMPOSERID, maxComposerId, true);
			// Cutter length = 2, so two block will be set on mapp
			// However, only one of them would be a mainblock (isMain = true)
			switch (direction) {
			case UP:
				mapp[x][y + 1] = Node(COMPOSERID, maxComposerId, false);
				break;
			case DOWN:
				mapp[x][y - 1] = Node(COMPOSERID, maxComposerId, false);
				break;
			case LEFT:
				mapp[x - 1][y] = Node(COMPOSERID, maxComposerId, false);
				break;
			case RIGHT:
				mapp[x + 1][y] = Node(COMPOSERID, maxComposerId, false);
				break;
			}
			composerNum++;
			maxComposerId++;
			break;

		case MINERID:
			mapp[x][y] = Node(MINERID, maxMinerId, true);
			miner[maxMinerId] = Miner(x, y, direction);
			maxMinerId++;
			break;

		case RUBBISHBINID:
			mapp[x][y] = Node(RUBBISHBINID, maxRubbishBinId, true);
			rubbishBin[maxRubbishBinId] = RubbishBin(x, y);
			maxRubbishBinId++;
			
			break;
	}
}

void World::putItemAt(Item item, int x, int y) {
	int buildingId = mapp[y][x].type;
	switch (buildingId) {
	case BELTID:
		belt[mapp[y][x].id].grantItem(item);
		belt[mapp[y][x].id].isEmpty = false;
		break;
	case MINERID:
		miner[mapp[y][x].id].setProduct(item);
		miner[mapp[y][x].id].isEmpty = false;
		break;
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

void World::refreshBeltAt(int x, int y, int direction) {
	int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
	//std::cout << "----------------------------------------------" << std::endl;
	//std::cout << "Refresh when adding belt " << maxBeltId << " at position (" << x << "," << y << ")" << std::endl;
	for (int i = 0; i < 4; i++) {
		int xx = x + dir[i][0];
		int yy = y + dir[i][1];
		if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
		if (mapp[xx][yy].type != BELTID) continue;
		int targetId = mapp[xx][yy].id;

		int targetDir = -1;
		switch (i) {
		case UP - 1:
			targetDir = DOWN;
			break;
		case DOWN - 1:
			targetDir = UP;
			break;
		case LEFT - 1:
			targetDir = RIGHT;
			break;
		case RIGHT - 1:
			targetDir = LEFT;
			break;
		}

		//std::cout << "with target direction = ";
		/*switch (targetDir) {
		case UP:
			std::cout << "UP" << std::endl;
			break;
		case DOWN:
			std::cout << "DOWN" << std::endl;
			break;
		case LEFT:
			std::cout << "LEFT" << std::endl;
			break;
		case RIGHT:
			std::cout << "RIGHT" << std::endl;
			break;
		}*/

		//std::cout << "find belt" << " at position (" << xx << "," << yy << ")" << " with direction ";
		/*switch (belt[targetId].dir) {
		case UP:
			std::cout << "UP" << std::endl;
			break;
		case DOWN:
			std::cout << "DOWN" << std::endl;
			break;
		case LEFT:
			std::cout << "LEFT" << std::endl;
			break;
		case RIGHT:
			std::cout << "RIGHT" << std::endl;
			break;
		}*/


		if (belt[targetId].dir == targetDir) {
			belt[targetId].idNxt = maxBeltId;
			/*std::cout << "find previous belt " << targetId << " at position (" << xx << "," << yy << ")";
			std::cout << " the expected direction is ";
			switch (targetDir) {
			case UP:
				std::cout << "UP" << std::endl;
				break;
			case DOWN:
				std::cout << "DOWN" << std::endl;
				break;
			case LEFT:
				std::cout << "LEFT" << std::endl;
				break;
			case RIGHT:
				std::cout << "RIGHT" << std::endl;
				break;
			}*/
		}

	}

	int xx = x + dir[direction - 1][0];
	int yy = y + dir[direction - 1][1];
	if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) return;

	if (mapp[xx][yy].type == BELTID) {
		belt[maxBeltId].idNxt = mapp[xx][yy].id;
		//std::cout << "find next belt " << mapp[xx][yy].id << " at position (" << xx << "," << yy << ")" << std::endl;
	}
}

Game::Game() {

	world = World();
}


void Game::loadTestMap() {
	world.buildAt(MINERID, 12, 0, RIGHT);
	for (int i = 1; i < 12; i++) world.buildAt(BELTID, 12, i, RIGHT);
	world.buildAt(CUTTERID, 12, 12, RIGHT);
	for (int i = 13; i < 14; i++) world.buildAt(BELTID, 12, i, RIGHT);
	world.buildAt(COMPOSERID, 12, 14, RIGHT);
	for (int i = 13; i < 14; i++) world.buildAt(BELTID, 13, i, RIGHT);
	for (int i = 15; i < 19; i++) world.buildAt(BELTID, 13, i, RIGHT);
	world.buildAt(RUBBISHBINID, 13, 19, 0);
	for (int i = 9; i < 13; i++) world.buildAt(BELTID, i, 15, UP);
	world.buildAt(RUBBISHBINID, 8, 15, 0);
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