#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>

#include "../include/map.h"
#include "../include/pokemon.h"

typedef struct Player Player;

Player * allocPlayer();

void freePlayer(Player *player);

int getPlayerPosition_X(Player * player);

void setPlayerPosition_X(Player * player, int position);

int getPlayerPosition_Y(Player * player);

void setPlayerPosition_Y(Player * player, int position);


#endif // PLAYER_H