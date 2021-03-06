#include "../include/utils.h"
#include "../include/battle.h"
#include "../include/attacks.h"

struct BattleStage {
    Pokemon * cpu_pokemon;
    Pokemon * player_pokemon;
    float escapeTries;
    float captureTries;
    int cpu_conditions[7];
    int player_conditions[7];
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

int battle(Pokemon * player_pokemon, Pokemon * cpu_pokemon, Game * new_game, FILE * logs)
{
    Pokemon *attacker;
    Pokemon *deffender;
    Attack **attacks = NULL;
    DebuffsList *attacker_debuffs;
    DebuffsList *deffender_debuffs;
    BattleStage *battle_stage = NULL;
    DebuffsList *cpu_debuffs = createDebuff(cpu_debuffs);
    DebuffsList *player_debuffs = createDebuff(player_debuffs);
    char trash;
    float randomToRun, type_relation, dmg;
    int i, turn = 0, randomToAttack, attacksQuantity = 0, option, isPlayerTurn = 1, run_away = 0, captured = 0, player_has_attacked = 0, is_disabled = 0, emerging = 0, conditions_qtt = 0;
    int *pokemon_attacks, *cpu_conditions, *player_conditions, *attacker_conditions, *deffender_conditions;

    attacks = readAttacks(&attacksQuantity);

    // initialize the battle_log list    
    new_game->battle_log = newBattleLog(new_game->battle_log);
    battle_stage = new_game->battle_log->battle;
    battle_stage->player_pokemon = player_pokemon;
    battle_stage->cpu_pokemon = cpu_pokemon;
    battle_stage->captureTries = 0;
    battle_stage->escapeTries = 0;


    cpu_conditions = (int* ) calloc(7, sizeof(int));
    player_conditions = (int* ) calloc(7, sizeof(int));
    
    // verifies if cpu pokemon is "new"
    if(getPokemonActualHP(cpu_pokemon) == getPokemonHP(cpu_pokemon))
    {
        printf("Um ");
        printPokemon(cpu_pokemon);
        printf(" selvagem aparece!\n\n");
    }
    
    loadDispatchAttack();
    loadDispatchDebuff();

    do
    {
        is_disabled = 0;
        pokemon_attacks = (int *) calloc(3, sizeof(int));

        if(turn % 2 == 0) {
            deffender = cpu_pokemon;
            attacker = player_pokemon;
            deffender_debuffs = cpu_debuffs;
            attacker_debuffs = player_debuffs;
            deffender_conditions = cpu_conditions;
            attacker_conditions = player_conditions;
            pokemon_attacks[0] = getPokemonATTACKS1(player_pokemon);
            pokemon_attacks[1] = getPokemonATTACKS2(player_pokemon);
            pokemon_attacks[2] = getPokemonATTACKS3(player_pokemon);
            isPlayerTurn = 1;        
        }else{
            attacker = cpu_pokemon;
            deffender = player_pokemon;
            attacker_debuffs = cpu_debuffs;
            deffender_debuffs = player_debuffs;
            attacker_conditions = cpu_conditions;
            deffender_conditions = player_conditions;
            pokemon_attacks[0] = getPokemonATTACKS1(cpu_pokemon);
            pokemon_attacks[1] = getPokemonATTACKS2(cpu_pokemon);
            pokemon_attacks[2] = getPokemonATTACKS3(cpu_pokemon);
            isPlayerTurn = 0;
        }
      
        // apply burning damage condition
        if(attacker_conditions[1]){
            setPokemonActualHP(attacker, getPokemonActualHP(attacker) - (getPokemonHP(attacker)/16));
            if(getPokemonActualHP(attacker) < 0)
            {   
                if(pokemon_attacks != NULL) free(pokemon_attacks);
                break;
            }
        }
        
        for(i = 0; i < 5; i++)
        {
            if(attacker_conditions[i] && i != 1) is_disabled = 1;
        }
       
        type_relation = typeRelation(getPokemonTYPE(attacker), getPokemonTYPE(deffender));
        option = 0;

        if(emerging) {
            is_disabled = 1;
            if(deffender_conditions[4] || deffender_conditions[3])
            {
                printf("Emergir bloqueado!\n");
            }else{
                dmg = calcDamage(80, getPokemonATK(attacker), getPokemonDEF(deffender), 0) * type_relation;
                setPokemonActualHP(deffender, getPokemonActualHP(deffender) - dmg);
            }
        }   
        emerging = 0;
        
        conditions_qtt = 0;
        fprintf(logs, "\t%s: %.0f%% HP ", getPokemonName(player_pokemon), (getPokemonActualHP(player_pokemon)/getPokemonHP(player_pokemon) * 100));
        for (i = 0; i < 3; i++)
        {
            if(player_conditions[i])
            {
                conditions_qtt++;
            }
        }
        if(conditions_qtt > 0){
            fprintf(logs, "(");
            if(player_conditions[0]){
                fprintf(logs, "paralizado");
                conditions_qtt--;
                if(conditions_qtt > 0) fprintf(logs, ",");
            }
            if(player_conditions[1]){
                fprintf(logs, "queimando");
                conditions_qtt--;
                if(conditions_qtt > 0) fprintf(logs, ",");
            }
            if(player_conditions[2]){
                fprintf(logs, "dormindo");
                conditions_qtt--;
            }
            fprintf(logs, ")");
        }
        fprintf(logs, "\n");
        conditions_qtt = 0;
        fprintf(logs, "\t%s: %.0f%% HP ", getPokemonName(cpu_pokemon), (getPokemonActualHP(cpu_pokemon)/getPokemonHP(cpu_pokemon) * 100));
        for (i = 0; i < 3; i++)
        {
            if(cpu_conditions[i])
            {
                conditions_qtt++;
            }
        }
        if(conditions_qtt > 0){
            fprintf(logs, "(");
            if(cpu_conditions[0]){
                fprintf(logs, "paralizado");
                conditions_qtt--;
                if(conditions_qtt > 0) fprintf(logs, ",");
            }
            if(cpu_conditions[1]){
                fprintf(logs, "queimando");
                conditions_qtt--;
                if(conditions_qtt > 0) fprintf(logs, ",");
            }
            if(cpu_conditions[2]){
                fprintf(logs, "dormindo");
                conditions_qtt--;
            }
            fprintf(logs, ")");
        }
        fprintf(logs, "\n\n");
        /**
         * Print pokemons data on screen;
         */
        printPokemon(cpu_pokemon);
        printf(": %.0f%% HP ", (getPokemonActualHP(cpu_pokemon)/getPokemonHP(cpu_pokemon) * 100));
        printf("(");
        if(cpu_conditions[0]) printf(" paralizado ");
        if(cpu_conditions[1]) printf(" queimando ");
        if(cpu_conditions[2]) printf(" dormindo ");
        if(cpu_conditions[3]) printf(" defendendo ");
        if(cpu_conditions[4]) printf(" enterrado ");
        printf(")\n");
        printPokemon(player_pokemon);
        printf(" do jogador: %.0f%% HP ", (getPokemonActualHP(player_pokemon)/getPokemonHP(player_pokemon) * 100));
        printf("(");
        if(player_conditions[0]) printf(" paralizado ");
        if(player_conditions[1]) printf(" queimando ");
        if(player_conditions[2]) printf(" dormindo ");
        if(player_conditions[3]) printf(" defendendo ");
        if(player_conditions[4]) printf(" enterrado ");
        printf(")\n");
        
        getchar();

        if(!is_disabled){
            if(isPlayerTurn) {
                do {
                    if(option == 4)
                    {
                        printf("Voce nao possui pokebolas!\n");
                    }
                    option = 0;

                    printf("Escolha um movimento:\n");
                    printf("1- %s\n", getAttackName(attacks[pokemon_attacks[0]]));
                    printf("2- %s\n", getAttackName(attacks[pokemon_attacks[1]]));
                    printf("3- %s\n", getAttackName(attacks[pokemon_attacks[2]]));
                    printf("4- Pokebola (%d disponiveis)\n", new_game->player_pokeballs);
                    printf("5- Fugir\n");
                    option = getUserNumberInput(1, 5);
                }while(option == 4 && new_game->player_pokeballs == 0);
            }else{
                option = (int) 1 + (rand() % 3);
            }
        }else{
            printPokemon(attacker);
            printf(" esta incapacitado.\n");
        }

        trash = system("clear");

        if(deffender_conditions[4])
        {
            emerging = 1;
        }
        switch (option)
        {
            case 1:
                fprintf(logs, "\t%s usa %s ", getPokemonName(attacker), getAttackName(attacks[pokemon_attacks[option-1]]));
                printPokemon(attacker);
                printf(" usou ");
                if((deffender_conditions[3] || deffender_conditions[4])) 
                {
                    setIsVulnerable(deffender,0);
                }
                else
                {
                    setIsVulnerable(deffender,1);
                }
                attackPokemon(pokemon_attacks[0] + 1, attacker, deffender, getLastDebuff(attacker_debuffs), getLastDebuff(deffender_debuffs), type_relation);
                if(pokemon_attacks[option-1] == 12)
                {
                    randomToAttack = 1 + (rand() % 14);

                    while (randomToAttack == 13)
                    {
                        randomToAttack = 1 + (rand() % 14);
                    }
                    fprintf(logs, "(%s)", getAttackName(attacks[ randomToAttack - 1 ]));
                    printf(" (");
                    attackPokemon(randomToAttack, attacker, deffender, getLastDebuff(attacker_debuffs), getLastDebuff(deffender_debuffs), type_relation);
                    printf(")");
                }
                printf("\n");
                if(type_relation > 1) printf("Eh muito efetivo!\n");
                if(type_relation < 1) printf("Eh pouco efetivo!\n");
            
                fprintf(logs, "\n");
                break;
            case 2:
                fprintf(logs, "\t%s usa %s\n", getPokemonName(attacker), getAttackName(attacks[pokemon_attacks[option-1]]));
                printPokemon(attacker);
                printf(" usou ");
               if((deffender_conditions[3] || deffender_conditions[4])) 
                {
                    setIsVulnerable(deffender,0);
                }
                else
                {
                    setIsVulnerable(deffender,1);
                }
                attackPokemon(pokemon_attacks[1] + 1, attacker, deffender, getLastDebuff(attacker_debuffs), getLastDebuff(deffender_debuffs), type_relation);
                printf("\n");
                if(type_relation > 1) printf("Eh muito efetivo!\n");
                if(type_relation < 1) printf("Eh pouco efetivo!\n");
            
                break;
            case 3:
                fprintf(logs, "\t%s usa %s\n", getPokemonName(attacker), getAttackName(attacks[pokemon_attacks[option-1]]));
                printPokemon(attacker);
                printf(" usou ");
                if((deffender_conditions[3] || deffender_conditions[4])) 
                {
                    setIsVulnerable(deffender,0);
                }
                else
                {
                    setIsVulnerable(deffender,1);
                }

                attackPokemon(pokemon_attacks[2] + 1, attacker, deffender, getLastDebuff(attacker_debuffs), getLastDebuff(deffender_debuffs), type_relation);
                printf("\n");
                if(type_relation > 1) printf("Eh muito efetivo!\n");
                if(type_relation < 1) printf("Eh pouco efetivo!\n");

                break;
            case 4: 
                fprintf(logs, "\tTentativa de Captura\n");
                printf("Voce tentou capturar o ");
                printPokemon(deffender);
                printf(" e");
                new_game->player_pokeballs--;
                if(calcRandomThings((float) (getPokemonHP(cpu_pokemon)/getPokemonActualHP(cpu_pokemon))/20))
                {
                    captured = 1;
                    fprintf(logs, "\tSucesso\n");
                    printf(" conseguiu!\n");
                }else{
                    fprintf(logs, "\tFracasso\n");
                    printf(" falhou!\n");
                }
                break;
            case 5:
                fprintf(logs, "\tTentativa de Fuga\n");
                printf("Voce tentou fugir e ");
                battle_stage->escapeTries++;

                if(player_has_attacked) {
                    randomToRun = calcRandomThings((float) 1/16);
                }else
                {
                    randomToRun = calcRandomThings((float) battle_stage->escapeTries / 4);
                }

                if(randomToRun){ 
                    run_away = 1;
                    fprintf(logs, "\tSucesso\n");
                    printf("conseguiu!\n");
                }else{
                    fprintf(logs, "\tFracasso\n");
                    printf("falhou!\n");
                }
                break;
            default:
                break;
        }

        printf("\n");
        getchar();
        passTurn(getFirstDebuff(player_debuffs));
        passTurn(getFirstDebuff(cpu_debuffs));
        debuffPokemon(attacker_conditions, attacker, getFirstDebuff(attacker_debuffs));
        debuffPokemon(deffender_conditions, deffender, getFirstDebuff(deffender_debuffs));

        turn++;
        free(pokemon_attacks);
        if(run_away || captured) break;
    }while(getPokemonActualHP(cpu_pokemon) > 0 && getPokemonActualHP(player_pokemon) > 0);
    
    
    for(i = 0; i < 7; i++)
    {
        battle_stage->cpu_conditions[i] = cpu_conditions[i];
        battle_stage->player_conditions[i] = player_conditions[i];
    }
    
    free(cpu_conditions);
    free(player_conditions);
    freeAttacks(attacks, attacksQuantity);
    freeDebuffsList(getFirstDebuff(player_debuffs));
    freeDebuffsList(getFirstDebuff(cpu_debuffs));

    if(getPokemonActualHP(player_pokemon) <= 0) return 0;

    if(getPokemonActualHP(cpu_pokemon) <= 0)
    {
        new_game->won_battles++;
        new_game->last_pokeball++;

        if(calcRandomThings((float) new_game->last_pokeball / 12)) {
            new_game->player_pokeballs++;
            new_game->last_pokeball = 0;
        }

        if(getPokemonActualHP(player_pokemon) < getPokemonHP(player_pokemon)){
            setPokemonActualHP(player_pokemon, getPokemonActualHP(player_pokemon) + 0.1 * getPokemonHP(player_pokemon));
            if(getPokemonActualHP(player_pokemon) > getPokemonHP(player_pokemon)) {
                setPokemonActualHP(player_pokemon, getPokemonHP(player_pokemon));
            }
        }
        return 1;
    }
    
    if(captured) return 2;
    
    if(run_away) return 3;
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

void freeBattleLog(BattleLog * log)
{
    BattleLog * actual_cell;

    actual_cell = log;

    do{
        log = actual_cell;

        actual_cell = actual_cell->next;
        free(log->battle);
        free(log);
    }while(actual_cell != NULL);

}

void freeGame(Game * new_game)
{
    freeBattleLog(new_game->battle_log->first);
    free(new_game);
}