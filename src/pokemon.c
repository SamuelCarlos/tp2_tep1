#include "pokemon.h"
#include "attacks.h"

struct Pokemon {
    char *name;
    int hp;
    int atk;
    int def;
    char* type;
    int attacks[3];
};

Pokemon** readPokemons()
{
    FILE *poke;
    Pokemon **pokemons;
    int pokemons_quantity = 1, ended = 0;
    int array_parser, i;
    char *pointer, *pointer2, *token;
    char **row;
    size_t bufsize;
    size_t characters;

    pokemons = (Pokemon** ) calloc(pokemons_quantity, sizeof(Pokemon*));
    pokemons[0] = (Pokemon *) calloc(1, sizeof(Pokemon));

    poke = fopen("./data/pokemons.csv","r");

    do
    {
        if(pokemons_quantity > 1) 
        {
            pokemons = (Pokemon **) realloc(pokemons, pokemons_quantity * sizeof(Pokemon *));
            pokemons[pokemons_quantity - 1] = (Pokemon *) calloc(1, sizeof(Pokemon));
        }

        bufsize = 32;
        array_parser = 0;

        pointer = (char *) calloc(bufsize, sizeof(char));

        characters = getline(&pointer, &bufsize, poke);
        if(characters == -1)
        {
            free(pointer);
            break;
        }
        pointer[characters] = '\0';

        pointer2 = pointer;

        row = (char **) calloc(8, sizeof(char*));

        token = strtok_r(pointer, ",", &pointer);
        row[array_parser] = token;
        array_parser++;

        for(i = array_parser; i < 8; i++) {
            if(token == NULL) 
            {
                free(row);
                ended = 1;
                break;
            }
            token = strtok_r(NULL, ",", &pointer);
            row[i] = token;
        }

        pokemons[pokemons_quantity - 1]->name = strdup(row[0]);
        pokemons[pokemons_quantity - 1]->hp = atoi(row[1]);
        pokemons[pokemons_quantity - 1]->atk = atoi(row[2]);
        pokemons[pokemons_quantity - 1]->def = atoi(row[3]);
        pokemons[pokemons_quantity - 1]->type = strdup(row[4]);
        pokemons[pokemons_quantity - 1]->attacks[0] = atoi(row[5]);
        pokemons[pokemons_quantity - 1]->attacks[1] = atoi(row[6]);
        pokemons[pokemons_quantity - 1]->attacks[3] = atoi(row[7]);

        free(row);
        free(pointer2);
        
        pokemons_quantity++;
    } while(!ended);

    fclose(poke);
    return pokemons;
}

void printPokemon(Pokemon *pokemon) 
{
    printf("name: %s\nhp: %d\natk: %d\ndef: %d\ntype: %s\nattack 1: %d\nattack 2: %d\nattack 3: %d\n", pokemon->name,pokemon->hp, pokemon->atk, pokemon->def, pokemon->type, pokemon->attacks[0], pokemon->attacks[1], pokemon->attacks[2]);
}

void freePokemon(Pokemon *pokemon) 
{
    if(pokemon != NULL){
        free(pokemon->name);
        free(pokemon->type);
        free(pokemon);
    }
}