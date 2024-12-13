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


void World::buildAt(int building, int x, int y, int direction,
					// the following lines are for Acceptor
					int check1items, int goalX, int goalY, int goalColor, int goalShape,
					int check2items, int goalX2, int goalY2, int goalColor2, int goalShape2,
					int check3items, int goalX3, int goalY3, int goalColor3, int goalShape3,
					int check4items, int goalX4, int goalY4, int goalColor4, int goalShape4) {
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
			switch (direction) {
			case UP:
				if (x - 1 < 0) return;
				break;
			case DOWN:
				if (x + 1 >= MAPLENGTH) return;
				break;
			case LEFT:
				if (y + 1 >= MAPLENGTH) return;
				break;
			case RIGHT:
				if (y - 1 < 0) return;
				break;
			}
		
			if (deletedRotatorId->empty()) {
				newId = maxRotatorId;
				maxRotatorId++;
			}
			else {
				newId = deletedRotatorId->top();
				deletedRotatorId->pop();
			}
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
			rotatorNum++;
			rotator[newId] = Rotator(x, y, direction);
			mapp[x][y] = Node(ROTATORID, newId, true);
			
			break;

		case CUTTERID:
			switch (direction) {
			case UP:
				if (x - 1 < 0) return;
				if (y + 1 >= MAPLENGTH) return;
				break;
			case DOWN:
				if (x + 1 >= MAPLENGTH) return;
				if (y - 1 < 0) return;
				break;
			case LEFT:
				if (y - 1 < 0) return;
				if (x - 1 < 0) return;
				break;
			case RIGHT:
				if (y + 1 >= MAPLENGTH) return;
				if (x + 1 >= MAPLENGTH) return;
				break;
			}
			if (deletedCutterId.empty()) {
				newId = maxCutterId;
				maxCutterId++;
			}
			else {
				newId = deletedCutterId.top();
				deletedCutterId.pop();
			}
			switch (direction) {
			case UP:
				buildAt(BELTID, x - 1, y, direction);
				buildAt(BELTID, x - 1, y + 1, direction);
				mapp[x][y + 1] = Node(CUTTERID, newId, false);
				break;
			case DOWN:
				buildAt(BELTID, x + 1, y, direction);
				buildAt(BELTID, x + 1, y - 1, direction);
				mapp[x][y - 1] = Node(CUTTERID, newId, false);
				break;
			case LEFT:
				buildAt(BELTID, x, y - 1, direction);
				buildAt(BELTID, x - 1, y - 1, direction);
				mapp[x - 1][y] = Node(CUTTERID, newId, false);
				break;
			case RIGHT:
				buildAt(BELTID, x, y + 1, direction);
				buildAt(BELTID, x + 1, y + 1, direction);
				mapp[x + 1][y] = Node(CUTTERID, newId, false);
				break;
			}
			// 编号回收
			cutterNum++;
			cutter[newId] = Cutter(direction, x, y);

			mapp[x][y] = Node(CUTTERID, newId, true);
			// Cutter length = 2, so two block will be set on mapp
			// However, only one of them would be a mainblock (isMain = true)
			break;



		case COMPOSERID:
			switch (direction) {
			case UP:
				if (x - 1 < 0) return;
				if (y + 1 >= MAPLENGTH) return;
				break;
			case DOWN:
				if (x + 1 >= MAPLENGTH) return;
				if (y - 1 < 0) return;
				break;
			case LEFT:
				if (y - 1 < 0) return;
				if (x - 1 < 0) return;
				break;
			case RIGHT:
				if (y + 1 >= MAPLENGTH) return;
				if (x + 1 >= MAPLENGTH) return;
				break;
			}

			if (deletedCompId.empty()) {
				newId = maxComposerId;
				maxComposerId++;
			}
			else {
				newId = deletedCompId.top();
				deletedCompId.pop();
			}

			// 编号回收

			switch (direction) {
			case UP:
				buildAt(BELTID, x - 1, y, direction);
				mapp[x][y + 1] = Node(COMPOSERID, newId, false);
				
				break;
			case DOWN:
				buildAt(BELTID, x + 1, y, direction);
				mapp[x][y - 1] = Node(COMPOSERID, newId, false);
				
				break;
			case LEFT:
				buildAt(BELTID, x, y - 1, direction);
				mapp[x - 1][y] = Node(COMPOSERID, newId, false);
				
				break;
			case RIGHT:
				buildAt(BELTID, x, y + 1, direction);
				mapp[x + 1][y] = Node(COMPOSERID, newId, false);
				
				break;
			}

			composerNum++;

			composer[newId] = Composer(direction, x, y);

			mapp[x][y] = Node(COMPOSERID, newId, true);
			// Cutter length = 2, so two block will be set on mapp
			// However, only one of them would be a mainblock (isMain = true)
			break;

		case MINERID:
			mapp[x][y] = Node(MINERID, maxMinerId, true);
			miner[maxMinerId] = Miner(x, y, direction);
			maxMinerId++;
			break;

		case RUBBISHBINID:
			newId = maxRubbishBinId;
			maxRubbishBinId++;
			/*if (!deletedRubbishBinId->empty()) {
				maxRubbishBinId--;
				newId = deletedRubbishBinId->top();
				deletedRubbishBinId->pop();
			}*/
			mapp[x][y] = Node(RUBBISHBINID, newId, true);
			rubbishBin[newId] = RubbishBin(x, y);
			rubbishBinNum++;
			
			break;

		// ADDING THE ACCEPTOR BUIDING STEPS, 1207 by Xin Cao
		case ACCEPTORID:
			for (int dx = 0; dx < 3; dx++) {
				for (int dy = 0; dy < 3; dy++) {
					if (dx < 0 || dx >= MAPLENGTH || dy < 0 || dy >= MAPLENGTH) return;
				}
			}
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

			// For the 1st Quarter-Item
			if (check1items == 1) {
				acceptor[newId].check1items = check1items;
				acceptor[newId].goalX = goalX;
				acceptor[newId].goalY = goalY;
				acceptor[newId].goalShape = goalShape;
				acceptor[newId].goalColor = goalColor;
			}

			// For the 2nd Quarter-Item
			if (check2items == 1) {
				acceptor[newId].check2items = check2items;
				acceptor[newId].goalX2 = goalX2;
				acceptor[newId].goalY2 = goalY2;
				acceptor[newId].goalShape2 = goalShape2;
				acceptor[newId].goalColor2 = goalColor2;
			}

			// For the 3rd Quarter-Item
			if (check3items == 1) {
				acceptor[newId].check3items = check3items;
				acceptor[newId].goalX3 = goalX3;
				acceptor[newId].goalY3 = goalY3;
				acceptor[newId].goalShape3 = goalShape3;
				acceptor[newId].goalColor3 = goalColor3;
			}

			// For the 4th Quarter-Item
			if (check4items == 1) {
				acceptor[newId].check4items = check4items;
				acceptor[newId].goalX4 = goalX4;
				acceptor[newId].goalY4 = goalY4;
				acceptor[newId].goalShape4 = goalShape4;
				acceptor[newId].goalColor4 = goalColor4;
			}


			//int goalX = 0, goalY = 0, goalColor = REDITEM, goalShape = QUARTERSQUARE;
			//int goalX2 = 0, goalY2 = 0, goalColor2 = 0, goalShape2 = 0;

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
	case RUBBISHBINID:
		rubbishBin[id].pos[0] = -1;
		rubbishBinNum--;
		if (id == maxRubbishBinId - 1) {
			maxRubbishBinId--;
		}
		else {
			deletedRubbishBinId->push(id);
		}
		break;

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
	if (buildingType == RUBBISHBINID) {
		int xx = rubbishBin[id].pos[0], yy = rubbishBin[id].pos[1];
		mapp[xx][yy] = Node();
	}
}

