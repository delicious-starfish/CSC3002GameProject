#include "gameLogic.h"
#include "gameCollection.h"
#include "constants.h"
#include "gameBuildings.h"
#include "gameItem.h"
#include <iostream>

void logicTick(World * world) {
	setPreItems(world);

	buildingInput(world);

	beltLogic(world);

	buildingOutput(world);
}

void setPreItems(World * world) {
	for (int i = 0; i < world->maxBeltId; i++) {
		if (world->belt[i].exist()) {
			world->belt[i].isMoved = false;
			world->belt[i].itemPre = world->belt[i].itemNow;
		}
	}
	for (int i = 0; i < world->maxCutterId; i++) {
		world->cutter[i].isMovedMain = false;
		world->cutter[i].isMovedSub = false;
		world->cutter[i].OutputMainPre = world->cutter[i].OutputMain;
		world->cutter[i].OutputSubPre = world->cutter[i].OutputSub;
	}
	for (int i = 0; i < world->maxComposerId; i++) {
		world->composer[i].isMoved = false;
		world->composer[i].OutputPre = world->composer[i].Output;
	}
	for (int i = 0; i < world->maxMinerId; i++) {
		world->miner[i].isMoved = false;
	}
	for (int i = 0; i < world->maxRotatorId; i++) {
		world->rotator[i].isMoved = false;
		world->rotator[i].OutputPre = world->rotator[i].Output;
	}
	for (int i = 0; i < world->maxAcceptorId; i++) {
		world->acceptor[i].isMoved = false;
	}
}

void beltLogic(World * world) {
	bool * book = new bool[world->maxBeltId];
	// book means whether this belt has been updated
	for (int i = 0; i < world->maxBeltId; i++) book[i] = false;
	for (int i = 0; i < world->maxBeltId; i++) {
		if (!world->belt[i].exist()) continue;
		world->belt[i].isStuck = false;
		world->belt[i].nxtStuck = false;
	}

	for (int i = 0; i < world->maxBeltId; i++) {

		if (!world->belt[i].exist()) continue;
		if (book[i]) continue;
		//This belt has been updated

		if(world->belt[i].isEmpty)
			belt_FindEndAndUpdate(world, book, i);
	}

	for (int i = 0; i < world->maxBeltId; i++) {
		if (!book[i]) world->belt[i].isStuck = true;
		if (world->belt[i].isStuck) expand_nxtStuck(world,i);
	}


	delete [] book;
}

