#include "game.h"
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

int nextLogic;
int nextRender;
int logicInterval;
int renderInterval;

int currentTime;
int startTime;
double screenScale;
double previousScreenScale;
int pScale;
int cameraPositionX;
int cameraPositionY;
int mousePositionX;
int mousePositionY;
int controlPositionX;
int controlPositionY;
int scrollCase;
int tickRender;
bool isBuildingOperated;
int totalScore;
bool isPause;
bool preSpeedup;
bool isSpeedup;

void initGame(long long int time) {
    startTime = time;
    nextLogic = time; nextRender = time;
    LOGIC_FPS = 2;
    RENDER_FPS = 32;
    logicInterval = 1000 / LOGIC_FPS; renderInterval = 1000 / RENDER_FPS;
    //set screen size (No larger than 1920*1080)
    screenScale = 1;
    //set screen scale (Better within 0.25~1.00)
    previousScreenScale = 1;
    pScale = 0;
    setbkcolor(0X608096);
    cameraPositionX = 0;
    cameraPositionY = -444;
    //The origin camera point

    mousePositionX = 0;
    mousePositionY = 0;
    controlPositionX = 0;
    controlPositionY = 0;
    mouseCase = 0;
    hoverCase = 0;
    scrollCase = 1;
    totalScore = 0;
    isPause = false;
    preSpeedup = false;
    isSpeedup = false;
    tickRender = 0;
    settextcolor(0Xdbeef5);
}

void playGame(ExMessage mouseMessage)
{
    // the game is not under pause state
       //Logic operation
    if (currentTime >= nextLogic) {
        if (!isPause) {
            tickRender = 0;
            if (preSpeedup) { isSpeedup = true; logicInterval = 500 / LOGIC_FPS; }
            else { isSpeedup = false; logicInterval = 1000 / LOGIC_FPS; }
            logicTick(game->world);
        }
        nextLogic += logicInterval;

    }

    // Render
    if (currentTime >= nextRender) {
        // Originally :     > -13                                        - 13
        if (cameraPositionX > -43) { cameraPositionX -= (cameraPositionX - 43) / 1.3; }
        if (cameraPositionX < (-MAPLENGTH * 64.0 * screenScale - 13 + screenSizeX)) { cameraPositionX -= (cameraPositionX - (-MAPLENGTH * 64.0 * screenScale - 13 + screenSizeX)) / 2.0; }
        if (cameraPositionY < (-MAPLENGTH * 64.0 * screenScale - 144 + screenSizeY)) { cameraPositionY -= (cameraPositionY - (-MAPLENGTH * 64.0 * screenScale - 144 + screenSizeY)) / 8.0; }
        if (cameraPositionY > 43) { cameraPositionY -= (cameraPositionY - 43) / 1.3; }
        // Originally :     > 13                                        - 13
        if (!isPause) {
            if (!isSpeedup)
                tickRender += 4;
            else
                tickRender += 8;
        }

        intimg1->renderTick(game->world);
        nextRender += renderInterval;

    }
    //    // Mouse Monitor
    gameButton->operateTick(game->world, mouseMessage);
    FlushBatchDraw();
}
