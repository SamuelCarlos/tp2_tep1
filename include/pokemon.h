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

void addPokemonOnList(PokemonsList *poke_list);

PokemonsList * removePokemonFromList(PokemonsList *poke_list, int position);

Pokemon * readPokemonFromList(PokemonsList *poke_list, int position);

PokemonsList * readPokemons(int *quantity);

#endif // POKEMON_H