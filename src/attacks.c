#include "attacks.h"

struct Attack {
    char *name;
    int is_damage_dealer;   // boolean
    int power;
    int is_MT;              // boolean
};

Attack ** readAttacks()
{
    FILE * atks;
    Attack **attacks;
    int attack_quantity = 1;
    int array_parser, i;
    char *pointer, *pointer2, *token;
    char **row;
    size_t bufsize;
    size_t characters;

    attacks = (Attack **) calloc(attack_quantity, sizeof(Attack *));
    attacks[0] = (Attack *) calloc(1, sizeof(Attack));

    atks = fopen("./data/attacks.csv","r");

    do
    {
        if(attack_quantity > 1)
        {
            attacks = (Attack **) realloc(attacks, attack_quantity * sizeof(Attack *));
            attacks[attack_quantity - 1] = (Attack *) calloc(1, sizeof(Attack));
        }
        bufsize = 32;
        array_parser = 0;

        pointer = (char *) calloc(bufsize, sizeof(char));

        characters = getline(&pointer, &bufsize, atks);
        if(characters == -1)
        {
            free(pointer);
            break;
        }
        pointer[characters] = '\0';

        pointer2 = pointer;

        row = (char **) calloc(4, sizeof(char*));

        token = strtok_r(pointer, ",", &pointer);
        row[array_parser] = token;
        array_parser++;

        for(i = array_parser; i < 4; i++) {
            if(token == NULL) 
            {
                free(row);
                break;
            }
            token = strtok_r(NULL, ",", &pointer);
            row[i] = token;
        }

        attacks[attack_quantity - 1]->name = strdup(row[0]);
        attacks[attack_quantity - 1]->is_damage_dealer = atoi(row[1]);
        attacks[attack_quantity - 1]->power = atoi(row[2]);
        attacks[attack_quantity - 1]->is_MT = atoi(row[3]);

        free(row);
        free(pointer2);
        
        attack_quantity++;
    } while(1);

    fclose(atks);
    return attacks;
}

void freeAttack(Attack *attack)
{
    if(attack != NULL) {
        free(attack->name);
        free(attack);
    }
}