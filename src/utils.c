#include "utils.h"

char * getUserName()
{
    int is_valid_name = 1, name_size = 10, count = 0;
    char temp;
    char *name;

    name = (char* ) calloc(name_size, sizeof(char));
    do 
    {  
        count = 0;
        name_size = 10;
        if(!is_valid_name){
            free(name);
            name = (char* ) calloc(name_size, sizeof(char));
            printf("Digite um nome valido: ");
        }

        is_valid_name = 1;

        while((temp = getchar()) != '\n') 
        {
            if(!isalpha(temp)) {
                if(temp != '_') is_valid_name = 0;
            }
            
            if(count == name_size - 1) 
            {
                name_size *= 2;
                name = (char* ) realloc(name, name_size * sizeof(char));
            }
            name[count] = temp;
            name[count + 1] = '\0';

            if(count >= 128) is_valid_name = 0;
            count++;
        }
        if(count == 0) is_valid_name = 0;
    } while(!is_valid_name);

    return name;
}

int getUserNumberInput(int min, int max)
{
    int option, valid_option = 1;

    do
    {
        if(!valid_option)
        {
            printf("Digite uma entrada valida: ");
            valid_option = 1;
        }
        while(scanf("%d", &option) != 1)
        {
            while(getchar() != '\n'){};
            printf("Digite uma entrada valida: ");
        }
        while(getchar() != '\n')
        {
            valid_option = 0;
        }

        if(option < min || option > max)
        {
            valid_option = 0;
        }
    } while (!valid_option);
    
    return option;
}

char *toUpperString(char *string) {
    int i;
    char * uppercased;

    uppercased = (char* ) calloc(strlen(string) + 1, sizeof(char));

    for(i = 0; i < strlen(string); i++) {
        if(!isupper(string[i])) 
        {
            uppercased[i] = toupper(string[i]);
        }
        else
        {
            uppercased[i] = string[i];
        }
    }

    uppercased[strlen(string)] = '\0';

    return uppercased;
}