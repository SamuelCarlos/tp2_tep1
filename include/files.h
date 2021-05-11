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
 * @brief Receives a pointer to the scores tree root and a pointer to "placares.txt" file and print in order on the file;
 * @param node: pointer to the tree root;
 * @param file: file where the tree will be printed;
 */
void printInorder(Scores* node, FILE * file);

/**
 * @brief Receives a pointer to the individual scores tree root and a pointer to "placares.txt" file and print the name on the file;
 * @param node: pointer to the tree root;
 * @param file: file where the tree will be printed;
 */
void printNameInorder(IndividualScore * node, FILE * file, int score);

/**
 * @brief free a pointer scores;
 * @param node: pointer to the tree root;
 */
void freeScores(Scores * node);

/**
 * @brief free a pointer individual scores;
 * @param node: pointer to the tree root;
 */
void freeIndividualScore(IndividualScore * node);

/**
 * @brief open a file and save all scores read from the file in a list of scores;
 * @param fileDir: the directory of the file to be read;
 * @return a list of all scores read from the file;
 */
Scores * readScoresFile(char * fileDir);

/**
 * @brief Receives a pointer to the scores tree root and a pointer to the directory of a file. Open the file and print the tree on the file;
 * @param fileDir: the directory of a file where the tree will be printed;
 * @param node: pointer to the tree root;
 */
void writeScoresOnFile(char * fileDir, Scores * score);

/**
 * @brief Receives a pointer to the scores tree root and print in order on the screen;
 * @param node: pointer to the tree root;
 * @param file: file where the tree will be printed;
 */
void printScoreTree(Scores *node);

/**
 * @brief Receives a pointer to the individual scores tree root and print the name on the screen;
 * @param node: pointer to the tree root;
 * @param score: player score;
 */
void printScoreboardName(IndividualScore * node, int score);

#endif