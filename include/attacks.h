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

void freeAttack(Attack *attack);

Attack ** readAttacks(int *attacksquantity);

char* getAttackName(Attack *attack);

void freeAttacks(Attack **attacks, int attacksQuantity);

void loadDispatchAttack();

float attackPokemon(int attack, int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

float calcDamage(int power, int A, int D, int is_MT);

float calcRandomThings(float probability);

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

#endif // ATTACKS_H