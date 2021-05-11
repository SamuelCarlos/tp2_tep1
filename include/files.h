#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"

typedef struct IndividualScore IndividualScore;

typedef struct Scores Scores;

Scores * createNewScoresNode(Scores * first_node, int score, char * name, int * position);

void countEqualPoints(IndividualScore * node, int * qnt);

void printInorder(Scores* node, FILE * file);

void printNameInorder(IndividualScore * node, FILE * file, int score);

void freeScores(Scores * node);

void freeIndividualScore(IndividualScore * node);

Scores * readScoresFile(char * fileDir);

void writeScoresOnFile(char * fileDir, Scores * score);

void printScoreTree(Scores *node);

void printScoreboardName(IndividualScore * node, int score);

#endif