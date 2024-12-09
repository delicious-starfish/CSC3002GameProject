#include "gameCollection.h"
#include "gameBuildings.h"
#include "gameRender.h"
#include <graphics.h>
#include <conio.h>
#include <cmath>

#pragma once
#ifndef _gameControl_h_
#define _gameControl_h_

extern int currentTime;
extern int screenSizeX;
extern int screenSizeY;
extern double screenScale;
extern double previousScreenScale;
extern int pScale;
extern int cameraPositionX;
extern int cameraPositionY;
extern int mousePositionX;
extern int mousePositionY;
extern int controlPositionX;
extern int controlPositionY;
extern int mouseCase;
extern int hoverCase;
extern int scrollCase;
extern int totalScore;
extern bool isPause;
extern bool preSpeedup;
extern bool isSpeedup;

class Button {
public:
	int lfBound;
	int rtBound;
	int upBound;
	int dnBound;
	//Four bounds of the button
	Button(int lf, int rt, int up, int dn);
	bool isHover();
	//Check whether the mouse is hovering above the button
};

class GameButton {
	//A group of button in the game scene
public:
	//Button of buildings on the bottom screen:
	Button BTbelt = Button(43, 140, 443, 540);
	Button BTrota = Button(140, 237, 443, 540);
	Button BTcutt = Button(237, 334, 443, 540);
	Button BTcomp = Button(334, 431, 443, 540);
	Button BTcolr = Button(431, 528, 443, 540);
	Button BTdelete = Button(528, 625, 443, 540);
	Button BTacceptor = Button(625, 722, 443, 540); // To be adjusted ...

	// Buttons on the top right corner:
	Button BTpause = Button(843, 914, 20, 80);
	Button BTspeed = Button(772, 843, 20, 80);
    ///后面还会加按钮


    void operateTick(World * world,ExMessage& msg);
	//Left click and drag to move the screen
	//Scroll to change the screen scale
	//Right click on the bottom building's area to select buildings
	//When select a building, Scroll to rotate it, Right click to place it
	//目前仅支持传送带和切割器的操作
	//---By Yilin Yao
	//添加删除按钮,把传递引用改成传递地址
	//---By Kan bo yi
};
//以后可能会有主菜单UI界面，用新的class建立



#endif