void buildingInput(World * world) {

	/// FOR DEFINING THE ACCEPTOR CRITERIA
	//int goalX = 0, goalY = 0, goalColor = REDITEM, goalShape = QUARTERSQUARE;
	//int goalX2 = 0, goalY2 = 0, goalColor2 = 0, goalShape2 = 0;

	int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
	//å¤„ç†åˆ‡å‰²å™¨çš„è¾“å…¥
	for (int i = 0; i < world->maxCutterId; i++) {
		//std::cout << "-----------------------------------" << "\næŸ¥è¯¢åˆ‡å‰²å™¨ç¼–å? << i << std::endl;
		if (world->cutter[i].dir == 0) continue;
		// It means that the cutter hasn't been built or has just been removed

		Cutter * cutter = &world->cutter[i];
		int x = cutter->pos[0], y = cutter->pos[1];
		int xx = x + dir[cutter->dir - 1][0], yy = y + dir[cutter->dir - 1][1];
		//std::cout << "æŸ¥è¯¢åæ ‡(" << xx << "," << yy << ")çš„è¾“å…? << std::endl;
		if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
		if (world->mapp[xx][yy].type == BELTID && world->belt[world->mapp[xx][yy].id].dir == cutter->dir) {
			if (world->belt[world->mapp[xx][yy].id].isEmpty != true) {
				// æå–è¾“å…¥
				cutter->input(world->belt[world->mapp[xx][yy].id]);
				//std::cout << "æ£€æµ‹åˆ°è¾“å…¥ï¼Œåæ ?" << xx << "," << yy << ")" << std::endl;
			}
		}
	}

	//å¤„ç†åžƒåœ¾æ¡¶çš„è¾“å…¥
	for (int i = 0; i < world->maxRubbishBinId; i++) {
		if (world->rubbishBin[i].pos[0] == -1) continue;
		RubbishBin* bin = &world->rubbishBin[i];
		int x = bin->pos[0], y = bin->pos[1];

		for (int d = 1; d <= 4; d++) {
			// æœç´¢å››ä¸ªæ–¹å‘æŒ‡å‘åžƒåœ¾æ¡¶çš„ä¼ é€å¸¦

			int xx = x + dir[d - 1][0], yy = y + dir[d - 1][1];
			if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;

			if (world->mapp[xx][yy].type == BELTID && world->belt[world->mapp[xx][yy].id].dir == d) {
				if (world->belt[world->mapp[xx][yy].id].isEmpty != true) {
					// æå–è¾“å…¥
					bin->input(world->belt[world->mapp[xx][yy].id]);

				}
			}
		}
	}
	//å¤„ç†åˆæˆå™¨çš„è¾“å…¥

	for (int i = 0; i < world->maxComposerId; i++) {
		//std::cout << "-----------------------------------" << "\næŸ¥è¯¢åˆ‡å‰²å™¨ç¼–å? << i << std::endl;
		if (world->composer[i].dir == 0) continue;
		// It means that the cutter hasn't been built or has just been removed

		Composer* composer = &world->composer[i];
		int x = composer->pos[0], y = composer->pos[1];
		int xx = x + dir[composer->dir - 1][0], yy = y + dir[composer->dir - 1][1];
		int inputBeltIdMain = -1, inputBeltIdSub = -1;
		//std::cout << "æŸ¥è¯¢åæ ‡(" << xx << "," << yy << ")çš„è¾“å…? << std::endl;
		if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
		if (world->mapp[xx][yy].type == BELTID && world->belt[world->mapp[xx][yy].id].dir == composer->dir) {
			if (world->belt[world->mapp[xx][yy].id].isEmpty != true) {
				// æå–è¾“å…¥
				inputBeltIdMain = world->mapp[xx][yy].id;
				//std::cout << "æ£€æµ‹åˆ°è¾“å…¥ï¼Œåæ ?" << xx << "," << yy << ")" << std::endl;
			}
		}

		//å¤„ç†å‰¯æ ¼çš„è¾“å…?
		xx = composer->getSubx() + dir[composer->dir - 1][0]; yy = composer->getSuby() + dir[composer->dir - 1][1];
		if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
		if (world->mapp[xx][yy].type == BELTID && world->belt[world->mapp[xx][yy].id].dir == composer->dir) {
			if (world->belt[world->mapp[xx][yy].id].isEmpty != true) {
				// æå–è¾“å…¥
				inputBeltIdSub = world->mapp[xx][yy].id;
				//std::cout << "æ£€æµ‹åˆ°è¾“å…¥ï¼Œåæ ?" << xx << "," << yy << ")" << std::endl;
			}
		}

		if (inputBeltIdMain != -1 && inputBeltIdSub != -1) composer->input(world->belt[inputBeltIdMain], world->belt[inputBeltIdSub]);
	}

		//Rotator
	for (int i = 0; i < world->maxRotatorId; i++) {
		if (world->rotator[i].dir == 0) continue;
		// It means that the rotator hasn't been built or has just been removed

		Rotator * rotator = &world->rotator[i];
		int x = rotator->pos[0], y = rotator->pos[1];
		int xx = x + dir[rotator->dir - 1][0], yy = y + dir[rotator->dir - 1][1];
		int inputBeltId = -1;
		if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
		if (world->mapp[xx][yy].type == BELTID && world->belt[world->mapp[xx][yy].id].dir == rotator->dir) {
			if (world->belt[world->mapp[xx][yy].id].isEmpty != true) {
				inputBeltId = world->mapp[xx][yy].id;
			}
		}

		if (inputBeltId != -1) rotator->input(world->belt[inputBeltId]);
	}

	// FOR ACCEPTOR, by Xin Cao, 1207
	for (int i = 0; i < world->maxAcceptorId; i++) {
		
		if (world->acceptor[i].pos[0] == -1) continue;
		Acceptor* acc = &world->acceptor[i];
		int cx = acc->pos[0] + 1;
		int cy = acc->pos[1] + 1;

		//1215: Change to a new target when totalScore >= 20

		//CHANGE TO TARGET 2: ...

		if (totalScore >= 20) {
			Item Target = Item(QUARTERSQUARE, WHITEITEM);

			Target.shapeId[0][0][1] = QUARTERCIRCLE;
			Target.shapeId[0][1][1] = QUARTERWINDMILL;
			//Target.colorId[0][0][0] = WHITEITEM;
			Target.colorId[0][0][1] = YELLOWITEM;
			Target.colorId[0][1][0] = BLUEITEM;

			world->putItemAt(Target, 11, 11);

		}

		// CHANGE TO TARGET 3: ...

		if (totalScore >= 40) {
			Item Target = Item(QUARTERSQUARE, WHITEITEM);

			Target.shapeId[0][1][0] = QUARTERCIRCLE;
			Target.shapeId[0][1][1] = QUARTERWINDMILL;
			//Target.colorId[0][0][0] = WHITEITEM;
			Target.colorId[0][0][0] = YELLOWITEM;
			Target.colorId[0][0][1] = REDITEM;

			 //Delete one quarterItem ...
			Target.shapeId[0][1][1] = 0;
			//Target.colorId[0][0][0] = WHITEITEM;
			Target.colorId[0][1][1] = 0;

			world->putItemAt(Target, 11, 11);

		}


		// CHANGE TO TARGET 4: ...

		if (totalScore >= 60) {
			Item Target = Item(QUARTERSQUARE, WHITEITEM);

			Target.shapeId[0][1][0] = QUARTERCIRCLE;
			Target.shapeId[0][1][1] = QUARTERWINDMILL;
			//Target.colorId[0][0][0] = WHITEITEM;
			Target.colorId[0][0][0] = YELLOWITEM;
			Target.colorId[0][0][1] = REDITEM;

			world->putItemAt(Target, 11, 11);

		}


		// CHANGE TO TARGET 5: ...

		if (totalScore >= 80) {
			Item Target = Item(QUARTERSQUARE, WHITEITEM);

			//Target.shapeId[0][1][0] = QUARTERCIRCLE;
			Target.shapeId[0][1][1] = QUARTERWINDMILL;
			//Target.colorId[0][0][0] = WHITEITEM;
			Target.colorId[0][0][0] = YELLOWITEM;
			//Target.colorId[0][0][1] = REDITEM;

			// Delete two quarterItems ...
			//Target.shapeId[0][0][1] = 0;
			Target.colorId[0][0][1] = 0;
			Target.shapeId[0][0][1] = 0;
			//Target.shapeId[0][1][0] = 0;
			//Target.colorId[0][1][0] = 0;

			world->putItemAt(Target, 11, 11);

		}

		 //Criteria to win is 100, after completing all the 5 targets, each 20
			// DEFINED #define SCOREREQUEST_TEST 100



		 //Wrote four directions, two blocks away:

		 //Up direction source: (cx-2, cy), belt must be DOWN(2)
		if (cx - 2 >= 0 && world->mapp[cx - 2][cy].type == BELTID) {
			
			int bId = world->mapp[cx - 2][cy].id;
			if (!world->belt[bId].isEmpty && world->belt[bId].dir == DOWN) {
				acc->input(world->belt[bId]);
			}
		}

		// Down direction source: (cx+2, cy), belt must be UP(1)
		if (cx + 2 < MAPLENGTH && world->mapp[cx + 2][cy].type == BELTID) {
			int bId = world->mapp[cx + 2][cy].id;
			if (!world->belt[bId].isEmpty && world->belt[bId].dir == UP) {
				acc->input(world->belt[bId]);
			}
		}

		// Left direction source: (cx, cy-2), belt must be RIGHT(4)
		if (cy - 2 >= 0 && world->mapp[cx][cy - 2].type == BELTID) {
			int bId = world->mapp[cx][cy - 2].id;
			if (!world->belt[bId].isEmpty && world->belt[bId].dir == RIGHT) {
				acc->input(world->belt[bId]);
			}
		}

		// Right direction source: (cx, cy+2), belt must be LEFT(3)
		if (cy + 2 < MAPLENGTH && world->mapp[cx][cy + 2].type == BELTID) {
			int bId = world->mapp[cx][cy + 2].id;
			if (!world->belt[bId].isEmpty && world->belt[bId].dir == LEFT) {
				acc->input(world->belt[bId]);
			}
		}
	}
	// Over

	return;
}