//void World::deleteAppendix(int building, int id) 

void World::clearGround(int building, int x, int y, int direction) {
	destroyAppendix(x, y);
	if (mapp[x][y].type != GROUNDID) { destoryAt(x, y);  }
	
	if (building == CUTTERID || building == COMPOSERID) {
		switch (direction) {
		case UP:
			if (mapp[x][y + 1].type != GROUNDID) { destoryAt(x, y + 1);}
			break;
		case DOWN:
			if (mapp[x][y - 1].type != GROUNDID) { destoryAt(x, y - 1);}
			
			break;
		case LEFT:
			if (mapp[x - 1][y].type != GROUNDID) {
				destoryAt(x - 1, y);
			}
			break;
		case RIGHT:
			if (mapp[x + 1][y].type != GROUNDID) {
				destoryAt(x + 1, y);
			}
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

	//world->buildAt(ACCEPTORID, 5, 7, 0, 1, 0, 0, REDITEM, QUARTERSQUARE,
	//									1, 0, 0, WHITEITEM, QUARTERSQUARE,
	//									0, 0, 0, 0, 0,
	//									0, 0, 0, 0, 0);
	//				// The following arguments are for Acceptor



	Item testItem = Item(QUARTERSQUARE, WHITEITEM);
	testItem.colorId[0][1][1] = YELLOWITEM;
	testItem.colorId[0][0][0] = REDITEM;
	testItem.colorId[0][1][0] = BLUEITEM;
	testItem.shapeId[0][1][0] = QUARTERWINDMILL;
	testItem.shapeId[0][1][1] = QUARTERCIRCLE;
	world->putItemAt(testItem, 0, 12);
	world->putItemAt(testItem, 3, 12);
}

void Game::loadShowMap() {
	world->buildAt(MINERID, 1, 0, RIGHT);
	world->buildAt(MINERID, 5, 0, RIGHT);
	world->buildAt(MINERID, 10, 0, RIGHT);
	world->buildAt(MINERID, 15, 0, RIGHT);
	world->buildAt(ACCEPTORID, 10, 10, UP);

	world->buildAt(BELTID, 1, 1, RIGHT);
	world->buildAt(BELTID, 1, 3, RIGHT);
	world->buildAt(BELTID, 2, 3, RIGHT);
	world->buildAt(BELTID, 2, 4, RIGHT);
	world->buildAt(BELTID, 5, 1, RIGHT);
	world->buildAt(BELTID, 2, 6, RIGHT);
	world->buildAt(BELTID, 5, 3, RIGHT);
	world->buildAt(BELTID, 6, 3, RIGHT);
	world->buildAt(BELTID, 5, 5, RIGHT);
	world->buildAt(BELTID, 5, 6, UP);
	world->buildAt(BELTID, 2, 8, RIGHT);
	world->buildAt(BELTID, 4, 6, UP);
	world->buildAt(BELTID, 3, 6, RIGHT);
	world->buildAt(BELTID, 2, 9, DOWN);
	world->buildAt(BELTID, 3, 9, DOWN);
	world->buildAt(BELTID, 4, 9, DOWN);
	world->buildAt(BELTID, 5, 9, DOWN);
	world->buildAt(BELTID, 6, 9, DOWN);
	world->buildAt(BELTID, 7, 9, DOWN);
	world->buildAt(BELTID, 8, 9, DOWN);
	world->buildAt(BELTID, 9, 9, RIGHT);
	world->buildAt(BELTID, 9, 10, RIGHT);
	world->buildAt(BELTID, 10, 1, RIGHT);
	world->buildAt(BELTID, 10, 3, RIGHT);
	world->buildAt(BELTID, 11, 3, RIGHT);
	world->buildAt(BELTID, 11, 5, RIGHT);
	world->buildAt(BELTID, 15, 1, RIGHT);
	world->buildAt(BELTID, 15, 3, RIGHT);
	world->buildAt(BELTID, 16, 3, RIGHT);
	world->buildAt(BELTID, 15, 5, RIGHT);
	world->buildAt(BELTID, 11, 8, RIGHT);
	world->buildAt(BELTID, 11, 6, RIGHT);
	world->buildAt(BELTID, 15, 6, UP);
	world->buildAt(BELTID, 14, 6, UP);
	world->buildAt(BELTID, 13, 6, UP);
	world->buildAt(BELTID, 12, 6, RIGHT);
	world->buildAt(BELTID, 5, 14, RIGHT);
	world->buildAt(BELTID, 5, 13, RIGHT);
	world->buildAt(BELTID, 5, 15, RIGHT);
	world->buildAt(BELTID, 5, 16, DOWN);
	world->buildAt(BELTID, 6, 16, DOWN);
	world->buildAt(BELTID, 7, 16, DOWN);
	world->buildAt(BELTID, 8, 16, LEFT);
	world->buildAt(BELTID, 8, 15, LEFT);
	world->buildAt(BELTID, 8, 14, LEFT);
	world->buildAt(BELTID, 8, 13, UP);
	world->buildAt(BELTID, 7, 13, UP);
	world->buildAt(BELTID, 6, 13, UP);
	world->buildAt(BELTID, 9, 11, DOWN);
	world->buildAt(BELTID, 11, 9, RIGHT);
	world->buildAt(COMPOSERID, 2, 7, RIGHT);
	world->buildAt(COMPOSERID, 11, 7, RIGHT);
	world->buildAt(CUTTERID, 1, 2, RIGHT);
	world->buildAt(CUTTERID, 5, 2, RIGHT);
	world->buildAt(CUTTERID, 10, 2, RIGHT);
	world->buildAt(CUTTERID, 15, 2, RIGHT);
	world->buildAt(ROTATORID, 2, 5, RIGHT);
	world->buildAt(ROTATORID, 5, 4, RIGHT);
	world->buildAt(ROTATORID, 11, 4, RIGHT);
	world->buildAt(ROTATORID, 15, 4, RIGHT);
	world->buildAt(RUBBISHBINID, 1, 4, UP);
	world->buildAt(RUBBISHBINID, 6, 4, UP);
	world->buildAt(RUBBISHBINID, 10, 4, UP);
	world->buildAt(RUBBISHBINID, 16, 4, UP);

	Item yellowSquare = Item(QUARTERSQUARE, YELLOWITEM);
	Item whiteSquare = Item(QUARTERSQUARE, WHITEITEM);	
	Item yellowCircle = Item(QUARTERCIRCLE, YELLOWITEM);
	Item whiteCircle = Item(QUARTERCIRCLE, WHITEITEM);
	world->putItemAt(whiteSquare, 0, 1);
	world->putItemAt(yellowSquare, 0, 10);
	world->putItemAt(yellowCircle, 0, 5);
	world->putItemAt(whiteCircle, 0, 15);
	
	whiteCircle.colorId[0][0][0] = BLUEITEM;
	whiteCircle.shapeId[0][0][0] = QUARTERWINDMILL;

	world->putItemAt(whiteCircle, 13, 8);
	world->putItemAt(yellowCircle, 13, 7);
	world->putItemAt(whiteSquare, 13, 6);
	world->putItemAt(yellowSquare, 13, 5);

	world->putItemAt(whiteCircle, 16, 8);
	world->putItemAt(yellowCircle, 16, 7);
	world->putItemAt(whiteSquare, 16, 6);
	world->putItemAt(yellowSquare, 16, 5);
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
void Game::showInstruction() {
	for (int i = 0; i <= world->maxBeltId; i++) {
		if (world->belt[i].dir == 0) continue;
		switch (world->belt[i].dir) {
		case UP:
			std::cout << "world->buildAt(BELTID," << world->belt[i].pos[0] << "," << world->belt[i].pos[1] << ",UP);" << std::endl;
			break;
		case DOWN:
			std::cout << "world->buildAt(BELTID," << world->belt[i].pos[0] << "," << world->belt[i].pos[1] << ",DOWN);" << std::endl;
			break;
		case LEFT:
			std::cout << "world->buildAt(BELTID," << world->belt[i].pos[0] << "," << world->belt[i].pos[1] << ",LEFT);" << std::endl;
			break;
		case RIGHT:
			std::cout << "world->buildAt(BELTID," << world->belt[i].pos[0] << "," << world->belt[i].pos[1] << ",RIGHT);" << std::endl;
			break;
		}
	}

	for (int i = 0; i <= world->maxComposerId; i++) {
		if (world->composer[i].dir == 0) continue;
		switch (world->composer[i].dir) {
		case UP:
			std::cout << "world->buildAt(COMPOSERID," << world->composer[i].pos[0] << "," << world->composer[i].pos[1] << ",UP);" << std::endl;
			break;
		case DOWN:
			std::cout << "world->buildAt(COMPOSERID," << world->composer[i].pos[0] << "," << world->composer[i].pos[1] << ",DOWN);" << std::endl;
			break;
		case LEFT:
			std::cout << "world->buildAt(COMPOSERID," << world->composer[i].pos[0] << "," << world->composer[i].pos[1] << ",LEFT);" << std::endl;
			break;
		case RIGHT:
			std::cout << "world->buildAt(COMPOSERID," << world->composer[i].pos[0] << "," << world->composer[i].pos[1] << ",RIGHT);" << std::endl;
			break;
		}
	}

	for (int i = 0; i <= world->maxCutterId; i++) {
		if (world->cutter[i].dir == 0) continue;
		switch (world->cutter[i].dir) {
		case UP:
			std::cout << "world->buildAt(CUTTERID," << world->cutter[i].pos[0] << "," << world->cutter[i].pos[1] << ",UP);" << std::endl;
			break;
		case DOWN:
			std::cout << "world->buildAt(CUTTERID," << world->cutter[i].pos[0] << "," << world->cutter[i].pos[1] << ",DOWN);" << std::endl;
			break;
		case LEFT:
			std::cout << "world->buildAt(CUTTERID," << world->cutter[i].pos[0] << "," << world->cutter[i].pos[1] << ",LEFT);" << std::endl;
			break;
		case RIGHT:
			std::cout << "world->buildAt(CUTTERID," << world->cutter[i].pos[0] << "," << world->cutter[i].pos[1] << ",RIGHT);" << std::endl;
			break;
		}
	}

	for (int i = 0; i <= world->maxRotatorId; i++) {
		if (world->rotator[i].dir == 0) continue;
		switch (world->rotator[i].dir) {
		case UP:
			std::cout << "world->buildAt(ROTATORID," << world->rotator[i].pos[0] << "," << world->rotator[i].pos[1] << ",UP);" << std::endl;
			break;
		case DOWN:
			std::cout << "world->buildAt(ROTATORID," << world->rotator[i].pos[0] << "," << world->rotator[i].pos[1] << ",DOWN);" << std::endl;
			break;
		case LEFT:
			std::cout << "world->buildAt(ROTATORID," << world->rotator[i].pos[0] << "," << world->rotator[i].pos[1] << ",LEFT);" << std::endl;
			break;
		case RIGHT:
			std::cout << "world->buildAt(ROTATORID," << world->rotator[i].pos[0] << "," << world->rotator[i].pos[1] << ",RIGHT);" << std::endl;
			break;
		}
	}

	for (int i = 0; i <= world->maxRubbishBinId; i++) {
		if (world->rubbishBin[i].pos[0] == -1) continue;
		std::cout << "world->buildAt(RUBBISHBINID," << world->rubbishBin[i].pos[0] << "," << world->rubbishBin[i].pos[1] << ",UP);" << std::endl;
	}
}