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
#include "game.h"
#include "menu.h"

#define SCOREREQUEST_TEST 100

int LOGIC_FPS;
int RENDER_FPS;
int SCENE;
int mouseCase;
int hoverCase;
int screenSizeX;
int screenSizeY;

IntImg* intimg1 = new IntImg();
GameButton* gameButton = new GameButton();
MenuButton* menuButton = new MenuButton();

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

    initgraph(screenSizeX, screenSizeY);

    BeginBatchDraw();

    loadImgRes();
    intimg1->loadMask();
    //game->loadTestMap();
    game->loadShowMap();

    ExMessage mouseMessage{};
    //initialize the mouse

    SCENE = SCENEMENU;

    initGame(getTime());

    while (true) {
        currentTime = getTime();
        switch (SCENE) {
        case SCENEMENU:
            playMenu(mouseMessage);
            break;
        case SCENESETTING:
            break;
        case SCENEGAME:
            playGame(mouseMessage);
            break;
        }
        if (totalScore >= SCOREREQUEST_TEST || totalScore == -1) {
            totalScore = 0;
            game->showInstruction();
            Game* oldGame = game;
            delete oldGame;
            game = new Game();
            SCENE = SCENEMENU;
        }
    }

    delete game;
    return 0;
}