void buildingOutput(World * world) {
	int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
	// å¤„ç†cutter
	for (int i = 0; i < world->maxCutterId; i++) {
		if (world->cutter[i].dir == 0) continue;
		if (world->cutter[i].isOperated) { world->cutter[i].isOperated = false; continue; }
		//std::cout << "-----------------------------------" << "\næŸ¥è¯¢åˆ‡å‰²å™¨ç¼–å? << i << std::endl;
		Cutter* cutter = &world->cutter[i];

		if(!cutter->isEmptyMain){
			//è¾“å‡ºmainçš„éƒ¨åˆ?
			int x = cutter->pos[0], y = cutter->pos[1];
			int xx = x + dir[cutter->dir - 1][0], yy = y + dir[cutter->dir - 1][1];
			if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
			if (world->mapp[xx][yy].type == BELTID) {
				if (world->belt[world->mapp[xx][yy].id].isEmpty) {
					// 1.è¿™æ˜¯æ¡ä¼ é€å¸¦
					// 2.è¿™æ¡å¸¦å­æ˜¯ç©ºçš?	
					cutter->outputMain(world->belt[world->mapp[xx][yy].id]);
				}
			}
		}
		if (!cutter->isEmptySub) {
			//è¾“å‡ºsubçš„éƒ¨åˆ?
			int x = cutter->getSubx(), y = cutter->getSuby();
			int xx = x + dir[cutter->dir - 1][0], yy = y + dir[cutter->dir - 1][1];
			if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
			if (world->mapp[xx][yy].type == BELTID) {
				if (world->belt[world->mapp[xx][yy].id].isEmpty) {
					// 1.è¿™æ˜¯æ¡ä¼ é€å¸¦
					// 2.è¿™æ¡å¸¦å­æ˜¯ç©ºçš?	
					cutter->outputSub(world->belt[world->mapp[xx][yy].id]);
				}
			}
		}
	}

	//å¤„ç†Miner
	for (int i = 0; i < world->maxMinerId; i++) {
		if (world->miner[i].dir == 0) continue;
		Miner* miner = &world->miner[i];

		if (!miner->isEmpty) {
			//è¾“å‡ºmainçš„éƒ¨åˆ?
			int x = miner->pos[0], y = miner->pos[1];
			int xx = x + dir[miner->dir - 1][0], yy = y + dir[miner->dir - 1][1];
			if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
			if (world->mapp[xx][yy].type == BELTID) {
				if (world->belt[world->mapp[xx][yy].id].isEmpty) {
					// 1.è¿™æ˜¯æ¡ä¼ é€å¸¦
					// 2.è¿™æ¡å¸¦å­æ˜¯ç©ºçš?	
					miner->output(world->belt[world->mapp[xx][yy].id]);
				}
			}
		}
	
	}
	//å¤„ç†Composer

	for (int i = 0; i < world->maxComposerId; i++) {
		if (world->composer[i].dir == 0) continue;
		if (world->composer[i].isOperated) { world->composer[i].isOperated = false; continue; }
		//std::cout << "-----------------------------------" << "\næŸ¥è¯¢åˆ‡å‰²å™¨ç¼–å? << i << std::endl;
		Composer* composer = &world->composer[i];

		if (!composer->OutisEmpty) {
			int x = composer->pos[0], y = composer->pos[1];
			int xx = x + dir[composer->dir - 1][0], yy = y + dir[composer->dir - 1][1];
			if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
			if (world->mapp[xx][yy].type == BELTID) {
				if (world->belt[world->mapp[xx][yy].id].isEmpty) {
					// 1.è¿™æ˜¯æ¡ä¼ é€å¸¦
					// 2.è¿™æ¡å¸¦å­æ˜¯ç©ºçš?	
					composer->output(world->belt[world->mapp[xx][yy].id]);
				}
			}
		}

	}

		//Rotator
	for (int i = 0; i < world->maxRotatorId; i++) {
		if (world->rotator[i].dir == 0) continue;
		if (world->rotator[i].isOperated) { world->rotator[i].isOperated = false; continue; }
		Rotator* rotator = &world->rotator[i];

		if (!rotator->OutisEmpty) {
			int x = rotator->pos[0], y = rotator->pos[1];
			int xx = x + dir[rotator->dir - 1][0], yy = y + dir[rotator->dir - 1][1];
			if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
			if (world->mapp[xx][yy].type == BELTID) {
				if (world->belt[world->mapp[xx][yy].id].isEmpty) {
					rotator->output(world->belt[world->mapp[xx][yy].id]);
				}
			}
		}
	}
}

