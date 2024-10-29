#include "gameCollection.h"
#include "gameBuildings.h"
#include <graphics.h>
#include <conio.h>

#pragma once
#ifndef _gameRender_h_
#define _gameRender_h_

extern int currentTime;
extern int currentRenderTime;
extern int cameraPositionX;
extern int cameraPositionY;
extern int mousePositionX;
extern int mousePositionY;
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
	By Yao Yi Ling
*/

void putAlphaImage(int x, int y, IMAGE* srcimg);
//It can put alpha images (images with opacity) on position(x,y)
//By Yao Yi Ling

void renderTick(World &world);
// This function will not change the value of world
// It use the value in world to render the screen
// input World world
// output nothing
// By Yao Yi Ling

void renderBuildings(World& world);
/*
	Method: renderBuildings
	Usage: renderBuildings(world);
			it is a sub function in method renderTick, only use in renderTick
	--------------------------------
	Output the graph of buildings
	By Yao Yi Ling
*/

void renderMouse();
/*
	Method: renderMouse
	Usage: renderMouse();
			注意，本函数无法侦测鼠标位置，鼠标位置信息来自于main.cpp中监听到的鼠标位置，
			该位置存储于gameRender.h定义的全局变量mousePositionX与mousePositionY
	-------------------------------------------
	Output the graph of mouse, including the building it select and is going to build
	By Yao Yi Ling
*/
#endif
