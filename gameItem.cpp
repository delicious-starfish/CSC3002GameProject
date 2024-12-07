#include "gameItem.h"
#include "constants.h"
#include <vcruntime_string.h>

using namespace std;

Item::Item() {
	memset(shapeId,0,sizeof(shapeId));
	memset(colorId, 0, sizeof(colorId));
}

Item::Item(int assignedShapeId, int assignedColorId) {
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			shapeId[0][x][y] = assignedShapeId;
			colorId[0][x][y] = assignedColorId;
		}
	}
}