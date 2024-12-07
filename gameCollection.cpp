#include "gameCollection.h"
#include "constants.h"
#include "gameBuildings.h"
#include <string>
#include <stack>
#include <iostream>

using namespace std;

World::World() {

	for (int i = 0; i < MAPLENGTH; i++)
		for (int j = 0; j < MAPLENGTH; j++)
			mapp[i][j] = Node(GROUNDID, 0, false);
	for (int i = 0; i < 2500; i++) belt[i] = Belt();
	deletedRotatorId = new stack <int>;
	rotator = new Rotator[2500];
	//belt = new Belt[2500];
	//cutter = new Cutter[2500];
	//rubbishBin = new RubbishBin[2500];
	//composer = new Composer[2500];
	//miner = new Miner[2500];
	for (int i = 0; i < 2500; i++) belt[i] = Belt();
	for (int i = 0; i < 2500; i++) cutter[i] = Cutter();
	for (int i = 0; i < 2500; i++) rubbishBin[i] = RubbishBin();
	for (int i = 0; i < 2500; i++) composer[i] = Composer();
	for (int i = 0; i < 2500; i++) miner[i] = Miner();
	for (int i = 0; i < 2500; i++) rotator[i] = Rotator();
	for (int i = 0; i < 2500; i++) acceptor[i] = Acceptor();
}


void World::buildAt(int building, int x, int y, int direction) {
	clearGround(building,x,y,direction);
	int newId;
	switch (building) {
		case BELTID:
			if (deletedBeltId.empty()) {
				belt[maxBeltId] = Belt(direction, x, y);
				mapp[x][y] = Node(BELTID, maxBeltId, true);
				maxBeltId++;
			}
			else {
				belt[deletedBeltId.top()] = Belt(direction, x, y);
				mapp[x][y] = Node(BELTID, deletedBeltId.top(), true);
				deletedBeltId.pop();
			}
			this->refreshBeltAt(x, y, direction);
			// update the idNxt that is prepared for update
			beltNum++;

			break;

		case ROTATORID:
			if (deletedRotatorId->empty()) {
				newId = maxRotatorId;
				maxRotatorId++;
			}
			else {
				newId = deletedRotatorId->top();
				deletedRotatorId->pop();
			}
			rotatorNum++;
			rotator[newId] = Rotator(x, y, direction);
			mapp[x][y] = Node(ROTATORID, newId, true);
			switch (direction) {
			case UP:
				buildAt(BELTID, x - 1, y, direction);
				break;
			case DOWN:
				buildAt(BELTID, x + 1, y, direction);
				break;
			case LEFT:
				buildAt(BELTID, x, y - 1, direction);
				break;
			case RIGHT:
				buildAt(BELTID, x, y + 1, direction);
				break;
			}
			break;

		case CUTTERID:
			if (deletedCutterId.empty()) {
				newId = maxCutterId;
				maxCutterId++;
			}
			else {
				newId = deletedCutterId.top();
				deletedCutterId.pop();
			}
			// 编号回收
			cutterNum++;
			cutter[newId] = Cutter(direction, x, y);

			mapp[x][y] = Node(CUTTERID, newId, true);
			// Cutter length = 2, so two block will be set on mapp
			// However, only one of them would be a mainblock (isMain = true)
			switch (direction) {
				case UP:
					mapp[x][y + 1] = Node(CUTTERID, newId, false);
					buildAt(BELTID, x - 1, y, direction);
					buildAt(BELTID, x - 1, y+1, direction);
					break;
				case DOWN:
					mapp[x][y - 1] = Node(CUTTERID, newId, false);
					buildAt(BELTID, x + 1, y, direction);
					buildAt(BELTID, x + 1, y - 1, direction);
					break;
				case LEFT:
					mapp[x - 1][y] = Node(CUTTERID, newId, false);
					buildAt(BELTID, x, y - 1, direction);
					buildAt(BELTID, x - 1, y - 1, direction);
					break;
				case RIGHT:
					mapp[x + 1][y] = Node(CUTTERID, newId, false);
					buildAt(BELTID, x, y + 1, direction);
					buildAt(BELTID, x + 1, y + 1, direction);
					break;
			}
			break;



		case COMPOSERID:
			if (deletedCompId.empty()) {
				newId = maxComposerId;
				maxComposerId++;
			}
			else {
				newId = deletedCompId.top();
				deletedCompId.pop();
			}
			// 编号回收
			composerNum++;

			composer[newId] = Composer(direction, x, y);

			mapp[x][y] = Node(COMPOSERID, newId, true);
			// Cutter length = 2, so two block will be set on mapp
			// However, only one of them would be a mainblock (isMain = true)
			switch (direction) {
			case UP:
				mapp[x][y + 1] = Node(COMPOSERID, newId, false);
				buildAt(BELTID, x - 1, y, direction);
				break;
			case DOWN:
				mapp[x][y - 1] = Node(COMPOSERID, newId, false);
				buildAt(BELTID, x + 1, y, direction);
				break;
			case LEFT:
				mapp[x - 1][y] = Node(COMPOSERID, newId, false);
				buildAt(BELTID, x, y - 1, direction);
				break;
			case RIGHT:
				mapp[x + 1][y] = Node(COMPOSERID, newId, false);
				buildAt(BELTID, x, y + 1, direction);
				break;
			}
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

		// ADDING THE ACCEPTOR BUIDING STEPS, 1207 by Xin Cao
		case ACCEPTORID:
			clearGround(ACCEPTORID, x, y, direction);
			int newId;
			if (deletedAcceptorId.empty()) {
				newId = maxAcceptorId;
				maxAcceptorId++;
			}
			else {
				newId = deletedAcceptorId.top();
				deletedAcceptorId.pop();
			}
			acceptorNum++;
			acceptor[newId] = Acceptor(x, y);

			// Fill 3x3 area in the map:
			// The main block is at (x+1, y+1)
			for (int dx = 0; dx < 3; dx++) {
				for (int dy = 0; dy < 3; dy++) {
					bool mainBlock = (dx == 1 && dy == 1);
					mapp[x + dx][y + dy] = Node(ACCEPTORID, newId, mainBlock);
				}
			}
			break;
		// Over

	}
}

