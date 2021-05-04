#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Map Map;

typedef struct MapList MapList;

void readMapChunk();

MapList * createNewMap(MapList * player_maps);

MapList * getLastMap(MapList * player_maps);

#endif