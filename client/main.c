#include <stdio.h>
#include <time.h>
#include "menu.h"

int main (int argc, char *argv[])
{
    int seed = 1;
    char * scoresLocation = argv[1];
    char * logsLocation = argv[2];
    
    printf("argv1: %s, argv2: %s\n", argv[1], argv[2]);
    if(argc < 2)
    {
        printf("Faltam argumentos.\n");
    }
    if(argv[3])
    {
        seed = atoi(argv[3]);
    }else{
        seed = time(NULL);
    }
    srand(seed);
    mainMenu(scoresLocation, logsLocation);

    return 0;
}