void belt_FindEndAndUpdate(World * world, bool footprint[], int nowId) {

	if (footprint[nowId]) return;
	footprint[nowId] = true;
	if (!world->belt[nowId].isEmpty) {
		world->belt[nowId].isStuck = true;
		return;
	}

	for (int i = 1; i < world->belt[nowId].idBef[0]; i++) {
		int idB = world->belt[nowId].idBef[i];
		if (footprint[idB]) continue;
		if (world->belt[idB].isEmpty) continue;
		if (!world->belt[nowId].isEmpty) break;

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++) {
					world->belt[nowId].itemNow.colorId[i][j][k] = world->belt[idB].itemNow.colorId[i][j][k];
					world->belt[idB].itemNow.colorId[i][j][k] = 0;
					world->belt[nowId].itemNow.shapeId[i][j][k] = world->belt[idB].itemNow.shapeId[i][j][k];
					world->belt[idB].itemNow.shapeId[i][j][k] = 0;
				}
		world->belt[nowId].isEmpty = false;
		world->belt[nowId].isMoved = true;
		world->belt[idB].isEmpty = true;
		belt_FindEndAndUpdate(world, footprint, idB);

	}

}

void expand_nxtStuck(World* world, int id) {

	for (int i = 1; i < world->belt[id].idBef[0]; i++) {
		int idB = world->belt[id].idBef[i];
		world->belt[idB].nxtStuck = true;

	}
}
