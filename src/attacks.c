#include "../include/attacks.h"
#include "../include/battle.h"

fptrAttack doAttack[15];

fptrDebuff doDebuff[9];

struct Attack {
    char *name;
    int is_damage_dealer;   
    int power;
    int is_MT;              
};

struct Debuffs {
    int type;
    int roundsLeft;
};

struct DebuffsList {
    Debuffs * debuff;
    DebuffsList * start;
    DebuffsList * next;
    DebuffsList * last;
};

Attack ** readAttacks(int *attacksquantity)
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
    *attacksquantity = attack_quantity - 1; 
    return attacks;
}

void freeAttack(Attack *attack)
{
    if(attack != NULL) {
        free(attack->name);
        free(attack);
    }
}

char* getAttackName(Attack *attack)
{
    return attack->name;
}

void freeAttacks(Attack **attacks, int attacksQuantity)
{
    int i = 0;
    do{
        // if(attacks[i] == NULL) break;
        freeAttack(attacks[i]);
        i++;
    }while(i <= attacksQuantity);
    free(attacks);
}

void loadDispatchAttack()
{
    doAttack[0] = NULL;
    doAttack[1] = attack1;
    doAttack[2] = attack2;
    doAttack[3] = attack3;
    doAttack[4] = attack4;
    doAttack[5] = attack5;
    doAttack[6] = attack6;
    doAttack[7] = attack7;
    doAttack[8] = attack8;
    doAttack[9] = attack9;
    doAttack[10] = attack10;
    doAttack[11] = attack11;
    doAttack[12] = attack12;
    doAttack[13] = attack13;
    doAttack[14] = attack14;
}

void attackPokemon(int attack, Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation)
{
    fptrAttack atk;

    atk = doAttack[attack];

    atk(attacker, deffender, attacker_debuffs, deffender_debuffs, type_relation);
   
}

float calcDamage(int power, int A, int D, int is_MT)
{
    float dmg, MT = 1;
    int crit = 1;

    if(calcRandomThings((float) 1/24)) crit = 2;
    if(is_MT) MT = 1.5;

    dmg = (float) ((14 * power * A/D) / 50 + 2) * crit * MT;

    return dmg;
}

float calcRandomThings(float probability) {
    float random = (float) rand()/(float)(RAND_MAX);

    if(random <= probability){
        return 1;
    }
    else{
        return 0;
    }
}

int findDebuffOnList(int type, DebuffsList * debuff_list)
{
    DebuffsList * actual_cell = debuff_list;

    do{
        if(actual_cell->debuff->type == type) return 1;
        actual_cell = actual_cell->next;
    }while(actual_cell != NULL);

    return 0;
}

void attack1(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation)
{
    float dmg;
    printf("Choque do Trovao");
    
    if(getIsVulnerable(deffender)){
        dmg = calcDamage(40, getPokemonATK(attacker), getPokemonDEF(deffender), 1) * type_relation;

        setPokemonActualHP(deffender, getPokemonActualHP(deffender) - dmg);

        if(calcRandomThings((float) 1/10))
        {  
            deffender_debuffs = createDebuff(deffender_debuffs);
            deffender_debuffs->debuff->type = 0;
            deffender_debuffs->debuff->roundsLeft = 2;
        }
    }
    else
    {   
        printf("\nAtaque bloqueado!");
    }
}

void attack2(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation)
{
    printf("Onda de Choque");
    if(getIsVulnerable(deffender)){
        deffender_debuffs = createDebuff(deffender_debuffs);
        deffender_debuffs->debuff->type = 0;
        deffender_debuffs->debuff->roundsLeft = 2;
    }
    else
    {
         printf("\nAtaque bloqueado!");
    }
}

void attack3(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation)
{
    float dmg;
    
    printf("Bater");
    if(getIsVulnerable(deffender))
    {
        dmg = calcDamage(40, getPokemonATK(attacker), getPokemonDEF(deffender), 0) * type_relation;

        setPokemonActualHP(deffender, getPokemonActualHP(deffender) - dmg);
    }
    else
    {   
        printf("\nAtaque bloqueado!");
    }
}

void attack4(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation)
{
    float dmg;

    printf("Lanca Chamas");

    if(getIsVulnerable(deffender)){
        dmg = calcDamage(90, getPokemonATK(attacker), getPokemonDEF(deffender), 1) * type_relation;

        setPokemonActualHP(deffender, getPokemonActualHP(deffender) - dmg);

        if(calcRandomThings((float) 1/10))
        {
            deffender_debuffs = createDebuff(deffender_debuffs);
            deffender_debuffs->debuff->type = 1;
            deffender_debuffs->debuff->roundsLeft = -1;
        }
    }
    else
    {   
        printf("\nAtaque bloqueado!");
    }

}

