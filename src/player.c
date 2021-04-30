#include "player.h"
#include "pokemon.h"

struct Player {
    char *name;
    int score;
};

Player * allocPlayer() 
{
    Player *player;

    player = (Player* ) calloc(1, sizeof(Player));

    return player;
}

void freePlayer(Player *player)
{
    if(player != NULL)
    {
        free(player);
    }
}
