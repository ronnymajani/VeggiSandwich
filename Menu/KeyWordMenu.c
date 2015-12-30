#include "Menu.h"
#include "../Functions/GeneralFunctions.h"
#include "../Key_Word/Frequency.h"
#include "../Key_Word/Ceaser.h"
#include <stdio.h>
#include <stdlib.h>

void run_KeyWordMenu()
{
    char input;

    fflush(stdin);

    while(1)
    {
        puts("\n\n\n=====================KEYWORD CRACK=======================\n");
        printf("Select a Tool:\n"
               "[1] Frequency Analysis\n"
               "[2] Automatically Crack the Cipher\n"
               "[-] Return to Main Menu\n"
               ">>  ");
        scanf("%c", &input);

        switch(input)
        {
            case '1':
                run_FrequencyMenu();
                break;
            case '2':
                run_CeaserMenu();
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
