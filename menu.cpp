#include "menu.h"
#include "game.h"
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include<stdlib.h>
#include <chrono>
#include "gameRender.h"
#include "gameControl.h"
#include "gameConfig.h"
#include "gameUtil.h"

void playMenu(ExMessage mouseMessage)
{
	menuButton->operateMenu(mouseMessage);
	intimg1->renderMenu();
	FlushBatchDraw();
}