void attack5(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation)
{

    printf("Dormir");
    attacker_debuffs = createDebuff(attacker_debuffs);
    attacker_debuffs->debuff->type = 2;
    attacker_debuffs->debuff->roundsLeft = 4;
}

void attack6(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation)
{
    float dmg;
    
    printf("Arma de Agua");
    if(getIsVulnerable(deffender))
    {
        dmg = calcDamage(40, getPokemonATK(attacker), getPokemonDEF(deffender), 1) * type_relation;

        setPokemonActualHP(deffender, getPokemonActualHP(deffender) - dmg);
    } 
    else
    {   
        printf("\nAtaque bloqueado!");
    }
}

void attack7(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation)
{
    printf("Proteger");
    attacker_debuffs = createDebuff(attacker_debuffs);
    attacker_debuffs->debuff->type = 3;
    attacker_debuffs->debuff->roundsLeft = 2;
}

void attack8(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation)
{
    printf("Po de Sono");
    if(getIsVulnerable(deffender))
    {
        int roundsLeft = (int) (1 + (rand() % 3)) * 2;
        deffender_debuffs = createDebuff(deffender_debuffs);
        deffender_debuffs->debuff->type = 4;
        deffender_debuffs->debuff->roundsLeft = roundsLeft;
    }
    else
    {   
        printf("\nAtaque bloqueado!");
    }
}

void attack9(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation)
{
    float dmg;

    printf("Bomba de Semente");

    if(getIsVulnerable(deffender))
    {
        dmg = calcDamage(80, getPokemonATK(attacker), getPokemonDEF(deffender), 1) * type_relation;

        setPokemonActualHP(deffender, getPokemonActualHP(deffender) - dmg);
    }
    else
    {   
        printf("\nAtaque bloqueado!");
    }
}

void attack10(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation)
{
    float dmg;

    printf("Dois Gumes");

    dmg = calcDamage(120, getPokemonATK(attacker), getPokemonDEF(deffender), 0) * type_relation;

    if(getIsVulnerable(deffender))
    {
        setPokemonActualHP(deffender, getPokemonActualHP(deffender) - dmg);
        
    }
    else
    {
        printf("\nAtaque bloqueado!");
    }

    dmg = dmg / 3;

    setPokemonActualHP(attacker, getPokemonActualHP(attacker) - dmg);
}

void attack11(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation)
{
    float dmg;

    printf("Rabo de Ferro");
    
    if(getIsVulnerable(deffender))
    {
        dmg = calcDamage(100, getPokemonATK(attacker), getPokemonDEF(deffender), 1) * type_relation;
        
        setPokemonActualHP(deffender, getPokemonActualHP(deffender) - dmg);
    }
    else
    {
        printf("\nAtaque bloqueado!");
    }
}

void attack12(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation)
{
    printf("Cavar");
    attacker_debuffs = createDebuff(attacker_debuffs);
    attacker_debuffs->debuff->type = 5;
    attacker_debuffs->debuff->roundsLeft = 2;
}

void attack13(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation)
{
    printf("Metronomo");
}

void attack14(Pokemon * attacker, Pokemon * deffender, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs, float type_relation)
{
    float dmg;

    printf("Auto-destruir");
    
    if(getIsVulnerable(deffender))
    {
        dmg = calcDamage(200, getPokemonATK(attacker), getPokemonDEF(deffender), 0) * type_relation;

        setPokemonActualHP(deffender, getPokemonActualHP(deffender) - dmg);
    }
    else
    {
        printf("\nAtaque bloqueado!");
    }

    setPokemonActualHP(attacker, -1);
}

DebuffsList * createDebuff(DebuffsList * debuff_list)
{
    if(debuff_list == NULL)
    {
        debuff_list = (DebuffsList*) calloc(1, sizeof(DebuffsList));
        debuff_list->debuff = (Debuffs*) calloc(1, sizeof(Debuffs));
        debuff_list->debuff->type = -1;
        debuff_list->start = debuff_list;
        debuff_list->next = NULL;
        debuff_list->last = debuff_list;
    }else{
        debuff_list->next = (DebuffsList*) calloc(1, sizeof(DebuffsList));
        debuff_list->next->start = debuff_list->start;
        debuff_list = debuff_list->next;
        debuff_list->debuff = (Debuffs*) calloc(1, sizeof(Debuffs));
        debuff_list->debuff->type = -1;
        debuff_list->next = NULL;
        debuff_list->last = debuff_list;
    }

    return debuff_list;
}

