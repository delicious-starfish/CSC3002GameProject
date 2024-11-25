#pragma once
#include "gameCollection.h"

#ifndef _gameLogic_h_
#define _gameLogic_h_

extern bool isBuildingOperated;

void logicTick(World & world);
/*
*	Input: the World variable you need do logic calculation
*	Output: Nothing, but the World variable will be changed
*	-----
	This function change the value in the variable world. It will first calculate
	the factories' logic, then calculate the belts' logic
*/
void setPreItems(World& world);
/*
*  Record previous item before going to the next logic
*  Reset building's isMoved
*  The Animation will show the previous object's movement, which means it will be 1 logictick later than current logic
*/


void beltLogic(World & world);
/*
	Method beltLogic
	Usage: beltLogic(world); This function is only used in method logicTick
	--------------------------------
	let every belt to extract product from the machine and pass on the items to the other belt

	made by Kanboyi
*/

void buildingInput(World& world);
/*
	Method buildingInput
	Usage: buildingInput(world); This function is only used in method logicTick
	--------------------------------
	let every building to get the ingredient from the belts. In the meantime it will store its product in its variable

	Only finished the cutter

	by Kan bo yi

	
*/

void buildingOutput(World& world);
/*
	Method buildingOutput
	Usage: buildingOutput(world); This function is only used in method logicTick
	--------------------------------
	let every building output the product to the belts.

	Only finished the cutter

	by Kan bo yi


*/

void belt_FindEndAndUpdate(World& world, bool footprint[], int nowId);
/*
	Method belt_FindRowsAndUpdate
	Usage: belt_FindRowsAndUpdate(world,book,i); This function is only used in method logicTick
	--------------------------------
	�ݹ��Ѱ�ҡ���ĩβ�Ĵ��ʹ����������ڻ���ʱ��������
	���ܹ�������

	made by Kanboyi
*/
#endif
