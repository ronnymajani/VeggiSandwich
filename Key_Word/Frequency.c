#include "../Functions/SharedMacros.h"
#include "../Functions/DataFunctions.h"
#include "../Functions/GeneralFunctions.h"
#include "Frequency.h"
#include "Ceaser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


void run_FrequencyMenu()
{
    char input;
    int keylength;
    fflush(stdin);

    while(1)
    {
        puts("\n\n\n===================FREQUENCY ANALYSIS====================\n");
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
                frequency_analysis(keylength);
                break;
            case '1':
                printf("\nEnter Keyword Length:  ");
                scanf("%d", &keylength);
                frequency_analysis(keylength);
                break;
            default:
                error((AppError = INCORRECT_INPUT), NULL);
                break;
        }
        fflush(stdin);
    }
}





void frequency_analysis(int length)
{//calculates frequency of letters
    //each letters repetition is stored in its corresponding index in the array.
    //Unknown characters are stored in the last index
    register int j, k;
    int repetition[length][27];
    float frequencies[length][26];
    long int totalSum;


    //totalSum of letters:
    totalSum = letter_count();

    //letter frequencies:
    file_letter_frequencies(repetition, length);

    //calculate permutations of the letters:
    for(j = 0; j < length; j++)
        for(k = 0; k < 26; k++)
            frequencies[j][k] = (float)(repetition[j][k])*100/totalSum;


    //print these to screen:
    for(j = 0; j < length; j++)
    {
        printf("\n[Offset = %d]\n", j+1);
        for(k = 0; k < 26; k++)
        {
            printf("%c: %f\t", k + 'a', frequencies[j][k]);
        }
        printf("\nUNKNOWN: %d\n", repetition[j][26]);
        puts("----------------");
    }
    input_pause();
}



void file_letter_frequencies( int empty_array[][27], int length)
{
    FILE *file;
    register int i;
    //opening file:
    open_encryptedfile();
    file = Session.openencryptedfile;
    //fill array with zeros:
    for(i=0;i<length;i++)
        fill_array_with(empty_array[i], 0, 27);

    //collecting letter repetitions:
    for(i = 0; i < length; i++)
    {
        char c;
        fseek(file, i, SEEK_SET);
        while((c = fgetc(file)) != EOF)
        {
            c = c - 'a';
            if(c < 26 && c >= 0)
                empty_array[i][(int)c]++;
            else
                empty_array[i][26]++;
            fseek(file, length-1, SEEK_CUR);
        }
    }
    //close all the files:
    fclose(file);
}



void letter_permutations(double empty_array[26], char partial_array[], int text_length)
{
    register int i, totalSum;

    totalSum = 0;

    fill_doublearray_with(empty_array, 0, 26);

    for(i = 0; i < text_length; i++)
    {
        int c = partial_array[i] - 'a';
        if(c < 26 && c > 0)
        {
            empty_array[c]++;
            totalSum++;
        }
    }

    //calculate permutations of the letters:
    for(i = 0; i < 26; i++)
        empty_array[i] = (double)((empty_array[i])*100/totalSum);
}

void scale_frequencies(double frequencies[26])
{
    register int i;
    double scaleFactor;

    scaleFactor = (double)(English_Max_Frequency / frequencies[maximum_double(frequencies, 26)]);
    for(i = 0; i < 26; i++)
        frequencies[i] *= scaleFactor;
}


double sum_residual_error(double scaled_frequencies[26])
{
    register int i;
    double ErrorSum;
    double English_Frequencies[] =
    {8.167, 1.492, 2.782, 4.253, 12.702,
    2.228, 2.015, 6.094, 6.996, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507,
    1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074};
    ErrorSum = 0;

    for(i = 0; i < 26; i++)
        ErrorSum += pow((scaled_frequencies[i] - English_Frequencies[i]), 2);

    return ErrorSum;
}


int letter_count()
{
    FILE *file;
    char c;
    int count = 0;
    //opening file:
    open_encryptedfile();
    file = Session.openencryptedfile;

    //count letters:
    while((c = fgetc(file)) != EOF)
        if(isalpha(c))
            count++;

    //closing file:
    fclose(file);

    //return count:
    Session.letterCount = count;
    return count;
}
