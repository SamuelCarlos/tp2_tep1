#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"

typedef struct IndividualScore IndividualScore;

typedef struct Scores Scores;

/**
 * @brief Receives a pointer to the tree root and creates a new ramification to add a new player, inside each tree node we have another tree to order by name;
 * @param first_node: pointer to the tree root;
 * @param score: player score to add it on the tree;
 * @param name: player name to add it on the tree;
 * @param position: pointer to int who tells the actual player position on score;
 * @return pointer to the first node of the tree;
 */
Scores * createNewScoresNode(Scores * first_node, int score, char * name, int * position);

/**
 * @brief Receives a pointer to the names tree root and count how many nodes it have;
 * @param node: pointer to the tree root;
 * @param qnt: pointer to increment at each position of tree;
 */
void countEqualPoints(IndividualScore * node, int * qnt);

/**
 * @brief Receives a pointer to the scores tree root and a pointer to "placares.txt" file;
 * @param node: pointer to the tree root;
 * @param qnt: pointer to increment at each position of tree;
 */
void printInorder(Scores* node, FILE * file);

void printNameInorder(IndividualScore * node, FILE * file, int score);

void freeScores(Scores * node);

void freeIndividualScore(IndividualScore * node);

Scores * readScoresFile(char * fileDir);

void writeScoresOnFile(char * fileDir, Scores * score);

void printScoreTree(Scores *node);

void printScoreboardName(IndividualScore * node, int score);

#endif