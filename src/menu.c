#include "menu.h"

void mainMenu()
{
    int option, is_valid_option, ending = 0;
    char trash;

    do 
    {
        printf("1. Jogar\n2. Melhores pontuacoes\n3. Sair\n");

        do
        {
            if(!is_valid_option) printf("Digite uma entrada valida: ");
            is_valid_option = 1;

            while(scanf("%d", &option) != 1) 
            {
                while(getchar() != '\n'){};
                printf("Digite uma entrada valida: ");
            }
            while(getchar() != '\n') 
            {
                is_valid_option = 0;
            }

            if(option < 1 || option > 3) is_valid_option = 0; 

        }while(!is_valid_option);
        
        // trash = system("clear");

        switch (option)
        {
        case 1:
            playGame();
            break;
        case 2:
            printf("DOIS\n");
            break;
        case 3:
            printf("TRES\n");
            ending = 1;
            break;
        default:
            break;
        }
    } while (!ending);
}

void playGame()
{
    Pokemon **pokemons;
    Attack **attacks;
    Player *player;
    char *name;

    printf("Digite seu nome: ");

    pokemons = readPokemons();
    attacks = readAttacks();

    player = allocPlayer();

    name = getUserName();
    
    free(name);
    freePlayer(player);

    freeGameData(pokemons, attacks);
    free(pokemons);
    free(attacks);
}

void freeGameData(Pokemon **pokemons, Attack **attacks)
{
    int i = 0;
    do{
        if(pokemons[i] == NULL) break;
        freePokemon(pokemons[i]);
        i++;
    }while(1);
    i = 0;
    do{
        if(attacks[i] == NULL) break;
        freeAttack(attacks[i]);
        i++;
    }while(1);
}