#include "gameCollection.h"
#include "gameBuildings.h"
#include <graphics.h>
#include <conio.h>
#include <cmath>

#pragma once
#ifndef _gameRender_h_
#define _gameRender_h_

extern int currentTime;
extern int currentRenderTime;
extern int screenSizeX;
extern int screenSizeY;
extern double screenScale;
extern int cameraPositionX;
extern int cameraPositionY;
extern int mousePositionX;
extern int mousePositionY;
extern int totalScore;


class IntImg {
	//Integer Image
    public:
	int pixel[1920][1080];
	//An int array representing pixels
	//Screen size cannot be larger than this

	int shade[1920][1080];

	int leftBound; int rightBound;
	int upBound; int dnBound;

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

	void putBuildings(World &world);
        /*
	    Method: putBuildings
	    Usage: putBuildings(world);
	    		it is a sub function in method renderTick, only use in renderTick
	--------------------------------
	    Output the layer of buildings
	    By Yao Yilin
        */

	void putItems(World& world);
	/*
	    Method: putItems
	    Usage: putItems(world);
	    		it is a sub function in method renderTick, only use in renderTick
	-------------------------------------------
	    Output the layer of items, actually it only care about item on the belt
	    By Kan Bo Yi && Yao Yilin

		At present only render the first layer
		Not Finished
        */

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

    void renderTick(World &world);
    // This function will not change the value of world
    // It use the value in world to render the screen
    // input World world
    // output nothing
	//By Yao Yilin
};

void loadImgRes();
/*
	Load the graphic resources of the game.
	Must be loaded first
        By Yao Yilin
*/

#endif
