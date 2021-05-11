#ifndef BATTLE_H
#define BATTLE_H

#include <stdio.h>
#include <stdlib.h>
#include "pokemon.h"

typedef struct BattleStage BattleStage;

typedef struct BattleLog BattleLog;

typedef struct BattleList BattleList;

typedef struct Game Game;

/**
 * @brief allocates space for a Game type struct;
 * @param game: struct with the game data ;
 * @return the allocated struct pointer ;
 */
Game * newGame(Game* game);

/**
 * @brief allocates space for a BattleLog type struct;
 * @param battle_log: struct with the battle data ;
 * @return the allocated struct pointer;
 */
BattleLog * newBattleLog(BattleLog* battle_log);

/**
 * @brief returns how many battles the player has won since the last mew found;
 * @param game: struct with the game data ;
 * @return how many battles the player has won since the last mew found;
 */
int getGameLastMew(Game * game);

/**
 * @brief changes the number of battles a player has won since the last mew found;
 * @param game: struct with the game data ;
 * @param last_mew: value that will be set;
*/
void setGameLastMew(Game * game, int last_mew);

/**
 * @brief function that execute a battle between two pokemon;
 * @param player_pokemon: struct that contains all the data of the player pokemon ;
 * @param cpu_pokemon: struct that contains all the data of the cpu pokemon ;
 * @param new_game: struct with the game data ;
 * @param logs: file used to save the battle log ;
 */
int battle(Pokemon *player_pokemon, Pokemon *cpu_pokemon, Game * new_game, FILE * logs);

/**
 * @brief check the relation between the types of pokemon;
 * @param atk_type: the type of the attacking pokemon;
 * @param def_type: the type of the defending pokemon;
 * @return 0.5 if the attacker has disadvantage;
 * @return 1 if vantage is null;
 * @return 2 if the attacker has vantage;
 */
float typeRelation (int atk_type, int def_type);

/**
 * @brief free the BattleLog struct pointer;
 * @param log: struct with the battle data;
 */
void freeBattleLog(BattleLog * log);

/**
 * @brief free the Game struct pointer;
 * @param new_game: struct with the game data;
 */
void freeGame(Game * new_game);

#endif // BATTLE_H