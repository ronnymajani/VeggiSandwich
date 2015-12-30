#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../Functions/SharedMacros.h"
#include "../Functions/GeneralFunctions.h"
#include "../Functions/DataFunctions.h"
#include "Frequency.h"
#include "Ceaser.h"


void run_CeaserMenu()
{
    char input;
    int keylength;
    fflush(stdin);

    while(1)
    {
        puts("\n\n\n===================KEYWORD CRACK====================\n");
        printf("[1] Manually Enter Keyword Length\n"
               "[;] Use Saved KeyLength < %d >\n"
               "[-] Return to Previous Menu\n>>  ", Session.keylength);
        scanf("%c", &input);

        switch(input)
        {
            case '-':
                return;
            case ';':
                keylength = Session.keylength;
                CeaserCrack(Session.keyword, keylength);
                break;
            case '1':
                printf("\nEnter Keyword Length:  ");
                scanf("%d", &keylength);
                CeaserCrack(Session.keyword, keylength);
                break;
            default:
                error((AppError = INCORRECT_INPUT), NULL);
                break;
        }
        fflush(stdin);
    }
}




static void encipher(char text[], char key, int len)
{
    register int i;
    char *encrypted;

    encrypted = (char*)malloc(len * sizeof(char) + 1);
    if(encrypted == NULL)
        error((AppError = MALLOC_FAIL), "[static] encipher()");

    for(i = 0; i < len; i++)
        text[i] = 'a' + (((text[i] - 'a') + (key - 'a')) % 26);
}


static char *partial_array(char *array, int offset, int stepSize, int arrayLength)
{
    register int i, j;
    char *part;

    part = (char*)malloc(arrayLength * sizeof(char) + 1);
    if(part == NULL)
        error((AppError = MALLOC_FAIL), "[static] partial_array()");

    for(i = offset, j = 0; i < arrayLength; i += stepSize)
        part[j++] = array[i];

    part[j] = '\0';

    return part;
}


void CeaserCrack(char emptyKeyword[], int KeyLength)
{
    register int j, k, len;
    char input;
    char *text;

    text = load_into_array();
    len = strlen(text);

    for(j = 0; j < KeyLength; j++)
    {
        double smallestError = -1;
        int bestKey = 0;
        for(k = 0; k < 26; k++)
        {
            double frequencies[26];
            char *tempPart = partial_array(text, j, KeyLength, len);
            int tempLen = strlen(tempPart);
            double currentError;
            char currentKey = ('a' + (26 - k));
            if(k == 0)
                currentKey = 'a';

            encipher(tempPart, currentKey, tempLen);
            letter_permutations(frequencies, tempPart, tempLen);
            scale_frequencies(frequencies);
            currentError = sum_residual_error(frequencies);

            if(smallestError == -1)
                smallestError = currentError;
            else
                if(currentError < smallestError)
                {
                    smallestError = currentError;
                    bestKey = k;
                }
        }
        emptyKeyword[j] = bestKey + 'a';
    }
    emptyKeyword[j] = '\0';

    printf("Predicted Key: <   ");
    for(k = 0; k < j; k++)
        printf("%c  ", toupper(emptyKeyword[k]));
    puts("  >\n\n");

    //prompt user to save key:
    fflush(stdin);
    while(1)
    {
        printf("[1] SAVE the predicted KEY < %s >\n"
               "[2] Discard the predicted KEY and return to Previous Menu\n>>  ", emptyKeyword);
        scanf("%c", &input);

        switch(input)
        {
            case '1':
                strcpy(Session.keyword, emptyKeyword);
                save_datafile();
                puts("SUCCESS | SAVED PREDICTED KEY");
                input_pause();
                return;
                break;
            case '2':
                puts("\n{!} DATA DISCARDED {!}");
                input_pause();
                return;
                break;
            default:
                error((AppError = INCORRECT_INPUT), NULL);
                break;
        }
        fflush(stdin);
    }
}
