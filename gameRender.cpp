#include "gameCollection.h"
#include "gameRender.h"
#include <graphics.h>
#include <conio.h>

IMAGE grnd;
IMAGE belt;
IMAGE belC;
IMAGE rota;

void loadImgRes(){
	loadimage(&grnd, _T("tex\\grd1.png"));
	loadimage(&belt, _T("tex\\belt.png"));
	loadimage(&belC, _T("tex\\belC.png"));
	loadimage(&rota, _T("tex\\rota.png"));
}


void renderTick(World& world){
	cleardevice();
	for (int i = 0; i < MAPLENGTH;i++) {
		for (int j = 0; j < MAPLENGTH; j++) {
			switch (world.mapp[i][j].type)
			{
			case(GROUNDID):
				putimage(i * 32, j * 32, &grnd); break;
			case(BELTID):
				putimage(i * 32, j * 32, &belt); break;
			case(ROTATORID):
				putimage(i * 32, j * 32, &rota); break;
				
			}
		}
	}
	putimage(5 * 32, 6 * 32, &belt);
	putimage(6 * 32, 6 * 32, &belC);
	putimage(4 * 32, 6 * 32, &rota);
}