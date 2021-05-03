#include "player.h"
#include "../include/map.h"
#include "../include/pokemon.h"

struct Player {
    int position[2];
    MapList * visited_maps;
};

Player * allocPlayer() 
{
    Player *player;

    player = (Player* ) calloc(1, sizeof(Player));
    player->visited_maps = NULL;

    return player;
}

void freePlayer(Player *player)
{
    if(player != NULL)
    {
        free(player);
    }
}

int getPlayerPosition_X(Player * player)
{
    return player->position[0];
}

void setPlayerPosition_X(Player * player, int position)
{
    player->position[0] = position;
}

int getPlayerPosition_Y(Player * player)
{
    return player->position[1];
}

void setPlayerPosition_Y(Player * player, int position)
{
    player->position[1] = position;
}

// MapList * getPlayerVisitedMaps(Player * player)
// {
//     return player->visited_maps;
// }

