#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Menu.h"
#include "../Functions/SharedMacros.h"
#include "../Functions/GeneralFunctions.h"
#include "../Decrypt/Decrypt.h"

static int check_string(char[], int);

void run_DecryptMenu()
{
    while(1)
    {
        char input[MAX_KEYWORD_LENGTH + 1];

        printf("\n\n\n===========================DECRYPTION================================\n"
               "DECRYPTION:\n"
               "Enter the KEYWORD\n"
               "or type [;] to load it from Memory\n"
               "or type [-] to return to the Main Menu\n"
               "KEYWORD Max LENGTH is 20 Characters\n>> ");
        scanf("%s", input);

        if(input[0] == ';')
            strcpy(input, Session.keyword);
        else if(input[0] == '-')
            return;

        //error check that the string is completely letters of the alphabet and lower case any uppercase letters:
        else if(check_string(input, MAX_KEYWORD_LENGTH) == -1)
            continue;

        printf("--------------------via KEYWORD: < %s >---------------------\n", input);
        decrypt_file(input, 1);
        input_pause();
    }
}


static int check_string(char array[], int length)
{
    int i;

    for(i = 0; i < length && array[i] != '\0'; i++)
    {
        if(!isalpha(array[i]))
        {
            error(INCORRECT_INPUT, NULL);
            return -1;
        }
        array[i] = tolower(array[i]);
    }
    return 1;
}
