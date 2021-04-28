#include "menu.h"
#include "../include/utils.h"
#include "../include/player.h"
#include "../include/pokemon.h"
#include "../include/attacks.h"

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
    PokemonsList *pokemons;
    Attack **attacks;
    Player *player;
    char *name;
    int pokemonsQuantity = 0,attacksQuantity = 0, i;
    int user_pokemons[3] = {-1, -1, -1};

    printf("Digite seu nome: ");

    pokemons = readPokemons(&pokemonsQuantity);
    attacks = readAttacks(&attacksQuantity);

    player = allocPlayer();

    name = getUserName();

    printPokemonList(pokemons);

    removePokemonFromList(pokemons, 3);

    printPokemonList(pokemons);

    // for(i = 0; i < 3; i++)
    // {
    //     user_pokemons[i] = userPokemonChoose(pokemons, pokemonsQuantity, user_pokemons) - 1;
    // }

    free(name);
    freePlayer(player);
    freeGameData(attacks, attacksQuantity);
    freePokemonList(pokemons);
    free(attacks);
}

void freeGameData(Attack **attacks, int attacksQuantity)
{
    int i = 0;
    do{
        //if(attacks[i] == NULL) break;
        freeAttack(attacks[i]);
        i++;
    }while(i <= attacksQuantity);
}

int userPokemonChoose(Pokemon ** pokemons, int pokemonsQuantity, int * user_pokemons)
{
    int i, j, is_equal, valid_option = 1, option;

    printf("Escolha um dos pokemons abaixo:\n");

    for(i = 0; i < pokemonsQuantity; i++)
    {   
        is_equal = 0;
        for(j = 0; j < 3; j++)
        {
            if(user_pokemons[j] == i) is_equal = 1;
        }
        if(!is_equal)
        {
            printf("%d - ", i + 1);
            printPokemon(pokemons[i]);
        }
    }

    do
    {
        if(!valid_option)
        {
            printf("Digite uma opcao valida!\n");
        }
        valid_option = 1;

        while(scanf("%d", &option) != 1) 
        {
            while(getchar() != '\n'){};
            printf("Digite uma entrada valida: ");
        }
        while(getchar() != '\n') 
        {
            valid_option = 0;
        }

        if(option < 1 || option > pokemonsQuantity)
        {
            valid_option = 0;
        }
        else
        {
            for(i = 0; i < 3; i++)
            {
                if(user_pokemons[i] == option)
                {
                    valid_option = 0;
                }
            }
        } 
    
    }while(!valid_option);

    return option;
}