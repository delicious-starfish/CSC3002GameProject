#pragma once
#include "gameCollection.h"

#ifndef _gameLogic_h_
#define _gameLogic_h_
void logicTick(World & world);
/*
*	Input: the World variable you need do logic calculation
*	Output: Nothing, but the World variable will be changed
*	-----
	This function change the value in the variable world. It will first calculate
	the factories' logic, then calculate the belts' logic
*/

void beltLogic(World & world);
/*
	Method beltLogic
	Usage: beltLogic(world); This function is only used in method logicTick
	--------------------------------
	let every belt to extract product from the machine and pass on the items to the other belt

	made by Kanboyi
*/

void buildingLogic(World& world);
/*
	Method buildingLogic
	Usage: buildingLogic(world); This function is only used in method logicTick
	--------------------------------
	let every building to get the ingredient from the belts. The belt then generate the product, which is stored inside the
	building, waiting for being extracted

	
*/

void belt_FindEndAndUpdate(World& world, bool footprint[], int nowId);
/*
	Method belt_FindRowsAndUpdate
	Usage: belt_FindRowsAndUpdate(world,book,i); This function is only used in method logicTick
	--------------------------------
	�ݹ��Ѱ�ҡ���ĩβ�Ĵ��ʹ����������ڻ���ʱ��������
	���ܹ�����

	made by Kanboyi
*/
#endif
