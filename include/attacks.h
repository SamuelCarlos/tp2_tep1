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

/*
@brief free the attack struct pointer;
@param Attack *attack: Attack struct pointer ;
*/
void freeAttack(Attack *attack);

/*
@brief reads from the file "attacks.csv" all attacks and save to a pointer to pointer of type Attack;
@param int *attackquantity: pointer to save the amount of attacks read ;
@return pointer to pointer of type Attack with all attacks read from file;
*/
Attack ** readAttacks(int *attacksquantity);

/*
@brief receives a struct attack and returns its name;
@param Attack *attack: Attack struct pointer ;
@return char* with the attack name;
*/
char* getAttackName(Attack *attack);

/*
@brief free the attacks struct pointer to pointer;
@param Attack **attacks: attack struct pointer to pointer ;
@param int attacksQuantity: total number of attacks (used in the for) ;
*/
void freeAttacks(Attack **attacks, int attacksQuantity);

/*
@brief calculates the damage caused by an attack;
@param int power: the attack power;
@param int A: the attack value of the attacking pokemon;
@param int D: the defense value of the defending pokemon;
@param int is_MT: checks if the attack is of the same type as the pokemon;
@return float: the damage done;
*/
float calcDamage(int power, int A, int D, int is_MT);
/*
@brief receives a probability and checks if happened or not;
@param float probability;
@return 1 if happened;
@return 0 if didn't happened;
*/
float calcRandomThings(float probability);

/*
@brief Initializes a dispatch table with all attack functions;
*/
void loadDispatchAttack();

