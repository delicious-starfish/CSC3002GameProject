#include <graphics.h>
#include <conio.h>
#include <iostream>
#include<stdlib.h>
#include <chrono>
#include "gameCollection.h"
#include "gameLogic.h"
#include "gameRender.h"

#define LOGIC_FPS 5
#define RENDER_FPS 10

int currentTime;
int currentRenderTime;
int screenSizeX;
int screenSizeY;
double screenScale;
int cameraPositionX;
int cameraPositionY;
int mousePositionX;
int mousePositionY;
int totalScore;




IntImg* intimg1 = new IntImg();

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

    screenSizeX = 960;
    screenSizeY = 540;
    //set screen size (No larger than 1920*1080)
    screenScale = 1;
    //set screen scale (Better within 0.25~1.00)
    double previousScreenScale = 1;
    
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
    testItem.shapeId[0][0][1] = QUARTERCIRCLE;
    testItem.shapeId[0][1][1] = QUARTERCIRCLE;
    game->world.putItemAt(testItem, 0, 12);
    game->world.putItemAt(testItem, 3, 12);
    cameraPositionX = 0;
    cameraPositionY = 0;
    //The origin camera point

    mousePositionX = 0;
    mousePositionY = 0;
    int controlPositionX = 0;
    int controlPositionY = 0;
    ExMessage mouseMessage;
    //initialize the mouse

    int nextLogic = getTime(), nextRender = getTime();
    int logicInterval = 1000 / LOGIC_FPS, renderInterval = 1000 / RENDER_FPS;
    int currentTime;


    while (true) {
        currentTime = getTime();


        //Logic operation
        if (currentTime >= nextLogic) {
            logicTick(game -> world);
            nextLogic += logicInterval;
            
        }
        // Render
        if (currentTime >= nextRender) {
            intimg1->renderTick(game-> world);
            nextRender += renderInterval;
        }
        // Mouse Monitor
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
            case WM_MOUSEWHEEL:
                //Change screenscale by scrolling mouse
                if (mouseMessage.wheel > 0 && screenScale < 1) screenScale+=0.0625;
                else if (mouseMessage.wheel < 0 && screenScale>0.375) screenScale-=0.0625;
                mouseMessage.wheel = 0;
                //Reset camera position to Realize mouse-centered scaling
                cameraPositionX = mousePositionX - (mousePositionX - cameraPositionX) * screenScale / previousScreenScale;
                cameraPositionY = mousePositionY - (mousePositionY - cameraPositionY) * screenScale / previousScreenScale;
                previousScreenScale = screenScale;
                break;
            case WM_KEYDOWN:
                if (mouseMessage.vkcode == VK_ESCAPE)
                    return 0;
                break;
                break;
            }
        }
        FlushBatchDraw();
        //Sleep(0.05);

    }
    delete game;
    return 0;
}
