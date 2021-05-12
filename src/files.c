#include "../include/files.h"
#include <string.h>

struct IndividualScore {
    char * name;
    IndividualScore * left;
    IndividualScore * right;
};

struct Scores {
    IndividualScore * firstScore;
    int score;
    Scores * left;
    Scores * right;
};

Scores * createNewScoresNode(Scores * first_node, int score, char * name, int * pos)
{   
    Scores * node = first_node;
    Scores * previous = NULL;
    IndividualScore * individualNode = NULL;
    IndividualScore * previousIndividualNode = NULL;
    IndividualScore * temp = NULL;
    int rightOrLeft = 0;
    int position = 0;
    char * uppercasedName = NULL;
    char * uppercasedNameAtTree = NULL;

    if (first_node == NULL) 
    {
        position++;
        first_node = (Scores*) calloc(1, sizeof(Scores));
        first_node->score = score;
        first_node->left = NULL;
        first_node->right = NULL;
        first_node->firstScore = (IndividualScore*) calloc(1, sizeof(IndividualScore));
        first_node->firstScore->name = strdup(name);
        first_node->firstScore->left = NULL;
        first_node->firstScore->right = NULL;
    }
    else
    {
        do
        {
            previous = node;
            if(score < node->score)
            {
                rightOrLeft = -1;
                node = node->left;
                temp = previous->firstScore;
                countEqualPoints(temp, &position);
            }
            else if(score > node->score)
            {
                rightOrLeft = 1;
                node = node->right;
            }else{
                rightOrLeft = 0;
                break;
            }
            
        }while(node != NULL);

        if(rightOrLeft != 0) 
        {
            position++;
            node = (Scores*) calloc(1, sizeof(Scores));
            if(rightOrLeft == 1)
            {
                previous->right = node;
            }else{
                previous->left = node;
            }
            node->score = score;
            node->left = NULL;
            node->right = NULL;
            node->firstScore = (IndividualScore*) calloc(1, sizeof(IndividualScore));
            node->firstScore->name = strdup(name);
            node->firstScore->left = NULL;
            node->firstScore->right = NULL;
        }
        else
        {
            individualNode = node->firstScore;
            do
            {
                previousIndividualNode = individualNode;
                uppercasedName = toUpperString(name);
                uppercasedNameAtTree = toUpperString(individualNode->name);

                if(strcmp(uppercasedName, uppercasedNameAtTree) < 0)
                {
                    individualNode = individualNode->left;
                    rightOrLeft = 0;
                     
                }
                else if(strcmp(uppercasedName, uppercasedNameAtTree) >= 0)
                {
                    individualNode = individualNode->right;
                    rightOrLeft = 1;
                    position++;
                }

                free(uppercasedName);
                free(uppercasedNameAtTree);
            }while(individualNode != NULL);

            individualNode = (IndividualScore*) calloc(1, sizeof(IndividualScore));
            if(rightOrLeft) {
                previousIndividualNode->right = individualNode;
            }else{
                previousIndividualNode->left = individualNode;
            }
            position++;
            individualNode->name = strdup(name);
            individualNode->left = NULL;
            individualNode->right = NULL;
        }
    }
    *pos = position;
    return first_node;
}

void countEqualPoints(IndividualScore * node, int * qnt)
{
    if (node == NULL) return;
    
    countEqualPoints(node->left, qnt);

    *qnt = *qnt + 1; 

    countEqualPoints(node->right, qnt);
}

void printInorder(Scores* node, FILE * file)
{
    if (node == NULL) return;
 
    printInorder(node->right, file);
    
    IndividualScore * first_node = node->firstScore;
    printNameInorder(first_node, file, node->score);
    
    printInorder(node->left, file);
}
 
void printNameInorder(IndividualScore * node, FILE * file, int score)
{
    if (node == NULL) return;
    
    printNameInorder(node->left, file, score);

    fprintf(file, "%s %d\n", node->name, score);
 
    printNameInorder(node->right, file, score);
}

void freeScores(Scores * node)
{
    Scores * temp;
    if (node == NULL) return;
 
    
    freeScores(node->left);
 
    freeIndividualScore(node->firstScore);
    temp = node->right;
    free(node);
 
    freeScores(temp);
}

void freeIndividualScore(IndividualScore * node)
{
    if (node == NULL) return;
    IndividualScore * temp;
    
    freeIndividualScore(node->left);
 
    free(node->name);
    temp = node->right;
    free(node);

    freeIndividualScore(temp);
}

Scores * readScoresFile(char * fileDir)
{
    FILE * file;
    Scores * scores_list = NULL;
    char *pointer, *pointer2, *token;
    char **row;
    size_t bufsize;
    size_t characters;
    int position, array_parser, i;

    file = fopen(fileDir, "r");
    if(file == NULL)
    {
        return NULL;
    }

    do{
        bufsize = 32;
        array_parser = 0;

        pointer = (char *) calloc(bufsize, sizeof(char));

        characters = getline(&pointer, &bufsize, file);
        if(characters == -1)
        {
            free(pointer);
            break;
        }
        pointer[characters] = '\0';

        pointer2 = pointer;

        row = (char **) calloc(3, sizeof(char*));

        token = strtok_r(pointer, " ", &pointer);
        row[array_parser] = token;
        array_parser++;

        token = strtok_r(NULL, "\0", &pointer);
        row[array_parser] = token;

        scores_list = createNewScoresNode(scores_list, atoi(row[1]), row[0], &position);
    
        free(row);
        free(pointer2);
    }while(1);

    fclose(file);

    return scores_list;
}

void writeScoresOnFile(char * fileDir, Scores * score)
{
    FILE * file;

    file = fopen(fileDir, "w");

    printInorder(score, file);

    fclose(file);
}

void printScoreTree(Scores *node)
{
    if (node == NULL) return;
    
    printScoreTree(node->right);
    
    IndividualScore * aux = node->firstScore;
    printScoreboardName(node->firstScore, node->score);
 
    printScoreTree(node->left);
}

void printScoreboardName(IndividualScore * node, int score)
{
    if (node == NULL) return;

    printScoreboardName(node->left, score);
 
    printf("%s %d\n", node->name, score);
 
    printScoreboardName(node->right, score);
}