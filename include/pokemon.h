#ifndef POKEMON_H
#define POKEMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pokemon Pokemon;

typedef struct PokemonsList PokemonsList;

/**
 * @brief print the pokemon name;
 * @param pokemon: a struct pointer with the pokemon data;
 */
void printPokemon(Pokemon *pokemon);

/**
 * @brief print the pokemons names from a list;
 * @param poke_list: a list whit various pokemons;
 */
void printPokemonList(PokemonsList *poke_list);

/**
 * @brief free the Pokemon struct pointer;
 * @param pokemon: a struct pointer with the pokemon data;
 */
void freePokemon(Pokemon *pokemon);

/**
 * @brief free the pokemons list;
 * @param poke_list: a list whit various pokemons;
 */
void freePokemonList(PokemonsList *poke_list);

/**
 * @brief allocates space for a Pokemon type struct pointer;
 * @return the allocated struct pointer;
 */
Pokemon * createPokemon();

/**
 * @brief copy the data of a poke2 for poke;
 * @param poke: a struct pointer with the pokemon data(destiny);
 * @param poke2: a struct pointer with the pokemon data (origin);
 * @return the copied struct pointer;
 */
Pokemon * copyPokemon(Pokemon *poke, Pokemon *poke2);

/**
 * @brief scrolls through the list to the position passed and returns the pokemon from that position;
 * @param poke_list: a list whit various pokemons;
 * @param position: the position of the pokemon in the list;
 * @return the Pokemon of the position;
 */
Pokemon * readPokemonFromList(PokemonsList *poke_list, int position);

/**
 * @brief add a new Pokémon to the list;
 * @param poke_list: a list whit various pokemons;
 * @return the list with the new pokemon;
 */
PokemonsList * addPokemonOnList(PokemonsList *poke_list);

/**
 * @brief copy the data of a pokemon for cell of list;
 * @param cell: a cell of list(destiny);
 * @param pokemon: a struct pointer with the pokemon data (origin);
 * @return the list with the copied cell;
 */
PokemonsList * attributePokemonToCell(PokemonsList* cell, Pokemon* pokemon);

/**
 * @brief remove a Pokémon to the list;
 * @param poke_list: a list whit various pokemons;
 * @param position: the position of the pokemon in the list;
 * @return the list without the pokemon;
 */
PokemonsList * removePokemonFromList(PokemonsList *poke_list, int position);

/**
 * @brief reads from the file "pokemons.csv" all pokemons and save to a list of type PokemonsList;
 * @param quantity: pointer to save the amount of pokemons read ;
 * @return the list with all pokemons read from file;
 */
PokemonsList * readPokemons(int *quantity);

/**
 * @brief receives a struct Pokemon and returns the maximum hp of the pokemon;
 * @param pokemon: a struct pointer with the pokemon data;
 * @return float with the maximum hp;
 */
float getPokemonHP(Pokemon *pokemon);

/**
 * @brief receives a struct Pokemon and returns the actual hp of the pokemon;
 * @param pokemon: a struct pointer with the pokemon data;
 * @return float with the actual hp;
 */
float getPokemonActualHP(Pokemon *pokemon);

/**
 * @brief receives a struct Pokemon and returns the pokemon name;
 * @param pokemon: a struct pointer with the pokemon data;
 * @return char* with the name;
 */
char * getPokemonName(Pokemon *pokemon);

/**
 * @brief receives a struct Pokemon and modify the actual hp of the pokemon;
 * @param pokemon: a struct pointer with the pokemon data;
 * @param new_hp: the new pokemon hp;
 */
void setPokemonActualHP(Pokemon *pokemon, float new_hp);

/**
 * @brief receives a struct Pokemon and returns the ATK of the pokemon;
 * @param pokemon: a struct pointer with the pokemon data;
 * @return int with the ATK;
 */
int getPokemonATK(Pokemon *pokemon);

/**
 * @brief receives a struct Pokemon and returns the DEF of the pokemon;
 * @param pokemon: a struct pointer with the pokemon data;
 * @return int with the DEF;
 */
int getPokemonDEF(Pokemon *pokemon);

/**
 * @brief receives a struct Pokemon and returns the TYPE of the pokemon;
 * @param pokemon: a struct pointer with the pokemon data;
 * @return int with the TYPE;
 */
int getPokemonTYPE(Pokemon *pokemon);

/**
 * @brief receives a struct Pokemon and returns the first attack of the pokemon;
 * @param pokemon: a struct pointer with the pokemon data;
 * @return int with the number that represents the first attack;
*/
int getPokemonATTACKS1(Pokemon *pokemon);

/**
 * @brief receives a struct Pokemon and returns the second attack of the pokemon;
 * @param pokemon: a struct pointer with the pokemon data;
 * @return int with the number that represents the second attack;
 */
int getPokemonATTACKS2(Pokemon *pokemon);

/**
 * @brief receives a struct Pokemon and returns the third attack of the pokemon;
 * @param pokemon: a struct pointer with the pokemon data;
 * @return int with the number that represents the third attack;
 */
int getPokemonATTACKS3(Pokemon *pokemon);

/**
 * @brief receives a struct Pokemon and returns if the pokemon is vulnerable;
 * @param pokemon: a struct pointer with the pokemon data;
 * @return int with the number that represents your vulnerability;
 */
int getIsVulnerable(Pokemon *pokemon);

/**
 * @brief receives a struct Pokemon and modify the vulnerable value of the pokemon;
 * @param pokemon: a struct pointer with the pokemon data;
 * @param vulnerable: the new pokemon vulnerable value;
 */
void setIsVulnerable(Pokemon *pokemon, int vulnerable);

#endif // POKEMON_H