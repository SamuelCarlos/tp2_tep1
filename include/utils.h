#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char * getUserName();

int getUserNumberInput(int min, int max);

char *toUpperString(char *string);

#endif // UTILS_H