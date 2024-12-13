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

bool Item::operator == (Item & item) {
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++) {
			if (shapeId[0][i][j] != item.shapeId[0][i][j]) return false;
			if (colorId[0][i][j] != item.colorId[0][i][j]) return false;
		}
	return true;
}

void Item::rotate() {
	int temp = shapeId[0][0][0];
	shapeId[0][0][0] = shapeId[0][1][0];
	shapeId[0][1][0] = shapeId[0][1][1];
	shapeId[0][1][1] = shapeId[0][0][1];
	shapeId[0][0][1] = temp;
	
	temp = colorId[0][0][0];
	colorId[0][0][0] = colorId[0][1][0];
	colorId[0][1][0] = colorId[0][1][1];
	colorId[0][1][1] = colorId[0][0][1];
	colorId[0][0][1] = temp;
}