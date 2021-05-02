#ifndef BATTLE_H
#define BATTLE_H

#include <stdio.h>
#include <stdlib.h>
#include "pokemon.h"

typedef struct BattleStage BattleStage;

typedef struct BattleLog BattleLog;

typedef struct BattleList BattleList;

typedef struct Game Game;

Game * newGame(Game* game);

BattleLog * newBattleLog(BattleLog* battle_log);

int getGameLastMew(Game * game);

void setGameLastMew(Game * game, int last_mew);

int battle(Pokemon *player_pokemon, Pokemon *cpu_pokemon, Game * new_game);

float typeRelation (int atk_type, int def_type);

void freeBattleLog(BattleLog * log);

void freeGame(Game * new_game);

#endif // BATTLE_H