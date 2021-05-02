#ifndef POKEMON_H
#define POKEMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pokemon Pokemon;

typedef struct PokemonsList PokemonsList;

void printPokemon(Pokemon *pokemon);

void printPokemonList(PokemonsList *poke_list);

void freePokemon(Pokemon *pokemon);

void freePokemonList(PokemonsList *poke_list);

Pokemon * createPokemon();

Pokemon * copyPokemon(Pokemon *poke, Pokemon *poke2);

Pokemon * readPokemonFromList(PokemonsList *poke_list, int position);

PokemonsList * addPokemonOnList(PokemonsList *poke_list);

PokemonsList * attributePokemonToCell(PokemonsList* cell, Pokemon* pokemon);

PokemonsList * removePokemonFromList(PokemonsList *poke_list, int position);

PokemonsList * readPokemons(int *quantity);

float getPokemonHP(Pokemon *pokemon);

float getPokemonActualHP(Pokemon *pokemon);

void setPokemonActualHP(Pokemon *pokemon, float new_hp);

int getPokemonATK(Pokemon *pokemon);

int getPokemonDEF(Pokemon *pokemon);

int getPokemonTYPE(Pokemon *pokemon);

int getPokemonATTACKS1(Pokemon *pokemon);

int getPokemonATTACKS2(Pokemon *pokemon);

int getPokemonATTACKS3(Pokemon *pokemon);

#endif // POKEMON_H