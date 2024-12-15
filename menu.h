#include <graphics.h>
#include <conio.h>
#include <iostream>
#include<stdlib.h>
#include <chrono>
#include "gameRender.h"
#include "gameControl.h"

#pragma once
#ifndef _menu_h_
#define _menu_h_

extern int LOGIC_FPS;
extern int RENDER_FPS;
extern int SCENE;
extern int mouseCase;
extern int hoverCase;
extern int screenSizeX;
extern int screenSizeY;
extern int mousePositionX;
extern int mousePositionY;
extern IntImg* intimg1;
extern MenuButton* menuButton;
extern MenuIntroButton* menuIntroButton;

void playMenu(ExMessage mouseMessage);
//render the menu, click start to enter the game
void playIntroMenu(ExMessage mouseMessage);
void playFailedMenu(ExMessage mouseMessage);
void playSuccessfulMenu(ExMessage mouseMessage);

#endif