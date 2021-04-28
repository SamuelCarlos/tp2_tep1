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

void freeGameData(Pokemon **pokemons, Attack **attacks,int pokemonsquantity,int attacksquantity);

#endif // MENU_H