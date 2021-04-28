#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Player Player;

Player * allocPlayer();

void freePlayer(Player *player);

#endif // PLAYER_H