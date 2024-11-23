#include "gameLogic.h"
#include "gameCollection.h"
#include "constants.h"
#include "gameBuildings.h"
#include "gameItem.h"
#include <iostream>

void logicTick(World& world) {
	if(isBuildingOperated)
	buildingInput(world);

	beltLogic(world);

	if(!isBuildingOperated)
	buildingOutput(world);
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

void buildingInput(World & world) {
	int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
	//�����и���������
	for (int i = 0; i < world.maxCutterId; i++) {
		//std::cout << "-----------------------------------" << "\n��ѯ�и������" << i << std::endl;
		if (world.cutter[i].dir == 0) continue;
		// It means that the cutter hasn't been built or has just been removed

		Cutter * cutter = &world.cutter[i];
		int x = cutter->pos[0], y = cutter->pos[1];
		int xx = x + dir[cutter->dir - 1][0], yy = y + dir[cutter->dir - 1][1];
		//std::cout << "��ѯ����(" << xx << "," << yy << ")������" << std::endl;
		if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
		if (world.mapp[xx][yy].type == BELTID && world.belt[world.mapp[xx][yy].id].dir == cutter->dir) {
			if (world.belt[world.mapp[xx][yy].id].isEmpty != true) {
				// ��ȡ����
				cutter->input(world.belt[world.mapp[xx][yy].id]);
				//std::cout << "��⵽���룬����(" << xx << "," << yy << ")" << std::endl;
			}
		}
	}

	//��������Ͱ������
	for (int i = 0; i < world.maxRubbishBinId; i++) {
		if (world.rubbishBin[i].pos[0] == -1) continue;
		RubbishBin* bin = &world.rubbishBin[i];
		int x = bin->pos[0], y = bin->pos[1];

		for (int d = 1; d <= 4; d++) {
			// �����ĸ�����ָ������Ͱ�Ĵ��ʹ�

			int xx = x + dir[d - 1][0], yy = y + dir[d - 1][1];
			if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;

			if (world.mapp[xx][yy].type == BELTID && world.belt[world.mapp[xx][yy].id].dir == d) {
				if (world.belt[world.mapp[xx][yy].id].isEmpty != true) {
					// ��ȡ����
					bin->input(world.belt[world.mapp[xx][yy].id]);

				}
			}
		}
	}
	//����ϳ���������

	for (int i = 0; i < world.maxComposerId; i++) {
		//std::cout << "-----------------------------------" << "\n��ѯ�и������" << i << std::endl;
		if (world.composer[i].dir == 0) continue;
		// It means that the cutter hasn't been built or has just been removed

		Composer* composer = &world.composer[i];
		int x = composer->pos[0], y = composer->pos[1];
		int xx = x + dir[composer->dir - 1][0], yy = y + dir[composer->dir - 1][1];
		int inputBeltIdMain = -1, inputBeltIdSub = -1;
		//std::cout << "��ѯ����(" << xx << "," << yy << ")������" << std::endl;
		if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
		if (world.mapp[xx][yy].type == BELTID && world.belt[world.mapp[xx][yy].id].dir == composer->dir) {
			if (world.belt[world.mapp[xx][yy].id].isEmpty != true) {
				// ��ȡ����
				inputBeltIdMain = world.mapp[xx][yy].id;
				//std::cout << "��⵽���룬����(" << xx << "," << yy << ")" << std::endl;
			}
		}

		//�����������
		xx = composer->getSubx() + dir[composer->dir - 1][0]; yy = composer->getSuby() + dir[composer->dir - 1][1];
		if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
		if (world.mapp[xx][yy].type == BELTID && world.belt[world.mapp[xx][yy].id].dir == composer->dir) {
			if (world.belt[world.mapp[xx][yy].id].isEmpty != true) {
				// ��ȡ����
				inputBeltIdSub = world.mapp[xx][yy].id;
				//std::cout << "��⵽���룬����(" << xx << "," << yy << ")" << std::endl;
			}
		}

		if (inputBeltIdMain != -1 && inputBeltIdSub != -1) composer->input(world.belt[inputBeltIdMain], world.belt[inputBeltIdSub]);
	}
	return;
}

void buildingOutput(World& world) {
	int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
	// ����cutter
	for (int i = 0; i < world.maxCutterId; i++) {
		if (world.cutter[i].dir == 0) continue;
		//std::cout << "-----------------------------------" << "\n��ѯ�и������" << i << std::endl;
		Cutter* cutter = &world.cutter[i];

		if(!cutter->isEmptyMain){
			//���main�Ĳ���
			int x = cutter->pos[0], y = cutter->pos[1];
			int xx = x + dir[cutter->dir - 1][0], yy = y + dir[cutter->dir - 1][1];
			if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
			if (world.mapp[xx][yy].type == BELTID) {
				if (world.belt[world.mapp[xx][yy].id].isEmpty) {
					// 1.���������ʹ�
					// 2.���������ǿյ�		
					cutter->outputMain(world.belt[world.mapp[xx][yy].id]);
				}
			}
		}
		if (!cutter->isEmptySub) {
			//���sub�Ĳ���
			int x = cutter->getSubx(), y = cutter->getSuby();
			int xx = x + dir[cutter->dir - 1][0], yy = y + dir[cutter->dir - 1][1];
			if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
			if (world.mapp[xx][yy].type == BELTID) {
				if (world.belt[world.mapp[xx][yy].id].isEmpty) {
					// 1.���������ʹ�
					// 2.���������ǿյ�		
					cutter->outputSub(world.belt[world.mapp[xx][yy].id]);
				}
			}
		}
	}

	//����Miner
	for (int i = 0; i < world.maxMinerId; i++) {
		if (world.miner[i].dir == 0) continue;
		Miner* miner = &world.miner[i];

		if (!miner->isEmpty) {
			//���main�Ĳ���
			int x = miner->pos[0], y = miner->pos[1];
			int xx = x + dir[miner->dir - 1][0], yy = y + dir[miner->dir - 1][1];
			if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
			if (world.mapp[xx][yy].type == BELTID) {
				if (world.belt[world.mapp[xx][yy].id].isEmpty) {
					// 1.���������ʹ�
					// 2.���������ǿյ�		
					miner->output(world.belt[world.mapp[xx][yy].id]);
				}
			}
		}
	
	}
	//����Composer

	for (int i = 0; i < world.maxComposerId; i++) {
		if (world.composer[i].dir == 0) continue;
		//std::cout << "-----------------------------------" << "\n��ѯ�и������" << i << std::endl;
		Composer* composer = &world.composer[i];

		if (!composer->OutisEmpty) {
			int x = composer->pos[0], y = composer->pos[1];
			int xx = x + dir[composer->dir - 1][0], yy = y + dir[composer->dir - 1][1];
			if (xx < 0 || xx >= MAPLENGTH || yy < 0 || yy >= MAPLENGTH) continue;
			if (world.mapp[xx][yy].type == BELTID) {
				if (world.belt[world.mapp[xx][yy].id].isEmpty) {
					// 1.���������ʹ�
					// 2.���������ǿյ�		
					composer->output(world.belt[world.mapp[xx][yy].id]);
				}
			}
		}

	}
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