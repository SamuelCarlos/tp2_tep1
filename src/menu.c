#include "menu.h"
#include "../include/utils.h"
#include "../include/battle.h"
#include "../include/player.h"
#include "../include/pokemon.h"
#include "../include/attacks.h"

void mainMenu()
{
    int option, is_valid_option = 1, ending = 0;
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
        
        trash = system("clear");

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
    FILE * log;
    Game * new_game;
    Player *player;
    Pokemon * cpu_pokemon;
    PokemonsList *pokemons, *user_pokemons = NULL, *last_user_pokemon = NULL;
    char *name;
    char trash;
    int battle_result, player_defeated = 0, random_pokemon;
    int pokemonsQuantity = 0, i, player_choice, player_score = 0;

    printf("Digite seu nome: ");

    pokemons = readPokemons(&pokemonsQuantity);

    player = allocPlayer();

    name = getUserName();

    trash = system("clear");

    user_pokemons = addPokemonOnList(user_pokemons);
    last_user_pokemon = user_pokemons;

    for(i = 0; i < 3; i++)
    {
        if(i > 0) {
            last_user_pokemon = addPokemonOnList(last_user_pokemon);
        }
        printPokemonList(pokemons);
        player_choice = getUserNumberInput(1, pokemonsQuantity - i);
        last_user_pokemon = attributePokemonToCell(last_user_pokemon, readPokemonFromList(pokemons, player_choice));
        pokemons = removePokemonFromList(pokemons, player_choice - 1);
        trash = system("clear");
    }
    // reset pokemons list
    freePokemonList(pokemons);
    pokemonsQuantity = 0;
    pokemons = readPokemons(&pokemonsQuantity);

    new_game = newGame(new_game);

    random_pokemon = randomPokemonNumber(new_game, pokemonsQuantity);

    cpu_pokemon = createPokemon(cpu_pokemon);
    cpu_pokemon = copyPokemon(cpu_pokemon, readPokemonFromList(pokemons, random_pokemon));


    do {
        trash = system("clear");
        battle_result = battle(readPokemonFromList(user_pokemons, 0), cpu_pokemon, new_game);

        switch (battle_result)
        {
            case 3: 
                freePokemon(cpu_pokemon);
                cpu_pokemon = createPokemon(cpu_pokemon);
                random_pokemon = randomPokemonNumber(new_game, pokemonsQuantity);
                cpu_pokemon = copyPokemon(cpu_pokemon, readPokemonFromList(pokemons, random_pokemon));
                break;
            case 2:
                last_user_pokemon = addPokemonOnList(last_user_pokemon);
                last_user_pokemon = attributePokemonToCell(last_user_pokemon, readPokemonFromList(pokemons, random_pokemon));
                freePokemon(cpu_pokemon);
                cpu_pokemon = createPokemon(cpu_pokemon);
                random_pokemon = randomPokemonNumber(new_game, pokemonsQuantity);
                cpu_pokemon = copyPokemon(cpu_pokemon, readPokemonFromList(pokemons, random_pokemon));
                player_score++;
                break;
            case 1:
                freePokemon(cpu_pokemon);
                cpu_pokemon = createPokemon(cpu_pokemon);
                random_pokemon = randomPokemonNumber(new_game, pokemonsQuantity);
                cpu_pokemon = copyPokemon(cpu_pokemon, readPokemonFromList(pokemons, random_pokemon));
                player_score++;
                break;
            case 0:
                user_pokemons = removePokemonFromList(user_pokemons, 0);
                if(user_pokemons == NULL) player_defeated = 1;
                break;
            default:
                break;
        }
    }while(!player_defeated);

    printf("Fim de jogo!\n");
    printf("%s sobreviveu %d rodadas e esta em %d° lugar no placar!\n", name, player_score, 3);

    freePokemon(cpu_pokemon);
    free(name);
    freePlayer(player);
    freePokemonList(pokemons);
    freeGame(new_game);
}

int randomPokemonNumber(Game* new_game, int pokemon_quantity)
{
    float random = (float)rand()/(float)(RAND_MAX);

    int lastMew = getGameLastMew(new_game);

    if(random <= (float)(lastMew/128)){
        setGameLastMew(new_game, 0);
        return pokemon_quantity - 1;
    }
    else{
        setGameLastMew(new_game, lastMew + 1);
        return (int) (1 + rand() % (pokemon_quantity - 1));
    }
}