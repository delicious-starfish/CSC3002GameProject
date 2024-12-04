#include "gameBuildings.h"
#include "gameItem.h"
#include "constants.h"
#include <vcruntime_string.h>
using namespace std;

Belt::Belt(int direction, int x, int y) {
	dir = direction;
	pos[0] = x;
	pos[1] = y;
	for (int i = 0; i < 4; i++) idBef[i] = 0;
	idBef[0] = 1;
	isStuck = false;
	itemNow = Item();
	isEmpty = true;
	nxtStuck = false;
	itemPre = Item();
	isMoved = false;
}

Belt::Belt() {
	dir = 0;
	pos[0] = -1;
	pos[0] = -1;
	itemNow = Item();
	isEmpty = true;
	isStuck = false;
	nxtStuck = false;
	for (int i = 0; i < 4; i++) idBef[i] = 0;
	idBef[0] = 1;
	itemPre = Item();
	isMoved = false;
}

bool Belt::exist() {
	return (dir != 0);
}

void Belt::grantItem(Item item) {
	itemNow = item;
}

Cutter::Cutter(int direction, int x, int y) {
	dir = direction;
	pos[0] = x;
	pos[1] = y;
	OutputMain = Item();
	OutputSub = Item();
	isEmptyMain = true;
	isEmptySub = true;
	OutputMainPre = Item();
	OutputSubPre = Item();
	isMovedMain = false;
	isMovedSub = false;
	isOperated = false;
}

Cutter::Cutter() {
	dir = 0;
	pos[0] = -1;
	pos[0] = -1;
	OutputMain = Item();
	OutputSub = Item();
	isEmptyMain = true;
	isEmptySub = true;
	OutputMainPre = Item();
	OutputSubPre = Item();
	isMovedMain = false;
	isMovedSub = false;
	isOperated = false;
}

bool Cutter::outputMain(Belt& output) {
	isMovedMain = true;
	if (isEmptyMain || !output.isEmpty) return false;

	isEmptyMain = true;

	
	output.grantItem(OutputMain);
	OutputMain = Item();
	output.isEmpty = false;

	return true;
}

bool Cutter::outputSub(Belt& output) {
	isMovedSub = true;
	if (isEmptySub || !output.isEmpty) return false;

	isEmptySub = true;


	output.grantItem(OutputSub);
	OutputSub = Item();
	output.isEmpty = false;

	return true;
}

int Cutter::getSubx() {
	switch(dir) {
	case UP:
		return pos[0];
	case DOWN:
		return pos[0];
	case LEFT:
		return pos[0] - 1;
	case RIGHT:
		return pos[0] + 1;
	}
}

int Cutter::getSuby() {
	switch (dir) {
	case UP:
		return pos[1] + 1;
	case DOWN:
		return pos[1] - 1;
	case LEFT:
		return pos[1];
	case RIGHT:
		return pos[1];
	}
}

bool Cutter::input(Belt & input) {
	if (!(isEmptyMain && isEmptySub)) return false;
	if (input.isEmpty) return false;
	Item item = input.itemNow;
	input.isEmpty = true;
	isOperated = true;



	Item leftHalf = Item(), rightHalf = Item();
	for (int i = 0; i < 2; i++) {
		leftHalf.shapeId[i][0][0] = item.shapeId[i][0][0]; leftHalf.colorId[i][0][0] = item.colorId[i][0][0];
		leftHalf.shapeId[i][1][0] = item.shapeId[i][1][0]; leftHalf.colorId[i][1][0] = item.colorId[i][1][0];

		rightHalf.shapeId[i][0][1] = item.shapeId[i][0][1]; rightHalf.colorId[i][0][1] = item.colorId[i][0][1];
		rightHalf.shapeId[i][1][1] = item.shapeId[i][1][1]; rightHalf.colorId[i][1][1] = item.colorId[i][1][1];
	}
	OutputMain = leftHalf;
	OutputSub = rightHalf;
	isEmptyMain = false;
	isEmptySub = false;
	input.itemNow = Item();
	return true;
}

Composer::Composer(int direction, int x, int y) {
	dir = direction;
	pos[0] = x;
	pos[1] = y;
	Output = Item();
	OutisEmpty = true;
	OutputPre = Item();
	isMoved = false;
	isOperated = false;
}

Composer::Composer() {
	dir = 0;
	pos[0] = -1;
	pos[1] = -1;
	Output = Item();
	OutisEmpty = true;
	OutputPre = Item();
	isMoved = false;
	isOperated = false;
}

bool Composer::output(Belt& output) {
	isMoved = true;
	if (OutisEmpty || !output.isEmpty) return false;

	OutisEmpty = true;

	output.grantItem(Output);
	Output = Item();
	output.isEmpty = false;

	return true;
}

int Composer::getSubx() {
	switch (dir) {
	case UP:
		return pos[0];
	case DOWN:
		return pos[0];
	case LEFT:
		return pos[0] - 1;
	case RIGHT:
		return pos[0] + 1;
	}
}

int Composer::getSuby() {
	switch (dir) {
	case UP:
		return pos[1] + 1;
	case DOWN:
		return pos[1] - 1;
	case LEFT:
		return pos[1];
	case RIGHT:
		return pos[1];
	}
}

