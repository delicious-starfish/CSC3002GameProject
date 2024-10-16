#include "gameItem.h"
#include "constants.h"
#include <vcruntime_string.h>

using namespace std;

Item::Item() {
	memset(shapeId,0,sizeof(shapeId));
	memset(colorId, 0, sizeof(colorId));
}