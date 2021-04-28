#include "pokemon.h"
#include "attacks.h"

struct Pokemon {
    char *name;
    int hp;
    int atk;
    int def;
    int type;
    struct Attack *attacks;
};

Pokemon* readPokemons()
{
    FILE *poke;
    Pokemon **pokemons;
    int pokemons_quantity = 1, ended = 0;
    int array_parser;
    long unsigned int size;
    char *pointer, *pointer2, *token;
    char **row;
    size_t bufsize = 32;
    size_t characters;

    pokemons = (Pokemon** ) calloc(pokemons_quantity, sizeof(Pokemon*));

    poke = fopen("./data/pokemons.csv","r");

    do
    {
        size = 0;
        array_parser = 0;

        pointer = (char *) calloc(bufsize, sizeof(char));

        characters = getline(&pointer, &size, poke);
        if(!characters)
        {
            free(pointer);
            break;
        }

        pointer2 = pointer;

        row = (char **) calloc(8, sizeof(char*));

        token = strtok_r(pointer, ",", &pointer);
        row[array_parser] = token;
        array_parser++;

        while(token != NULL) {
            if(token == NULL) 
            {
                free(row);
                break;
            }
            token = strtok_r(NULL, ",", &pointer);
            row[array_parser] = token;
            array_parser++;
        }

        free(row);
        free(pointer2);
        getchar();

    } while(!ended);

    fclose(poke);
    getchar();
}