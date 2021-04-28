#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"
#include "../include/player.h"
#include "../include/pokemon.h"
#include "../include/attacks.h"

void mainMenu();

void playGame();

void freeGameData(Attack **attacks, int attacksQuantity);

int userPokemonChoose(Pokemon ** pokemons, int pokemonsQuantity, int * user_pokemons);

#endif // MENU_H