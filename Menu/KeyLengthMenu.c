#include "../Key_Length/Friedman.h"
#include "../Functions/GeneralFunctions.h"
#include "../Key_Word/Frequency.h"
#include "../Key_Length/IndexCrack.h"
#include "Menu.h"
#include <stdio.h>

void run_KeyLengthMenu()
{
    char input;
    double result;
    //#POINTLESS:
    /*
    register int i;
    int totalFrequency;
    int frequencies[1][27];
    */

    fflush(stdin);

    while(1)
    {
        puts("\n\n\n====================KEYLENGTH FINDER======================\n");
        printf("Select a Tool:\n"
               "[1] Friedman Test\n"
               "[2] Index of Coincidence Test\n"
               "[3] Calculate Index of Coincidence\n"
               "[4] Show All Info\n"
               "[-] Return to Main Menu\n"
               ">>  ");
        scanf("%c", &input);

        switch(input)
        {
            case '1':
                result = friedman_test();
                printf("Keyword Length based on the Friedman Test is around: < %f >\n", result);
                input_pause();
                break;
            case '2':
                result = IndexCrack();
                printf("Keyword Length based on the Index of Coincidence Test is: < %d >\n", (int)result);
                input_pause();
                break;
            case '3':
                result = index_of_coincidence();
                printf("Index of Coincidence: < %f >\n", result);
                input_pause();
                break;
            case '4':
                /*#POINTLESS:
                //get letter frequencies:
                totalFrequency = 0;
                file_letter_frequencies(frequencies, 1);
                //calculate total frequencies:
                for(i = 0; i < 26; i++)
                    totalFrequency += (frequencies[0][i] * (frequencies[0][i] - 1L));
                */

                printf("Friedman Test Prediction: < %f >\n"
                       "Index of Coincidence Test Prediction: < %d >\n"
                       "Index of Coincidence: < %f >\n"
                       "Letter Count: < %d >\n",
                       friedman_test(), IndexCrack(), index_of_coincidence(), letter_count());
                input_pause();
                break;
            case '-':
                return;
                break;
            default:
                error((AppError = INCORRECT_INPUT), NULL);
                break;
        }
        fflush(stdin);
    }
}
