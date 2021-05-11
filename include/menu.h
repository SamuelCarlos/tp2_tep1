#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"
#include "../include/files.h"
#include "../include/battle.h"
#include "../include/pokemon.h"
#include "../include/attacks.h"

/**
 * @brief starts the game;
 * @param scoresLocation: pointer to string that meants the scores file location;
 * @param logsLocation: pointer to string that meants the logs file location;
 */
void mainMenu(char * scoresLocation, char * logsLocation);

/**
 * @brief plays the game;
 * @param scoresLocation: pointer to string that meants the scores file location;
 * @param logs: pointer to logs FILE;
 * @param match: int to represent the actual match;
 */
void playGame(char * scoresLocation, FILE * logs, int match);

/**
 * @brief CPU random pokemon number generator considering last time a Mew appears;
 * @param new_game: pointer to the game struct;
 * @param pokemon_quantity: how many pokemons the game have;
 * @return int to represent the number of the random pokemon;
 */
int randomPokemonNumber(Game* new_game, int pokemon_quantity);

#endif // MENU_H