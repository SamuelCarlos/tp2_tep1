#include "attacks.h"
#include "battle.h"

typedef float (*fptrAttack)(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs);

fptrAttack doAttack[15];
struct Attack {
    char *name;
    int is_damage_dealer;   // boolean
    int power;
    int is_MT;              // boolean
};

struct Debuffs {
    int type;
    int roundsLeft;
};

struct DebuffsList {
    Debuffs * debuff;
    DebuffsList * start;
    DebuffsList * next;
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
        //if(attacks[i] == NULL) break;
        freeAttack(attacks[i]);
        i++;
    }while(i <= attacksQuantity);
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

float attackPokemon(int attack, int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs)
{
    fptrAttack atk;
    float dmg;

    atk = doAttack[attack];

    dmg = atk(attacker_atk, deffender_def, attacker_debuffs, deffender_debuffs);
    return dmg;
}

float calcDamage(int power, int A, int D, int is_MT)
{
    float dmg, MT = 1;
    int crit = 1;

    if(calcRandomThings(1/24)) crit = 2;
    if(is_MT) MT = 1.5;

    dmg = ((14 * power * A/D) / 50 + 2) * crit * MT;

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

float attack1(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs)
{
    float dmg;
    
    dmg = calcDamage(40, attacker_atk, deffender_def, 1);

    if(calcRandomThings(1/10))
    {
        deffender_debuffs = createDebuff(deffender_debuffs);
        deffender_debuffs->debuff->type = 0;
        deffender_debuffs->debuff->roundsLeft = 1;
    }

    return dmg;
}

float attack2(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs)
{
    deffender_debuffs = createDebuff(deffender_debuffs);
    deffender_debuffs->debuff->type = 0;
    deffender_debuffs->debuff->roundsLeft = 1;

    return 0;
}

float attack3(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs)
{
    float dmg;
    
    dmg = calcDamage(40, attacker_atk, deffender_def, 0);

    return dmg;
}

float attack4(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs)
{
    float dmg;
    
    dmg = calcDamage(90, attacker_atk, deffender_def, 1);

    if(calcRandomThings(1/10))
    {
        deffender_debuffs = createDebuff(deffender_debuffs);
        deffender_debuffs->debuff->type = 1;
        deffender_debuffs->debuff->roundsLeft = -1;
    }

    return dmg;
}

float attack5(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs)
{
    attacker_debuffs = createDebuff(attacker_debuffs);
    attacker_debuffs->debuff->type = 2;
    attacker_debuffs->debuff->roundsLeft = 2;

    return 0;
}

float attack6(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs)
{
    float dmg;
    
    dmg = calcDamage(40, attacker_atk, deffender_def, 1);

    return dmg;
}

float attack7(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs)
{
    attacker_debuffs = createDebuff(attacker_debuffs);
    attacker_debuffs->debuff->type = 3;
    attacker_debuffs->debuff->roundsLeft = 1;

    return 0;
}

float attack8(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs)
{
    int roundsLeft = (int) 1 + (rand() % 2);
    deffender_debuffs = createDebuff(deffender_debuffs);
    deffender_debuffs->debuff->type = 4;
    deffender_debuffs->debuff->roundsLeft = roundsLeft;

    return 0;
}

float attack9(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs)
{
    float dmg;
    
    dmg = calcDamage(80, attacker_atk, deffender_def, 1);

    return dmg;
}

float attack10(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs)
{
    float dmg;
    
    dmg = calcDamage(120, attacker_atk, deffender_def, 0);

    attacker_debuffs = createDebuff(attacker_debuffs);
    attacker_debuffs->debuff->type = 5;
    attacker_debuffs->debuff->roundsLeft = 0;

    return dmg;
}

float attack11(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs)
{
    float dmg;
    
    dmg = calcDamage(100, attacker_atk, deffender_def, 1);

    return dmg;
}

float attack12(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs)
{
    attacker_debuffs = createDebuff(attacker_debuffs);
    attacker_debuffs->debuff->type = 6;
    attacker_debuffs->debuff->roundsLeft = 1;

    return 0;
}

float attack13(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs)
{
    fptrAttack atk;
    int random = (int) 1 + (rand() % 13);

    while (random == 13)
    {
        random = (int) 1 + (rand() % 13);
    }

    atk = doAttack[random];

    return atk(attacker_atk, deffender_def, attacker_debuffs, deffender_debuffs); 
}

float attack14(int attacker_atk, int deffender_def, DebuffsList* attacker_debuffs, DebuffsList* deffender_debuffs)
{
    float dmg;
    
    dmg = calcDamage(200, attacker_atk, deffender_def, 0);

    attacker_debuffs = createDebuff(attacker_debuffs);
    attacker_debuffs->debuff->type = 7;
    attacker_debuffs->debuff->roundsLeft = 0;

    return dmg;
}

DebuffsList * createDebuff(DebuffsList * debuff_list)
{
    if(debuff_list == NULL)
    {
        debuff_list = (DebuffsList*) calloc(1, sizeof(DebuffsList));
        debuff_list->debuff = (Debuffs*) calloc(1, sizeof(Debuffs));
        debuff_list->start = debuff_list;
        debuff_list->next = NULL;
    }else{
        debuff_list->next = (DebuffsList*) calloc(1, sizeof(DebuffsList));
        debuff_list->next->start = debuff_list->start;
        debuff_list = debuff_list->next;
        debuff_list->debuff = (Debuffs*) calloc(1, sizeof(Debuffs));
        debuff_list->next = NULL;
    }

    return debuff_list;
}