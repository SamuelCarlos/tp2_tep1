#include <stdio.h>
#include <time.h>
#include "menu.h"



int main (int argc, char *argv[])
{
    int seed;
    char * scoresLocation = argv[1];
    char * logsLocation = argv[2];
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