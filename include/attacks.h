#ifndef ATTACKS_H
#define ATTACKS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Attack Attack;

void freeAttack(Attack *attack);

Attack ** readAttacks();

#endif // ATTACKS_H