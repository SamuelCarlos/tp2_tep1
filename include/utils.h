#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief read a string from user;
 * @return pointer to the string;
 */
char * getUserName();

/**
 * @brief get a number input from user from min to max;
 * @param min: min acceptable range;
 * @param max: max acceptable range;
 * @return integer user have input;
 */
int getUserNumberInput(int min, int max);

/**
 * @brief transforms an string to UPPERCASE;
 * @param string to be uppercased;
 * @return pointer to the string;
 */
char *toUpperString(char *string);

#endif // UTILS_H