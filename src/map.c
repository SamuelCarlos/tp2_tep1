#include "map.h"
#include "../include/player.h"

#define MAP_HEIGHT 41
#define MAP_WIDTH 41

struct Map {
    int map_coordinate[2];
    char ** pattern;
};

struct MapList {
    Map * map;
    MapList * next;
    MapList * last;
};

MapList * getLastMap(MapList * player_maps)
{
    MapList * temp = player_maps;

    do {
        temp = temp->next;
    }while(temp->next != NULL);
    
    return temp;
}

MapList * createNewMap(MapList * player_maps)
{
    MapList * temp;

    if(player_maps == NULL)
    {
        player_maps = (MapList*) calloc(1, sizeof(MapList));
        player_maps->map = (Map*) calloc(1, sizeof(Map));
        player_maps->next = NULL;
        temp = player_maps;
    }else{
        temp = getLastMap(player_maps);
        temp->next = (MapList*) calloc(1, sizeof(MapList));
        temp = temp->next;
        temp->map = (Map*) calloc(1, sizeof(Map));
        temp->next = NULL;
    }

    return temp;
}

// void newMap(Player * player)
// {
//     MapList * player_maps = getPlayerVisitedMaps(player);

//     if(player_maps == NULL)
//     {
//         setPlayerPosition_X(player, 0);
//         setPlayerPosition_Y(player, MAP_HEIGHT/2 + 1);
//     }
// }

