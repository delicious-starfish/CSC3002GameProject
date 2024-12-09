#include <graphics.h>
#include <conio.h>
#include <iostream>
#include<stdlib.h>
#include <chrono>
#include "gameCollection.h"
#include "gameLogic.h"
#include "gameRender.h"
#include "gameControl.h"
#include "gameConfig.h"
#include "gameUtil.h"

#pragma once
#ifndef _game_h_
#define _game_h_

extern int LOGIC_FPS;
extern int RENDER_FPS;
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

extern int nextLogic;
extern int nextRender;
extern int logicInterval;
extern int renderInterval;
extern IntImg* intimg1;
extern GameButton* gameButton;
extern Game* game;

//seperated from original main function ---yyl

void initGame(long long int time);
//initialize global variable

void playGame(ExMessage mouseMessage);
//render and logic

#endif