#include "gameBuildings.h"
#include "gameItem.h"
#include <vcruntime_string.h>
using namespace std;

Belt::Belt(int direction, int x, int y) {
	dir = direction;
	pos[0] = x;
	pos[1] = y;
	itemNow = Item();
	isEmpty = true;
}

Belt::Belt() {
	dir = 0;
	pos[0] = -1;
	pos[0] = -1;
	itemNow = Item();
	isEmpty = true;
}

void Belt::grantItem(Item item) {
	itemNow = item;
}

Cutter::Cutter(int direction, int x, int y) {
	dir = direction;
	pos[0] = x;
	pos[1] = y;
	item = Item();
}

Cutter::Cutter() {
	dir = 0;
	pos[0] = -1;
	pos[0] = -1;
	item = Item();
}

Composer::Composer(int direction, int x, int y) {
	dir = direction;
	pos[0] = x;
	pos[1] = y;
	inputItemLeft = Item();
	inputItemRight = Item();
}

Composer::Composer() {
	dir = 0;
	pos[0] = -1;
	pos[0] = -1;
	inputItemLeft = Item();
	inputItemRight = Item();
}