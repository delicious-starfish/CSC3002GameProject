#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <chrono>
#include "gameCollection.h"
#include "gameLogic.h"
#include "gameRender.h"

#define LOGIC_FPS 10
#define RENDER_FPS 10

int currentTime;
int currentRenderTime;
int cameraPositionX;
int cameraPositionY;
int mousePositionX;
int mousePositionY;
int totalScore;
int BeltAMOUNT;
int CutterAMOUNT;
int AveragerAMOUNT;
int PorterAMOUNT;
int ComposerAMOUNT;
int RotatorAMOUNT;
int MinerAMOUNT;

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

int main() {

    initgraph(720, 640);
    setbkcolor(0Xcfd9eb);
    BeginBatchDraw();

    loadImgRes();
    game->loadTestMap();
    Item testItem = Item(QUARTERSQUARE, WHITEITEM);
    game->world.putItemAt(testItem, 5, 12);

    cameraPositionX = 0;
    cameraPositionY = 0;
    //The origin camera point

    mousePositionX = 0;
    mousePositionY = 0;
    int controlPositionX = 0;
    int controlPositionY = 0;
    ExMessage mouseMessage;
    //initialize the mouse

    std::cout << game->world.toString();

    int nextLogic = getTime(), nextRender = getTime();
    int logicInterval = 1000 / LOGIC_FPS, renderInterval = 1000 / RENDER_FPS;
    int currentTime;

    while (true) {
        currentTime = getTime();
        // Monitor the mouse action
       //if (currentTime >= nextLogic) {
       //    logicTick(game.world);
       //    nextLogic += logicInterval;
       //}
        if (currentTime >= nextRender) {
            renderTick(game->world);
            nextLogic += renderInterval;
        }
        while (peekmessage(&mouseMessage, EM_MOUSE | EM_KEY))
        {
            //Mouse Operation
            switch (mouseMessage.message)
            {
            case WM_MOUSEMOVE:
                if (mouseMessage.lbutton) { cameraPositionX = mouseMessage.x - controlPositionX; cameraPositionY = mouseMessage.y - controlPositionY; }
                mousePositionX = mouseMessage.x; mousePositionY = mouseMessage.y;
                break;
            case WM_LBUTTONDOWN:
                controlPositionX = mouseMessage.x - cameraPositionX; controlPositionY = mouseMessage.y - cameraPositionY;
                break;
            case WM_LBUTTONUP:
                break;
            case WM_KEYDOWN:
                if (mouseMessage.vkcode == VK_ESCAPE)
                    return 0;
                break;
            }
        }
        FlushBatchDraw();
        Sleep(10);

    }
    delete game;
    //return 0;
}
