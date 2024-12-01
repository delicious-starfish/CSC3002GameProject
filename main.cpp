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

#define LOGIC_FPS 2
#define RENDER_FPS 32

int currentTime;
int currentRenderTime;
int screenSizeX;
int screenSizeY;
double screenScale;
double previousScreenScale;
int cameraPositionX;
int cameraPositionY;
int mousePositionX;
int mousePositionY;
int controlPositionX;
int controlPositionY;
int mouseCase;
int hoverCase;
int scrollCase;
int tickRender;
bool isBuildingOperated;
int totalScore;



IntImg* intimg1 = new IntImg();
GameButton* gameButton = new GameButton();

long long getTime() {
    long long millisecSince1970 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
        .count();
    return millisecSince1970;
}
/*
    Input : nothing
    Output: a long long variable that tells how many milliseconds have passed since 1970
*/
Game* game = new Game();

std::string getAppFileNameNoExt()
{
    char path[MAX_PATH]; // 
    HMODULE hModule = GetModuleHandle(NULL); // get the handle of current app 
    if (hModule != NULL) {
        // get the path and filename by the handle
        GetModuleFileNameA(hModule, path, sizeof(path));

        std::string StrAppName = std::string(path);
        size_t pos = StrAppName.rfind(".exe");
        if (pos != std::string::npos) {
            return StrAppName.substr(0, pos);
        }

        return StrAppName; // the filename and path of current app (without file_ext_name)
    }
    return ""; // 
}

int main() {
    /*
    initialize the logger and configuration for the game
    */
    Logger::getInstance(getAppFileNameNoExt() + ".log");
    GameConfig::getInstance(getAppFileNameNoExt() + ".ini");

    screenSizeX = GameConfig::getInstance().get("Game", "ScreenWidth", 960);
    screenSizeY = GameConfig::getInstance().get("Game", "ScreenHeight", 540);

    //set screen size (No larger than 1920*1080)
    screenScale = 1;
    //set screen scale (Better within 0.25~1.00)
    previousScreenScale = 1;
    
    initgraph(screenSizeX, screenSizeY);
    
    setbkcolor(0Xcfd9eb);
    BeginBatchDraw();

    loadImgRes();
    game->loadTestMap();
    Item testItem = Item(QUARTERSQUARE, WHITEITEM);
    testItem.colorId[0][1][1] = YELLOWITEM;
    testItem.colorId[0][0][0] = REDITEM;
    testItem.colorId[0][1][0] = BLUEITEM;
    testItem.shapeId[0][1][0] = QUARTERWINDMILL;
    testItem.shapeId[0][1][1] = QUARTERCIRCLE;
    game->world->putItemAt(testItem, 0, 12);
    game->world->putItemAt(testItem, 3, 12);
    cameraPositionX = 0;
    cameraPositionY = 0;
    //The origin camera point

    mousePositionX = 0;
    mousePositionY = 0;
    controlPositionX = 0;
    controlPositionY = 0;
    mouseCase = 0;
    hoverCase = 0;
    scrollCase = 1;
    ExMessage mouseMessage;
    //initialize the mouse

    int nextLogic = getTime(), nextRender = getTime();
    int logicInterval = 1000 / LOGIC_FPS, renderInterval = 1000 / RENDER_FPS;
    int currentTime;
    tickRender = 0;
    isBuildingOperated = true;


    while (true) {
       currentTime = getTime();

        // the game is not under pause state
           //Logic operation
           if (currentTime >= nextLogic) {
               if (!game->world->isPause()) {
                   tickRender = 0;
                   isBuildingOperated ^= 1;
                   logicTick(game->world);
               }
               nextLogic += logicInterval;

           }
       
        // Render
        if (currentTime >= nextRender) {
            if (!game->world->isPause()) {
                tickRender += 4;
            }
            
            intimg1->renderTick(game->world);
            nextRender += renderInterval;
        }
    //    // Mouse Monitor
        gameButton->operateTick(game->world, mouseMessage);
        FlushBatchDraw();
        //Sleep(0.05);

    }
    delete game;
    return 0;
}
