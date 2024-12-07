#include "gameCollection.h"
#include "gameBuildings.h"
#include <graphics.h>
#include <conio.h>
#include <cmath>

#pragma once
#ifndef _gameRender_h_
#define _gameRender_h_

extern int currentTime;
extern int startTime;
extern int screenSizeX;
extern int screenSizeY;
extern double screenScale;
extern int pScale;
extern int cameraPositionX;
extern int cameraPositionY;
extern int mousePositionX;
extern int mousePositionY;
extern int mouseCase;
extern int hoverCase;
extern int scrollCase;
extern int tick21;
extern int tickRender;
extern int totalScore;
extern bool isPause;
extern bool isSpeedup;


class IntImg {
	//Integer Image
public:
	int pixel[1920][1080];
	//An int array representing pixels
	//Screen size cannot be larger than this

	int shade[1920][1080];

	int leftBound; int rightBound;
	int upBound; int dnBound;

	int mullist[257][11][5];
	//mullist [ix-x] [vScale] [0:1 1:64 2:128 3:192 4:256]
	//A multiplication list prepared for putImg1

	//float mouseTk

	IntImg();
	//Initialize

	void putImg(int x, int y, IMAGE* srcimg, int direction, double scale);
	/*
		Method: putImg
		Usage: putImg(PositionX, PositionY, Image pointer, Direction1234, Scale of zooming);

	-------------------------------------------
		Write the values to the array from an image
		By Yao Yilin
		*/

	void putImg1(int x, int y, IMAGE* srcimg);
	/*
		A faster way to put image.
		Only for 64*64  128*128  192*192  256*256 size building images in map
		By Yao Yilin
		*/

	void putImg(int x, int y, double r, IMAGE* srcimg, double scale);
	/*
		Method: putImg
		Usage: putImg(PositionX, PositionY, RotationRAD, Image pointer, Scale of zooming);

	-------------------------------------------
		Write the values to the array from an image, allow rotation
		By Yao Yilin
	*/
	//this may cost more time than previous one


	void putShadow(int x, int y, IMAGE* srcimg, double scale);
	/*
		Method: putShadow
		Usage: putShadow(PositionX, PositionY, Image pointer, Scale of zooming);

	-------------------------------------------
		Put the GI shadow, for better visual effect, doesn't affect game play
		By Yao Yilin
		*/

	void RenderImg();
	/*
		Method: RenderImg
		Usage: RenderImg();
				it is a sub function in method renderTick, only use in renderTick
	-------------------------------------------
		Output the final image
		By Yao Yilin
	*/
	//Should be called in method renderTick, or nothing will be putted on the screen!
	//Usually the last step of renderTick

	void ClearImg();
	/*
		Method: ClearImg
		Usage: ClearImg();
				it is a sub function in method renderTick, only use in renderTick
	-------------------------------------------
		Output an empty pixel[][] array
		By Yao Yilin
	*/
	//Usually the first step of renderTick

	void putGrounds();
	/*
	Method: putGrounds
	Usage: putGrounds();
			it is a sub function in method renderTick, only use in renderTick
--------------------------------
	Output the layer of background
	By Yao Yilin
	*/

	void putBuildings(World* world);
	/*
	Method: putBuildings
	Usage: putBuildings(world);
			it is a sub function in method renderTick, only use in renderTick
--------------------------------
	Output the layer of buildings
	By Yao Yilin
	// Change input from "World & world to World * world" by kby
	*/

	void putBuildings2(World* world);
	/*
	Method: putBuildings
	Usage: putBuildings(world);
			it is a sub function in method renderTick, only use in renderTick
--------------------------------
	Output the layer of buildings
	By Yao Yilin
	// Change input from "World & world to World * world" by kby
	*/

	void putItems(World* world);
	/*
		Method: putItems
		Usage: putItems(world);
				it is a sub function in method renderTick, only use in renderTick
	-------------------------------------------
		Output the layer of items, actually it only care about item on the belt
		By Kan Bo Yi && Yao Yilin

		At present only render the first layer
		Not Finished
		// Change input from "World & world to World * world" by kby
		*/

	void putAnItem(int shape, int color, int x, int y, int dir);

	void putUI();
	/*
		Method: putUI
		Usage: putUI();
				注意，本函数无法侦测鼠标位置，鼠标位置信息来自于main.cpp中监听到的鼠标位置，
				该位置存储于gameRender.h定义的全局变量mousePositionX与mousePositionY
	-------------------------------------------
		Output the layer of mouse, including the building it select and is going to build
		And UI
		By Yao Yilin
		*/

	void blur();
	/*
		Method: blur

	-------------------------------------------
		Blur the buillding box UI, for better visual effect, doesn't affect game play.
		It will cost some time.
		By Yao Yilin
		*/

	void putIllum(World* world);

	void renderTick(World* world);
	// This function will not change the value of world
	// It use the value in world to render the screen
	// input World world
	// output nothing
	//By Yao Yilin
	// Change input from "World & world to World * world" by kby
};

void loadImgRes();
/*
	Load the graphic resources of the game.
	Must be loaded first
		By Yao Yilin
*/
void putNumbers();

#endif
