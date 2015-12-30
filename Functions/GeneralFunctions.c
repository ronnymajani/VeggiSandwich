#include "GeneralFunctions.h"
#include "SharedMacros.h"
#include "DataFunctions.h"
#include <stdio.h>
#include <stdlib.h>

void error(errorE error_type, void *description)
{
    printf("\n!========================!\n{!} ");
    switch(error_type)
    {
        case CUSTOM_EXIT:
            printf("%s", (char*)description);
            exit(-11);
            break;
        case CUSTOM:
            printf("%s", (char*)description);
            break;
        case INCORRECT_INPUT:
            puts("INCORRECT INPUT, Please read carefully and try again");
            break;
        case FOPEN_OPEN_FAIL:
            printf("FAILED to OPEN File [ %s ]", (char*)description);
            break;
        case FOPEN_CREATE_FAIL:
            printf("FAILED to CREATE the File [ %s ]\n"
                   "Cannot continue processing\n"
                   "Exiting Application...", (char*)description);
            ExitApp(-2);
            break;
        case FOPEN_READ_FAIL:
            printf("ERROR READING < %s >", (char*)description);
            break;
        case MALLOC_FAIL:
            printf("FAILED ALLOCATING MEMORY IN FUNCTION < %s >", (char*)description);
            ExitApp(-3);
            break;
        default:
            puts("UNKNOWN ERROR\nExiting the application...");
            ExitApp(-1);
    }
    printf(" {!}\n!========================!\n\n");
}

void ExitApp(int status)
{
    save_datafile(&Session);
    fclose(Session.openfile);
    fclose(Session.openencryptedfile);
    free(Session.decrypted_text);
    free(Session.encrypted_text);
    exit(status);
}

void input_pause()
{
    //scanf("%*c\n");
    fflush(stdin);
    printf("...");
    getchar();
    fflush(stdin);
}


void fill_array_with( int arr[], const int value, const int arrLength)
{
    register int i;
    for(i = 0;  i < arrLength; i++)
        arr[i] = value;
}

void fill_doublearray_with(double arr[], const double value, const int arrLength)
{
    register int i;
    for(i = 0;  i < arrLength; i++)
        arr[i] = value;
}


int maximum_int(int arr[], int arrLength)
{
    register int i, max, index;
    max = 0;
    index = 0;
    for(i = 0; i < arrLength; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
            index = i;
        }
    }
    return index;

}

int maximum_double(double arr[], int arrLength)
{
    register int i, index;
    register double max;
    max = 0;
    index = 0;
    for(i = 0; i < arrLength; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
            index = i;
        }
    }
    return index;

}
