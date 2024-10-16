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

int main() {
    //initgraph(720, 640);
    //setbkcolor(0Xcfd9eb);
    //BeginBatchDraw();
    Game game;


    game.loadTestMap();

    std::cout << game.world.toString();

    //int nextLogic = getTime(), nextRender = getTime();
    //int logicInterval = 1000 / LOGIC_FPS, renderInterval = 1000 / RENDER_FPS;
    //int currentTime;

    //while (true) {
    //    currentTime = getTime();
    //     // Monitor the mouse action
    //    if (currentTime >= nextLogic) {
    //        logicTick(game.world);
    //        nextLogic += logicInterval;
    //    }
    //    if (currentTime >= nextRender) {
    //        renderTick(game.world);
    //        nextLogic += renderInterval;
    //    }

    //}

    //return 0;
}
