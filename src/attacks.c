#include "attacks.h"

struct Attack {
    char *name;
    int is_damage_dealer;   // boolean
    int power;
    int is_MT;              // boolean
};