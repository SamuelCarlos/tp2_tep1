#include "pokemon.h"
#include "attacks.h"

struct Pokemon {
    int id;
    char *name;
    float hp;
    float actual_hp;
    int atk;
    int def;
    int type;
    int *attacks;
};

struct PokemonsList {
    Pokemon *pokemon;
    PokemonsList *next;
};

PokemonsList * readPokemons(int *quantity)
{
    FILE *poke;
    Pokemon *pokemon;
    PokemonsList *poke_list;
    PokemonsList *actual_cell;
    int pokemons_quantity = 1, ended = 0;
    int array_parser, i;
    char *pointer, *pointer2, *token;
    char **row;
    size_t bufsize;
    size_t characters;

    poke_list = (PokemonsList*) calloc(1, sizeof(PokemonsList));
    poke_list->pokemon = createPokemon(poke_list->pokemon);
    poke_list->next = NULL;
    actual_cell = poke_list;

    poke = fopen("./data/pokemons.csv","r");

    do
    {
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

        if(pokemons_quantity > 1) 
        {
            addPokemonOnList(actual_cell);
            actual_cell = actual_cell->next;
        }

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

        actual_cell->pokemon->id = pokemons_quantity;
        actual_cell->pokemon->name = strdup(row[0]);
        actual_cell->pokemon->hp = atoi(row[1]);
        actual_cell->pokemon->actual_hp = atoi(row[1]);
        actual_cell->pokemon->atk = atoi(row[2]);
        actual_cell->pokemon->def = atoi(row[3]);
        actual_cell->pokemon->type = atoi(row[4]);
        actual_cell->pokemon->attacks[0] = atoi(row[5])-1;
        actual_cell->pokemon->attacks[1] = atoi(row[6])-1;
        actual_cell->pokemon->attacks[2] = atoi(row[7])-1;
        
        free(row);
        free(pointer2);
        
        pokemons_quantity++;
    } while(!ended);

    fclose(poke);
    *quantity = pokemons_quantity - 1;
    return poke_list;
}

void printPokemon(Pokemon *pokemon) 
{
    printf("%s", pokemon->name);
}

void printPokemonList(PokemonsList *poke_list)
{
    PokemonsList *actual_cell;
    int i = 1;

    actual_cell = poke_list;

    do
    {
        printf("%d - ", i);
        printPokemon(actual_cell->pokemon);
        printf("\n");
        actual_cell = actual_cell->next;
        i++;
    }while(actual_cell != NULL);
}


PokemonsList * addPokemonOnList(PokemonsList *poke_list)
{
    if(poke_list == NULL)
    {
        poke_list = (PokemonsList*) calloc(1, sizeof(PokemonsList));
        poke_list->pokemon = createPokemon(poke_list->pokemon);
        poke_list->next = NULL;
        return poke_list;
    }
    else
    {
        poke_list->next = (PokemonsList *) calloc(1, sizeof(PokemonsList));
        poke_list = poke_list->next;
        poke_list->pokemon = createPokemon(poke_list->pokemon);
        poke_list->next = NULL;
        return poke_list;
    }
}

PokemonsList * removePokemonFromList(PokemonsList *poke_list, int position)
{
    int i;
    PokemonsList *actual_cell;
    PokemonsList *previous_cell;

    actual_cell = poke_list;
    previous_cell = NULL;

    for(i = 0; i < position; i++)
    {
        previous_cell = actual_cell;
        if(actual_cell->next != NULL)
        {
            actual_cell = actual_cell->next;
        }
    }

    if(previous_cell == NULL)
    {
        poke_list = actual_cell->next;
    }
    else
    {
        previous_cell->next = actual_cell->next;
    }

    freePokemon(actual_cell->pokemon);
    free(actual_cell);

    return poke_list;
}

Pokemon * readPokemonFromList(PokemonsList *poke_list, int position)
{
    int i;
    PokemonsList *actual_cell;

    actual_cell = poke_list;

    for(i = 0; i < position - 1; i++)
    {
        actual_cell = actual_cell->next;
    }

    return actual_cell->pokemon;
}

Pokemon * createPokemon()
{
    Pokemon * pokemon;
    pokemon = (Pokemon*) calloc(1, sizeof(Pokemon));
    pokemon->attacks = (int *) calloc(3, sizeof(int));
    return pokemon;
}

PokemonsList * attributePokemonToCell(PokemonsList* cell, Pokemon* pokemon)
{
    cell->pokemon->id = pokemon->id;
    cell->pokemon->name = strdup(pokemon->name);
    cell->pokemon->hp = pokemon->hp;
    cell->pokemon->actual_hp = pokemon->hp;
    cell->pokemon->atk = pokemon->atk;
    cell->pokemon->def = pokemon->def;
    cell->pokemon->type = pokemon->type;
    cell->pokemon->attacks[0] = pokemon->attacks[0];
    cell->pokemon->attacks[1] = pokemon->attacks[1];
    cell->pokemon->attacks[2] = pokemon->attacks[2];

    return cell;
}

void freePokemon(Pokemon *pokemon) 
{
    if(pokemon != NULL){
        free(pokemon->name);
        free(pokemon->attacks);
        free(pokemon);
    }
}

void freePokemonList(PokemonsList *poke_list)
{
    PokemonsList *actual_cell;

    actual_cell = poke_list;

    do{
        poke_list = actual_cell;
        freePokemon(actual_cell->pokemon);

        actual_cell = actual_cell->next;
        free(poke_list);
    }while(actual_cell != NULL);

  
}

float getPokemonHP(Pokemon *pokemon)
{
    return pokemon->hp;
}

float getPokemonActualHP(Pokemon *pokemon)
{
    return pokemon->actual_hp;
}

void setPokemonActualHP(Pokemon *pokemon, float new_hp)
{
    pokemon->actual_hp = new_hp;
}

int getPokemonATK(Pokemon *pokemon)
{
    return pokemon->atk;
}

int getPokemonDEF(Pokemon *pokemon)
{
    return pokemon->def;
}

int getPokemonTYPE(Pokemon *pokemon)
{
    return pokemon->type;
}

int getPokemonATTACKS1(Pokemon *pokemon)
{
    int atk = pokemon->attacks[0];
    return atk;
}

int getPokemonATTACKS2(Pokemon *pokemon)
{
    int atk = pokemon->attacks[1];
    return atk;
}

int getPokemonATTACKS3(Pokemon *pokemon)
{
    int atk = pokemon->attacks[2];
    return atk;
}

Pokemon * copyPokemon(Pokemon *poke, Pokemon *poke2)
{
    poke->id = poke2->id;
    poke->name = strdup(poke2->name);
    poke->hp = poke2->hp;
    poke->actual_hp = poke2->hp;
    poke->atk = poke2->atk;
    poke->def = poke2->def;
    poke->type = poke2->type;
    poke->attacks[0] = poke2->attacks[0];
    poke->attacks[1] = poke2->attacks[1];
    poke->attacks[2] = poke2->attacks[2];

    return poke;
}