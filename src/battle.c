#include "utils.h"
#include "battle.h"
#include "attacks.h"

struct BattleStage {
    Pokemon * cpu_pokemon;
    Pokemon * player_pokemon;
    float escapeTries;
    float captureTries;
};

struct BattleLog {
    BattleStage *battle;
    BattleLog *first;
    BattleLog *next;
    BattleLog *last;
};

struct Game {
    BattleLog * battle_log;
    int won_battles;
    int last_mew;
    int last_pokeball;
    int player_pokeballs;
};

Game * newGame(Game* game)
{
    game = (Game* ) calloc(1, sizeof(Game));
    game->battle_log = NULL;
    game->won_battles = 0;
    game->last_mew = 0;
    game->last_pokeball = 0;
    game->player_pokeballs = 3;

    return game;
}

BattleLog * newBattleLog(BattleLog* battle_log)
{
    if(battle_log == NULL)
    {
        battle_log = (BattleLog*) calloc(1, sizeof(BattleLog));
        battle_log->battle = (BattleStage*) calloc(1, sizeof(BattleStage));
        battle_log->next = NULL;
        battle_log->first = battle_log;
        battle_log->last = battle_log;
    }
    else
    {
        battle_log->next = (BattleLog*) calloc(1, sizeof(BattleLog));
        battle_log->next->first = battle_log->first;
        battle_log = battle_log->next;
        battle_log->last = battle_log;
        battle_log->battle = (BattleStage*) calloc(1, sizeof(BattleStage));
    }
    return battle_log;
}

int battle(Pokemon * player_pokemon, Pokemon * cpu_pokemon, Game * new_game)
{
    DebuffsList * player_debuffs = NULL;
    DebuffsList * cpu_debuffs = NULL;
    BattleStage * battle_stage = NULL;
    Pokemon * attacker;
    Pokemon * deffender;
    Attack **attacks = NULL;
    int turn = 0, attacksQuantity = 0, option, isPlayerTurn = 1;
    int * pokemon_attacks;
    float damage;
    char trash;

    attacks = readAttacks(&attacksQuantity);
    
    new_game->battle_log = newBattleLog(new_game->battle_log);
    battle_stage = new_game->battle_log->battle;
    battle_stage->player_pokemon = player_pokemon;
    battle_stage->cpu_pokemon = cpu_pokemon;
    
    printf("Um ");
    printPokemon(cpu_pokemon);
    printf(" selvagem aparece!\n\n");
    
    loadDispatchAttack();

    do{
        trash = system("clear");
        if(turn % 2 == 0) {
            attacker = player_pokemon;
            deffender = cpu_pokemon;
            pokemon_attacks = getPokemonATTACKS(player_pokemon);
            isPlayerTurn = 1;
        }else{
            attacker = cpu_pokemon;
            deffender = player_pokemon;
            pokemon_attacks = getPokemonATTACKS(cpu_pokemon);
            isPlayerTurn = 0;
        }

        damage = 0;
        if(isPlayerTurn) {
            printPokemon(cpu_pokemon);
            printf(": %.0f%% HP\n", (getPokemonActualHP(cpu_pokemon)/getPokemonHP(cpu_pokemon) * 100));
            printPokemon(player_pokemon);
            printf(": %.0f%% HP\n\n", (getPokemonActualHP(player_pokemon)/getPokemonHP(player_pokemon) * 100));
            
            printf("Escolha um movimento:\n");
            printf("1- %s\n", getAttackName(attacks[pokemon_attacks[0]]));
            printf("2- %s\n", getAttackName(attacks[pokemon_attacks[1]]));
            printf("3- %s\n", getAttackName(attacks[pokemon_attacks[2]]));
            printf("4- Pokebola (%d disponiveis)\n", new_game->player_pokeballs);
            printf("5- Fugir\n");
            option = getUserNumberInput(1, 5);
        }else{
            option = (int) 1 + rand() % 3;
        }

        switch (option)
        {
        case 1:
            damage = attackPokemon(pokemon_attacks[0] + 1, getPokemonATK(attacker), getPokemonDEF(deffender), player_debuffs, cpu_debuffs);
            damage = damage * typeRelation(getPokemonTYPE(attacker), getPokemonTYPE(deffender));
            setPokemonActualHP(deffender, getPokemonActualHP(deffender) - damage);
            break;
        case 2:
            damage = attackPokemon(pokemon_attacks[1] + 1, getPokemonATK(attacker), getPokemonDEF(deffender), player_debuffs, cpu_debuffs);
            damage = damage * typeRelation(getPokemonTYPE(attacker), getPokemonTYPE(deffender));
            setPokemonActualHP(deffender, getPokemonActualHP(deffender) - damage);
            break;
        case 3:
            damage = attackPokemon(pokemon_attacks[2] + 1, getPokemonATK(attacker), getPokemonDEF(deffender), player_debuffs, cpu_debuffs);
            damage = damage * typeRelation(getPokemonTYPE(attacker), getPokemonTYPE(deffender));
            setPokemonActualHP(deffender, getPokemonActualHP(deffender) - damage);
            break;
        default:
            break;
        }
        
        turn++;
    }while(getPokemonActualHP(cpu_pokemon) > 0 && getPokemonActualHP(player_pokemon) > 0);

    if(getPokemonActualHP(cpu_pokemon) <= 0)
    {
        return 1;
    }
    if(getPokemonActualHP(player_pokemon) <= 0)
    {
        return 0;
    }

    freeAttacks(attacks, attacksQuantity);
    free(attacks);
}

int getGameLastMew(Game * game)
{
    return game->last_mew;
}

void setGameLastMew(Game * game, int last_mew)
{
    game->last_mew = last_mew;
}

float typeRelation (int atk_type, int def_type)
{
    float relations[6][6];

    relations[0][0] = 0.5;
    relations[0][1] = 1;
    relations[0][2] = 2;
    relations[0][3] = 0.5;
    relations[0][4] = 1;
    relations[0][5] = 1;
    relations[1][0] = 1;
    relations[1][1] = 0.5;
    relations[1][2] = 0.5;
    relations[1][3] = 2;
    relations[1][4] = 2;
    relations[1][5] = 1;
    relations[2][0] = 1;
    relations[2][1] = 2;
    relations[2][2] = 0.5;
    relations[2][3] = 0.5;
    relations[2][4] = 1;
    relations[2][5] = 1;
    relations[3][0] = 1;
    relations[3][1] = 0.5;
    relations[3][2] = 2;
    relations[3][3] = 0.5;
    relations[3][4] = 0.5;
    relations[3][5] = 1;
    relations[4][0] = 0.5;
    relations[4][1] = 0.5;
    relations[4][2] = 0.5;
    relations[4][3] = 1;
    relations[4][4] = 0.5;
    relations[4][5] = 1;
    relations[5][0] = 1;
    relations[5][1] = 1;
    relations[5][2] = 1;
    relations[5][3] = 1;
    relations[5][4] = 0.5;
    relations[5][5] = 0.5;

    return relations[atk_type][def_type];
}

