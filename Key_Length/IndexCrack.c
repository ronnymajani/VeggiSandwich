#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "IndexCrack.h"
#include "../Functions/DataFunctions.h"
#include "../Functions/SharedMacros.h"
#include "../Functions/GeneralFunctions.h"


static char *rotate_text(int rotation)
{
    register int i, j, len;
    char *rotated;
    char *original;

    if(Session.encrypted_text == NULL)
        original = load_into_array();
    else
        original = Session.encrypted_text;

    len = strlen(original);
    rotated = (char *)malloc(len * sizeof(char) + 1);
    if(rotated == NULL)
        error((AppError = MALLOC_FAIL), "load_into_array");

    for(i = 0, j = rotation; i < len; i++, j = ((j + 1) % len))
        rotated[j] = original[i];

    rotated[i] = '\0';

    if(strlen(original) != strlen(rotated))
        error((AppError = CUSTOM_EXIT), "FUNCTION < rotate_text >, strlen of rotated text != strlen of original text");

    return rotated;
}



int IndexCrack()
{//Finds the KeyLength by comparing the index of Coincidence of rotated version of the text
    //the range of these calculations is [0, MAX_KEYWORD_LENGTH]

    register int i, j;
    double IOC_list[MAX_KEYWORD_LENGTH];
    double smallestSquaredDiff;
    int keylength;
    char *original;
    int len;

    original = load_into_array();
    len = strlen(original);
    keylength = 0;

    for(i = 1; i < MAX_KEYWORD_LENGTH; i++)
    {
        double coincidence = 0;
        char *rotated = rotate_text(i);

        for(j = 0; j < len; j++)
            if(rotated[j] == original[j])
                coincidence++;

        IOC_list[i-1] = (coincidence / len);
    }

    smallestSquaredDiff = pow((IOC_list[0] - English_Kappa), 2);

    for(i = 1; i < MAX_KEYWORD_LENGTH; i++)
    {
        double SquaredDiff = pow((IOC_list[i-1] - English_Kappa), 2);

        /*printf("Len: %d\n"
               "IOC: %f\n"
               "Diff: %f\n"
               "SquaredDiff: %f\n", i, IOC_list[i-1], (IOC_list[i] - English_Kappa), SquaredDiff);*///#DEBUG
        if(SquaredDiff < smallestSquaredDiff)
        {
            smallestSquaredDiff = SquaredDiff;
            keylength = i;
        }
    }

    Session.keylength = keylength;
    return keylength;
}
