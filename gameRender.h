#include "gameCollection.h"
#include <graphics.h>
#include <conio.h>

#pragma once
#ifndef _gameRender_h_
#define _gameRender_h_

extern int currentTime;
extern int currentRenderTime;
extern int totalScore;
extern int BeltAMOUNT;
extern int CutterAMOUNT;
extern int AveragerAMOUNT;
extern int PorterAMOUNT;
extern int ComposerAMOUNT;
extern int RotatorAMOUNT;
extern int MinerAMOUNT;

void loadImgRes();
/*
	Load the graphic resources of the game.
	Must be loaded first!!!!
*/

void putAlphaImage(int x, int y, IMAGE* srcimg);
//It can put alpha images (images with opacity) on position(x,y)

void renderTick(World &world);
// This function will not change the value of world
// It use the value in world to render the screen
// input World world
// output nothing
#endif
