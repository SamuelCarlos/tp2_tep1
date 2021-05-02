#ifndef ATTACKS_H
#define ATTACKS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "battle.h"

typedef struct Attack Attack;

typedef struct Debuffs Debuffs;

typedef struct DebuffsList DebuffsList;

typedef float (*fptrAttack)(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

typedef void (*fptrDebuff)(int* conditions, Pokemon * pokemon, int is_removing);

void freeAttack(Attack *attack);

Attack ** readAttacks(int *attacksquantity);

char* getAttackName(Attack *attack);

void freeAttacks(Attack **attacks, int attacksQuantity);

void loadDispatchAttack();

float attackPokemon(int attack, int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

float calcDamage(int power, int A, int D, int is_MT);

float calcRandomThings(float probability);

int findDebuffOnList(int type, DebuffsList * debuff_list);

float attack1(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

float attack2(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

float attack3(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

float attack4(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

float attack5(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

float attack6(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

float attack7(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

float attack8(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

float attack9(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

float attack10(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

float attack11(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

float attack12(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

float attack13(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

float attack14(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

DebuffsList * createDebuff(DebuffsList * debuff_list);

void freeDebuffsList(DebuffsList * debuff_list);

DebuffsList * getLastDebuff(DebuffsList * debuff_list);

DebuffsList * getFirstDebuff(DebuffsList * debuff_list);

void printDebuffsList(DebuffsList * debuff_list);

void modifyStartPositionDebuffsList(DebuffsList * list);

void loadDispatchDebuff();

void passTurn(DebuffsList * debuffs_list);

void debuffPokemon(int * conditions, Pokemon * pokemon, DebuffsList * debuffs_list);

void debuff1(int * conditions, Pokemon * pokemon, int is_removing);

void debuff2(int * conditions, Pokemon * pokemon, int is_removing);

void debuff3(int * conditions, Pokemon * pokemon, int is_removing);

void debuff4(int * conditions, Pokemon * pokemon, int is_removing);

void debuff5(int * conditions, Pokemon * pokemon, int is_removing);

void debuff6(int * conditions, Pokemon * pokemon, int is_removing);

void debuff7(int * conditions, Pokemon * pokemon, int is_removing);

void debuff8(int * conditions, Pokemon * pokemon, int is_removing);

#endif // ATTACKS_H