#include "player.h"
#include "pokemon.h"

struct Player {
    char *name;
    int active_pokemons;
    int pokeballs;
    struct Pokemon *pokemon;
};