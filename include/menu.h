#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"
#include "../include/battle.h"
#include "../include/player.h"
#include "../include/pokemon.h"
#include "../include/attacks.h"

void mainMenu(char * scoresLocation, char * logsLocation);

void playGame();

int userPokemonChoose(Pokemon ** pokemons, int pokemonsQuantity, int * user_pokemons);

int randomPokemonNumber(Game* new_game, int pokemon_quantity);

#endif // MENU_H