void World::destoryAt(int x, int y) {
	int buildingType = mapp[x][y].type;
	int buildingId = mapp[x][y].id;
	if (buildingType == GROUNDID) return;

	if (buildingType == BELTID) deleteBeltLink(buildingId);

	//deleteAppendix(buildingType,buildingId);
	deleteInMapp(buildingType, buildingId);
	deleteInArray(buildingType, buildingId);

	
}

void World::destroyAppendix(int x, int y)
{
	int Id = mapp[x][y].id;
	if (mapp[x][y].type == BELTID) {
		int delDir = belt[Id].dir;
		switch (delDir) {
		case UP:x += 1; break;
		case DOWN:x -= 1; break;
		case LEFT:y += 1; break;
		case RIGHT:y -= 1; break;
		}
		switch (mapp[x][y].type) {
		case CUTTERID:if (cutter[mapp[x][y].id].dir == delDir) { destroyAppendix(x, y); destoryAt(x, y); break; }
		case COMPOSERID:if (composer[mapp[x][y].id].dir == delDir) { destroyAppendix(x, y); destoryAt(x, y); break; }
		case ROTATORID:if (rotator[mapp[x][y].id].dir == delDir) { destroyAppendix(x, y); destoryAt(x, y); break; }
		}
	}
	if (mapp[x][y].type == ROTATORID) {
		int direction = rotator[Id].dir;
		int x = rotator[Id].pos[0], y = rotator[Id].pos[1];
		switch (direction) {
		case UP:
			destoryAt(x - 1, y);
			break;
		case DOWN:
			destoryAt(x + 1, y);
			break;
		case LEFT:
			destoryAt(x, y - 1);
			break;
		case RIGHT:
			destoryAt(x, y + 1);
			break;
		}
	}
	if (mapp[x][y].type == COMPOSERID) {
		int direction = composer[Id].dir;
		int x = composer[Id].pos[0], y = composer[Id].pos[1];
		switch (direction) {
		case UP:
			destoryAt(x - 1, y);
			break;
		case DOWN:
			destoryAt(x + 1, y);
			break;
		case LEFT:
			destoryAt(x, y - 1);
			break;
		case RIGHT:
			destoryAt(x, y + 1);
			break;
		}
	}
	if (mapp[x][y].type == CUTTERID) {
		int direction = cutter[Id].dir;
		int x = cutter[Id].pos[0], y = cutter[Id].pos[1];
		switch (direction) {
		case UP:
			destoryAt(x - 1, y);
			destoryAt(x - 1, y + 1);
			break;
		case DOWN:
			destoryAt(x + 1, y);
			destoryAt(x + 1, y - 1);
			break;
		case LEFT:
			destoryAt(x, y - 1);
			destoryAt(x - 1, y - 1);
			break;
		case RIGHT:
			destoryAt(x, y + 1);
			destoryAt(x + 1, y + 1);
			break;
		}
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

void World::deleteInArray(int building, int id) {
	switch (building) {
	case BELTID:
		belt[id].dir = 0;
		belt[id].itemNow = Item();
		belt[id].itemPre = Item();
		beltNum--;
		if (id == maxBeltId) {
			//删的是末尾的，不用特意加指针了
			maxBeltId--;
			break;
		}
		deletedBeltId.push(id);
		break;
	case ROTATORID:
		rotator[id].dir = 0;
		rotator[id].Output = Item();
		rotator[id].OutputPre = Item();
		rotatorNum--;
		if (id == maxRotatorId) {
			maxRotatorId--;
			break;
		}
		deletedRotatorId->push(id);
		break;
	case COMPOSERID:
		composer[id].dir = 0;
		composer[id].Output = Item();
		composer[id].OutputPre = Item();
		composer[id].OutisEmpty = true;
		composerNum--;
		if (id == maxComposerId) {
			maxComposerId--;
			break;
		}
		deletedCompId.push(id);
		break;
	case CUTTERID:
		cutter[id].dir = 0;
		cutter[id].OutputMain = Item();
		cutter[id].OutputSub = Item();
		cutter[id].OutputMainPre = Item();
		cutter[id].OutputSubPre = Item();
		cutter[id].isEmptyMain = true;
		cutter[id].isEmptySub = true;
		cutterNum--;
		if (id == maxCutterId) {
			maxCutterId--;
			break;
		}
		deletedCutterId.push(id);
		break;

	// FOR ACCEPTOR, by Xin Cao on 1207
	case ACCEPTORID:
		acceptor[id].isEmpty = true;
		acceptor[id].storedItem = Item();
		acceptorNum--;
		if (id == maxAcceptorId - 1) {
			maxAcceptorId--;
		}
		else {
			deletedAcceptorId.push(id);
		}
		break;
	// Over
	}

}

void World::deleteInMapp(int buildingType, int id) {
	if (buildingType == BELTID) {
		int xx = belt[id].pos[0], yy = belt[id].pos[1];
		mapp[xx][yy] = Node();
	}
	if (buildingType == ROTATORID) {
		int xx = rotator[id].pos[0], yy = rotator[id].pos[1];
		mapp[xx][yy] = Node();
	}
	if (buildingType == COMPOSERID) {

		int xx = composer[id].pos[0], yy = composer[id].pos[1];
		mapp[xx][yy] = Node();
		int direction = composer[id].dir;
		//删除另一部分
		switch (direction) {
		case UP:
			mapp[xx][yy + 1] = Node();
			break;
		case DOWN:
			mapp[xx][yy - 1] = Node();
			break;
		case LEFT:
			mapp[xx - 1][yy] = Node();
			break;
		case RIGHT:
			mapp[xx + 1][yy] = Node();
			break;
		}
	}
	if (buildingType == CUTTERID) {
		int xx = cutter[id].pos[0], yy = cutter[id].pos[1];
		mapp[xx][yy] = Node();
		int direction = cutter[id].dir;
		//删除另一部分
		switch (direction) {
		case UP:
			mapp[xx][yy + 1] = Node();
			break;
		case DOWN:
			mapp[xx][yy - 1] = Node();
			break;
		case LEFT:
			mapp[xx - 1][yy] = Node();
			break;
		case RIGHT:
			mapp[xx + 1][yy] = Node();
			break;
		}
	}
	// FOR ACCEPTOR, by Xin Cao on 1207
	if (buildingType == ACCEPTORID) {
		int xx = acceptor[id].pos[0], yy = acceptor[id].pos[1];
		for (int dx = 0; dx < 3; dx++) {
			for (int dy = 0; dy < 3; dy++) {
				mapp[xx + dx][yy + dy] = Node();
			}
		}
	}
	// Over
}

//void World::deleteAppendix(int building, int id) 

void World::clearGround(int building, int x, int y, int direction) {
	destroyAppendix(x, y);
	if (building == BELTID || building == ROTATORID) {
		if (mapp[x][y].type != GROUNDID) destoryAt(x, y);
	}
	if (building == CUTTERID || building == COMPOSERID) {
		switch (direction) {
		case UP:
			if (mapp[x][y + 1].type != GROUNDID) destoryAt(x, y + 1);
			break;
		case DOWN:
			if (mapp[x][y - 1].type != GROUNDID) destoryAt(x, y - 1);
			break;
		case LEFT:
			if (mapp[x - 1][y].type != GROUNDID) destoryAt(x - 1, y);
			break;
		case RIGHT:
			if (mapp[x + 1][y].type != GROUNDID) destoryAt(x + 1, y);
			break;
		}
	}
}

string World::toString() {
	string output = "[";
	for (int i = 0; i < MAPLENGTH; i++) {

		for (int j = 0; j < MAPLENGTH; j++) {

			if (mapp[i][j].type == GROUNDID) output += "■";
			else if (mapp[i][j].type == BELTID) {
				if (!belt[mapp[i][j].id].isEmpty) {
					output += "*";
					continue;
				}
				switch (belt[mapp[i][j].id].dir) {


				case UP:
					output += "↑";
					break;
				case DOWN:
					output += "↓";
					break;
				case LEFT:
					output += "←";
					break;
				case RIGHT:
					output += "→";
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
					output += "‖";
					break;
				case RIGHT:
					output += "‖";
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
	int id = mapp[x][y].id;
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
		if (belt[targetId].dir == targetDir) {
			belt[id].idBef[belt[id].idBef[0]++] = targetId;
		}

	}


	int xx = x + dir[direction - 1][0];
	int yy = y + dir[direction - 1][1];
	if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) return;

	if (mapp[xx][yy].type == BELTID) {
		int idN = mapp[xx][yy].id;
		belt[idN].idBef[belt[idN].idBef[0]++] = id;
	}
}

void World::deleteBeltLink(int id) {
	int x = belt[id].pos[0], y = belt[id].pos[1];
	int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
	int direction = belt[id].dir;

	int xx = x + dir[direction - 1][0];
	int yy = y + dir[direction - 1][1];
	if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) return;

	if (mapp[xx][yy].type == BELTID) {
		int idN = mapp[xx][yy].id, indexDel = 0;
		for (int i = 1; i < belt[idN].idBef[0]; i++) {
			if (belt[idN].idBef[i] == id) { indexDel = i; break; }
		}
		belt[idN].idBef[0]--;
		for (int i = 1; i < belt[idN].idBef[0]; i++) {
			if (i >= indexDel) belt[idN].idBef[i] = belt[idN].idBef[i + 1];
		}
		
	}

}

Game::Game() {

	world = new World();
}


void Game::loadTestMap() {
	world->buildAt(MINERID, 12, 0, RIGHT);
	for (int i = 1; i < 6; i++) world->buildAt(BELTID, 12, i, RIGHT);
	for (int i = 8; i < 12; i++) world->buildAt(BELTID, 12, i, RIGHT);
	world->buildAt(CUTTERID, 12, 12, RIGHT);
	world->buildAt(ROTATORID, 12, 6, RIGHT);
	//for (int i = 13; i < 14; i++) world.buildAt(BELTID, 12, i, RIGHT);
	world->buildAt(COMPOSERID, 12, 14, RIGHT);
	//world.buildAt(BELTID, 12, 15, RIGHT);
	//for (int i = 13; i < 14; i++) world.buildAt(BELTID, 13, i, RIGHT);
	for (int i = 16; i < 19; i++) world->buildAt(BELTID, 13, i, RIGHT);
	world->buildAt(RUBBISHBINID, 13, 19, 0);
	for (int i = 9; i < 13; i++) world->buildAt(BELTID, i, 16, UP);
	world->buildAt(RUBBISHBINID, 8, 16, 0);

	// TEST THE ACCEPTOR
	// Build some belts
	for (int i = 3; i < 7; i++)
		world->buildAt(BELTID, 8, i, RIGHT);

	for (int i = 9; i < 12; i++)
		world->buildAt(BELTID, i, 3, UP);
	// Add another belt with dir=UP manually

	world->buildAt(ACCEPTORID, 7, 7, 0);
}



Node::Node(int buildingType, int dataId, bool isMainBlock) {
	type = buildingType;
	id = dataId;
	isMain = isMainBlock;
}

Node::Node() {
	type = GROUNDID;
	id = -1;
	isMain = false;
}