bool Composer::input(Belt& leftinput, Belt& rightinput) {
	if (leftinput.isEmpty || rightinput.isEmpty) return false;
	if (!(OutisEmpty)) return false;
	Item leftitem = leftinput.itemNow;
	Item rightitem = rightinput.itemNow;
	leftinput.isEmpty = true;
	rightinput.isEmpty = true;
	leftinput.itemNow = Item();
	rightinput.itemNow = Item();
	isOperated = true;

	Item itemout = Item();
	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 2; y++)
			if (leftitem.shapeId[0][x][y] != 0 && rightitem.shapeId[0][x][y] != 0) return false;

	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 2; y++) {
			itemout.shapeId[0][x][y] = leftitem.shapeId[0][x][y] == 0 ? rightitem.shapeId[0][x][y] : leftitem.shapeId[0][x][y];
			itemout.colorId[0][x][y] = leftitem.colorId[0][x][y] == 0 ? rightitem.colorId[0][x][y] : leftitem.colorId[0][x][y];
		}
	Output = itemout;
	OutisEmpty = false;
	return true;
}

Miner::Miner() {
	pos[0] = -1;
	pos[1] = -1;
	produceStatus = 1;
	isEmpty = true;
	dir = 0;
	isMoved = false;
}

Miner::Miner(int x, int y, int dir) {
	pos[0] = x;
	pos[1] = y;
	produceStatus = 1;
	isEmpty = true;
	this->dir = dir;
	isMoved = false;
}

void Miner::setProduct(Item product) {
	item = product;
}

bool Miner::output(Belt& output) {
	if (isEmpty) return false;
	if (!output.isEmpty || produceStatus < MINERTICKCOST) {
		produceStatus = min(produceStatus + 1, MINERTICKCOST);
		return false;
	}
	Item newItem = Item();
	for(int i = 0;i < 2;i ++)
		for(int j = 0;j < 2;j ++)
			for (int k = 0; k < 2; k++) {
				newItem.shapeId[i][j][k] = item.shapeId[i][j][k];
				newItem.colorId[i][j][k] = item.colorId[i][j][k];
			}
	this->isMoved = true;
	produceStatus = 1;
	output.grantItem(newItem);
	output.isEmpty = false;

	return true;
}

RubbishBin::RubbishBin() {
	pos[0] = -1;
	pos[1] = -1;
}
RubbishBin::RubbishBin(int x, int y) {
	pos[0] = x;
	pos[1] = y;
}

bool RubbishBin::input(Belt& input) {
	if (input.isEmpty) return false;

	input.isEmpty = true;
	input.itemNow = Item();

	return true;
}

Rotator::Rotator(int x, int y, int direction) {
	dir = direction;
	pos[0] = x;
	pos[1] = y;
	Output = Item();
	OutisEmpty = true;
	OutputPre = Item();
	isMoved = false;
	isOperated = false;
}

Rotator::Rotator() {
	dir = 0;
	pos[0] = -1;
	pos[1] = -1;
	Output = Item();
	OutisEmpty = true;
	OutputPre = Item();
	isMoved = false;
	isOperated = false;
}

bool Rotator::output(Belt& output) {

	isMoved = true;
	if (OutisEmpty || !output.isEmpty) return false;

	OutisEmpty = true;

	output.grantItem(Output);
	Output = Item();
	output.isEmpty = false;

	return true;
}

int Rotator::getSubx() {
	switch (dir) {
	case UP:
		return pos[0];
	case DOWN:
		return pos[0];
	case LEFT:
		return pos[0] - 1;
	case RIGHT:
		return pos[0] + 1;
	}
}

int Rotator::getSuby() {
	switch (dir) {
	case UP:
		return pos[1] + 1;
	case DOWN:
		return pos[1] - 1;
	case LEFT:
		return pos[1];
	case RIGHT:
		return pos[1];
	}
}

bool Rotator::input(Belt& input) {
	if (input.isEmpty) return false;
	if (!(OutisEmpty)) return false;
	Item item = input.itemNow;
	input.isEmpty = true;
	
	isOperated = true;
	Item itemout = Item();
	itemout.shapeId[0][0][0] = item.shapeId[0][0][1]; itemout.shapeId[0][0][0] = item.shapeId[0][0][1];
	itemout.shapeId[0][1][0] = item.shapeId[0][0][0]; itemout.shapeId[0][1][0] = item.shapeId[0][0][0];
	itemout.shapeId[0][1][1] = item.shapeId[0][1][0]; itemout.shapeId[0][1][1] = item.shapeId[0][1][0];
	itemout.shapeId[0][0][1] = item.shapeId[0][1][1]; itemout.shapeId[0][0][1] = item.shapeId[0][1][1];

	itemout.colorId[0][0][0] = item.colorId[0][0][1]; itemout.colorId[0][0][0] = item.colorId[0][0][1];
	itemout.colorId[0][1][0] = item.colorId[0][0][0]; itemout.colorId[0][1][0] = item.colorId[0][0][0];
	itemout.colorId[0][1][1] = item.colorId[0][1][0]; itemout.colorId[0][1][1] = item.colorId[0][1][0];
	itemout.colorId[0][0][1] = item.colorId[0][1][1]; itemout.colorId[0][0][1] = item.colorId[0][1][1];
	Output = itemout;
	OutisEmpty = false;
	input.itemNow = Item();
	return true;
}
