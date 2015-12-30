#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"
#include "../Functions/GeneralFunctions.h"

static void Main_Menu();
static void menu_switch(char c);
static void welcome_message();


int Initialize_App()
{
    //#TORESTORE:
    welcome_message();
    input_pause();
    puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    Initialize_Data();
    input_pause();

    Main_Menu();
    return 1;
}

static void Main_Menu()
{
    while(1)
    {
        char input;

        printf(
               "\n\n\n===========================================================\n"
               "Type the corresponding letter/number of the option you wish to use:\n\n"
               "[1]: KEY LENGTH FINDING TOOLS\n"
               "[2]: KEY WORD CRACKING TOOLS\n"
               "[3]: DECRYPTION\n"
               "[0]: MANAGE SESSIONS and SAVE FILES\n"
               "[x]: SAVE PROGRESS + EXIT APP\n\n"
               ">>  "
                );
        scanf("%c", &input);
        menu_switch(input);
        fflush(stdin);
    }
}


static void menu_switch(char c)
{
    switch(c)
    {
        case '1':
            run_KeyLengthMenu();
            break;
        case '2':
            run_KeyWordMenu();
            break;
        case '3':
            run_DecryptMenu();
            break;
        case '0':
            Data_Manager_UI();
            break;
        case 'x':
        case 'X':
            puts("Exiting App...");
            ExitApp(0);
            break;
        default:
            error((AppError = INCORRECT_INPUT), NULL);
            break;
    }
    puts("===========================================================");
    input_pause();
}


static void welcome_message()
{
    printf(
"Welcome to Project Veggie version 1.1\n"
"This application provides the required tools to assist the user and even possibly automate the process of cracking "
"text encrypted via the VEGENERE Cypher.\n"
"The application has a unique file that contains the calculated data so the user needs not write it down as he runs each step separately "
"hence providing the user with the option to manually attempt the deciphering or use the pre-calculated data.\n"
"The application automatically starts a new session everytime the app starts, but the user has the option to load an older session "
"and continue from where he\\she previously left off\n\n"
"The purpose of this app is to abstract the calculation that are gone through when decrypting text.\n"
"It is assumed the language in the text is ENGLISH, and therefore the normal probability constants specific to the ENGLISH language "
"will be used.\n\n"
"This application was written by Ronny Majani.\n"
"For further information please feel free to contact me at: ronnymajani@gmail.com\n\n"
"-------------------------------------------------------------------------------------------------------------------"
"-------------------------------------------------------------------------------------------------------------------"
"\n"
);
}