/*
@brief receives the attack number and performs the function of the dispatch table that corresponds to that attack
@param int attack: the attack number of dispatch table;
@param Pokemon *attacker: struct that contains all the data of the pokemon that is attacking ;
@param Pokemon *deffender: struct that contains all the data of the pokemon that is defending ;
@param DebuffsList* attacker_debuffs: debuff list of the attacking pokemon ;
@param DebuffsList* deffender_debuffs: debuff list of the defending pokemon ;
@param float type_relation: the type relation between the two pokemon;
*/
void attackPokemon(int attack, Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

/*
OBS: All the functions below have the same parameter;
@param Pokemon *attacker: struct that contains all the data of the pokemon that is attacking ;
@param Pokemon *deffender: struct that contains all the data of the pokemon that is defending ;
@param DebuffsList* attacker_debuffs: debuff list of the attacking pokemon ;
@param DebuffsList* deffender_debuffs: debuff list of the defending pokemon ;
@param float type_relation: the type relation between the two pokemon;
*/

//@brief execute the attack "Choque do Trovao" and applies (if any) the debuff caused by that attack
void attack1(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

//@brief execute the attack "Onda de Choque" and applies (if any) the debuff caused by that attack
void attack2(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

//@brief execute the attack "Bater" and applies (if any) the debuff caused by that attack
void attack3(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

//@brief execute the attack "Lanca Chamas" and applies (if any) the debuff caused by that attack
void attack4(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

//@brief execute the attack "Dormir" and applies (if any) the debuff caused by that attack
void attack5(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

//@brief execute the attack "Arma de Agua" and applies (if any) the debuff caused by that attack
void attack6(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

//@brief execute the attack "Proteger" and applies (if any) the debuff caused by that attack
void attack7(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

//@brief execute the attack "Po de Sono" and applies (if any) the debuff caused by that attack
void attack8(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

//@brief execute the attack "Bomba de Semente" and applies (if any) the debuff caused by that attack
void attack9(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

//@brief execute the attack "Dois Gumes" and applies (if any) the debuff caused by that attack
void attack10(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

//@brief execute the attack "Rabo de Ferro" and applies (if any) the debuff caused by that attack
void attack11(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

//@brief execute the attack "Cavar" and applies (if any) the debuff caused by that attack
void attack12(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

//@brief execute the attack "Metronomo" and applies (if any) the debuff caused by that attack
void attack13(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

//@brief execute the attack "Auto-Destruir" and applies (if any) the debuff caused by that attack
void attack14(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation);

/* ------------------------------------------------------------------------------------------------------------------------------------- */

/*
@brief create a debuff list or add a new cell to an existing list;
@param DebuffsList *debuff_list: a debuff list null or with the debuffs of pokemon ;
@return the updated list ;
*/
DebuffsList * createDebuff(DebuffsList * debuff_list);

/*
@brief free a debuff list;
@param DebuffsList *debuff_list: a debuff list with the debuffs of pokemon ;
*/
void freeDebuffsList(DebuffsList * debuff_list);

/*
@brief scroll through the list checking if the pokemon has the debuff passed as a parameter;
@param DebuffsList *debuff_list: a debuff or with the debuffs of pokemon ;
@param int type: number that corresponds to the debuff type;
@return 1 if find the debuff on the list ;
@return 0 if not find;
*/
int findDebuffOnList(int type, DebuffsList * debuff_list);

/*
@brief receives a debuff list and returns his first position;
@param DebuffsList *debuff_list: a debuff list with the debuffs of pokemon ;
@return first position  ;
*/
DebuffsList * getFirstDebuff(DebuffsList * debuff_list);

/*
@brief receives a debuff list and returns his last position;
@param DebuffsList *debuff_list: a debuff list with the debuffs of pokemon;
@return last position  ;
*/
DebuffsList * getLastDebuff(DebuffsList * debuff_list);

/*
@brief print the debuff list;
@param DebuffsList *debuff_list: a debuff list with the debuffs of pokemon;
*/
void printDebuffsList(DebuffsList * debuff_list);

/*
@brief receives a debuff list and modifys his first position;
@param DebuffsList *debuff_list: a debuff list with the debuffs of pokemon;
*/
void modifyStartPositionDebuffsList(DebuffsList * list);

/*
@brief Initializes a dispatch table with all debuff functions;
*/
void loadDispatchDebuff();

/*
@brief receives a debuff list and passes the pokemon debuff rounds;
@param DebuffsList *debuff_list: a debuff list with the debuffs of pokemon;
*/
void passTurn(DebuffsList * debuffs_list);

/*
@brief function used to select the debuff function;
@param int *conditions: array containing pokemon debuff conditions (between 0 and 7);
@param Pokemon *attacker: struct that contains all the data of the pokemon;
@param DebuffsList *debuff_list: a debuff list with the debuffs of pokemon;
*/
void debuffPokemon(int * conditions, Pokemon * pokemon, DebuffsList * debuffs_list);

/*
OBS: All the functions below have the same brief and parameter;
@brief functions used to apply debuffs in Pokémon;
@param int *conditions: array containing pokemon debuff conditions (between 0 and 7);
@param Pokemon *attacker: struct that contains all the data of the pokemon;
@param int is_removing: checks if the debuff needs to be removed;
*/

// execute the debuff "Paralizar"
void debuff1(int * conditions, Pokemon * pokemon, int is_removing);
// execute the debuff "Queimar"
void debuff2(int * conditions, Pokemon * pokemon, int is_removing);
// execute the debuff "Dormir e curar" (attacker pokemon)
void debuff3(int * conditions, Pokemon * pokemon, int is_removing);
// execute the debuff "Proteger"
void debuff4(int * conditions, Pokemon * pokemon, int is_removing);
// execute the debuff "Dormir" (deffender pokemon)
void debuff5(int * conditions, Pokemon * pokemon, int is_removing);
// execute the debuff "Cavar"
void debuff6(int * conditions, Pokemon * pokemon, int is_removing);
// execute the debuff ??
void debuff7(int * conditions, Pokemon * pokemon, int is_removing);
// execute the debuff ??
void debuff8(int * conditions, Pokemon * pokemon, int is_removing);
/* ------------------------------------------------------------- */
#endif // ATTACKS_H