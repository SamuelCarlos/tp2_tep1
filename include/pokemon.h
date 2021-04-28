#ifndef POKEMON_H
#define POKEMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pokemon Pokemon;

void printPokemon(Pokemon *pokemon);

void freePokemon(Pokemon *pokemon);

Pokemon** readPokemons(int *quantity);

#endif // POKEMON_H