void freeDebuffsList(DebuffsList * debuff_list)
{
    DebuffsList * actual_cell;

    actual_cell = debuff_list;

    do{
        debuff_list = actual_cell;
        actual_cell = actual_cell->next;
        free(debuff_list->debuff);
        free(debuff_list);
    }while(actual_cell != NULL);

}

DebuffsList * getLastDebuff(DebuffsList * debuff_list)
{
    DebuffsList * actual_cell;
    actual_cell = debuff_list;

    while(actual_cell->next != NULL) {
        actual_cell = actual_cell->next;
    }

    return actual_cell;
}

DebuffsList * getFirstDebuff(DebuffsList * debuff_list)
{
    return debuff_list->start;
}

void printDebuffsList(DebuffsList * debuff_list)
{
    DebuffsList * actual_cell;
    int i = 0;

    actual_cell = debuff_list;

    do{
        printf("[tipo %d falta %d]", actual_cell->debuff->type, actual_cell->debuff->roundsLeft);
        i++;
        actual_cell = actual_cell->next;
    }while(actual_cell != NULL);
}

void modifyStartPositionDebuffsList(DebuffsList * list)
{
    DebuffsList * actual_cell = list;
    DebuffsList * start_cell = list;

    do{
        actual_cell->start = start_cell;
        actual_cell = actual_cell->next;
    }while(actual_cell != NULL);
}

void loadDispatchDebuff(){
    doDebuff[0] = debuff1;
    doDebuff[1] = debuff2;
    doDebuff[2] = debuff3;
    doDebuff[3] = debuff4;
    doDebuff[4] = debuff5;
    doDebuff[5] = debuff6;
}

void passTurn(DebuffsList * debuffs_list)
{
    DebuffsList * actual_debuff;

    do{
        actual_debuff->debuff->roundsLeft--;
        actual_debuff = actual_debuff->next;
    }while(actual_debuff != NULL);
}

void debuffPokemon(int * conditions, Pokemon * pokemon, DebuffsList * debuffs_list)
{
    fptrDebuff dbff;
    DebuffsList * actual_debuff = debuffs_list;
    DebuffsList * next_debuff = NULL;
    DebuffsList * previous_debuff = NULL;
    int is_removing;

    
    do{
        is_removing = 0;

        next_debuff = actual_debuff->next;
        if(actual_debuff->debuff->type >= 0) {
            dbff = doDebuff[actual_debuff->debuff->type];

            if(actual_debuff->debuff->roundsLeft == 0)
            {
                is_removing = 1;
                if(previous_debuff == NULL)
                {
                    actual_debuff->next->start = actual_debuff->next;
                    modifyStartPositionDebuffsList(actual_debuff->next);
                }else{
                    previous_debuff->next = next_debuff;
                }
                
                free(actual_debuff->debuff);
                free(actual_debuff);
            }
            dbff(conditions, pokemon, is_removing);
        }
        
        if(!is_removing) previous_debuff = actual_debuff;
        actual_debuff = next_debuff;
    }while(actual_debuff != NULL);
    
}

void debuff1(int * conditions, Pokemon * pokemon, int is_removing)
{
    if(is_removing)
    {
        conditions[0] = 0;
    }else
    {
        conditions[0] = 1;
    }
}

void debuff2(int * conditions, Pokemon * pokemon, int is_removing)
{
    conditions[1] = 1;
}

void debuff3(int * conditions, Pokemon * pokemon, int is_removing)
{
    if(is_removing)
    {
        conditions[2] = 0;
        setPokemonActualHP(pokemon, getPokemonHP(pokemon));
    }else
    {
        conditions[2] = 1;
    }
}

void debuff4(int * conditions, Pokemon * pokemon, int is_removing)
{
    if(is_removing)
    {
        conditions[3] = 0;
    }else
    {
        conditions[3] = 1;
    }
}

void debuff5(int * conditions, Pokemon * pokemon, int is_removing)
{
    if(is_removing)
    {
        conditions[2] = 0;
    }else
    {
        conditions[2] = 1;
    }
}

void debuff6(int * conditions, Pokemon * pokemon, int is_removing)
{
    if(is_removing)
    {
        conditions[4] = 0;
    }else
    {
        conditions[4] = 1;
    }
}

