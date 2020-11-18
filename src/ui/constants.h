#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
#include <types.h>

const float TILE_SIZE = 256.0f;
const float HALF_TILE = TILE_SIZE / 2.0f;
const int MAP_WIDTH = 800;
const int MAP_HEIGHT = 800;
const Coordinate MAP_SIZE = Coordinate(MAP_WIDTH, MAP_HEIGHT);
const Coordinate HALF_MAP_SIZE = Coordinate(MAP_WIDTH / 2, MAP_HEIGHT / 2);

#endif //_CONSTANTS_H_
