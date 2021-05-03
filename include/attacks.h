#ifndef ATTACKS_H
#define ATTACKS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "battle.h"

typedef struct Attack Attack;

typedef struct Debuffs Debuffs;

typedef struct DebuffsList DebuffsList;

typedef void (*fptrAttack)(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

typedef void (*fptrDebuff)(int* conditions, Pokemon * pokemon, int is_removing);

void freeAttack(Attack *attack);

Attack ** readAttacks(int *attacksquantity);

char* getAttackName(Attack *attack);

void freeAttacks(Attack **attacks, int attacksQuantity);

void loadDispatchAttack();

void attackPokemon(int attack, Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

float calcDamage(int power, int A, int D, int is_MT);

float calcRandomThings(float probability);

int findDebuffOnList(int type, DebuffsList * debuff_list);

void attack1(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

void attack2(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

void attack3(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

void attack4(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

void attack5(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

void attack6(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

void attack7(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

void attack8(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

void attack9(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

void attack10(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

void attack11(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

void attack12(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

void attack13(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

void attack14(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

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