// pokemon
typedef struct pokemon {
    char *name;
    int hp;
    int atk;
    int def;
    int type;
    Attack attacks[3];
} Pokemon;

// actual player
typedef struct player {
    char *name;
    int active_pokemons;
    int pokeballs;
    Pokemon first_pokemon;
} Player;


typedef struct attack {
    char *name;
    int is_damage_dealer; // boolean
    int power;
    int is_MT;
} Attack;

typedef struct effect {
    char *name;
    int turns_left;
} Effect;

// carregar na memoria os dados dos pokemons do player
// assim que ele escolhe-los no menu;

// carregar também apenas os pokemons referentes a batalha atual
// assim como os ataques referentes a batalha atual;

/**
 *  Effects:
 *  Heal
 *  Burn
 *  Sleep
 *  Damage
 *  Defense
 *  Suicide
 *  Paralize
 *  Self Damage 
 *  Delayed Damage
 */