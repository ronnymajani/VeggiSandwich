#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Functions/SharedMacros.h"
#include "../Functions/GeneralFunctions.h"
#include "../Functions/DataFunctions.h"
#include "Menu.h"


void Initialize_Data()
{
    printf("\n\n========================LOADING DATA=======================\n");
    char *filename = Session.filename;
    FILE* AppDataF = fopen(APPDATA_FILENAME, "r");
    if(AppDataF == NULL)
    {//AppData doesnt exist: create a new one and fill it with the name of the project to work with:
        fclose(AppDataF);
        AppDataF = fopen(APPDATA_FILENAME, "w");
        printf("Please Enter the name of the Project you wish to work with\n(including it's full path "
             "if it's in a separate location from the executable file):\n>>  ");
        scanf("%127s", filename);

        while(strlen(filename) < 5 || strlen(filename) > 127)
        {
            printf("\n\n{!} Project Name should be at least 5 characters and at most %d characters long {!}\n"
                 "Please Enter the name of the Project you wish to work with\n(including it's full path "
                 "if it's in a separate location from the executable file):\n>>  ", MAX_FILENAME_LENGTH);
            scanf("%127s", filename);
        }

        fputs(filename, AppDataF);
    }
    else
    {//Read SaveFile name from AppData File:
        if(!fgets(filename, MAX_FILENAME_LENGTH, AppDataF))
        {
            error((AppError = FOPEN_READ_FAIL), filename);
            fclose(AppDataF);
            AppDataF = fopen(APPDATA_FILENAME, "w");
            puts("{!} The SAVE FILE is CORRUPT {!}\n"
                 "Please Type the name of the New Project you wish to start:");
            scanf("%127s\n", filename);
            while(strlen(filename) < 5 || strlen(filename) > 127)
            {
                printf("\n\n{!} Project Name should be at least 5 characters and at most %d characters long {!}\n"
                     "Please Enter the name of the Project you wish to work with\n(including it's full path "
                     "if it's in a separate location from the executable file):\n>>  ", MAX_FILENAME_LENGTH);
                scanf("%127s", filename);
            }
            fputs(filename, AppDataF);
        }
        /*
        else if(strlen(filename) < 5 || strcmp(filename, "") == 0)
        {
            fclose(AppDataF);
            AppDataF = fopen(APPDATA_FILENAME, "w");
            puts("{!} The Name of the Saved project is INALID {!}\n"
                 "Please Type the name of the New Project you wish to start:");
            scanf("%127s\n", filename);
            fputs(filename, AppDataF);
        }
        */
    }

    //Open Save File:
    open_sessionFile();
    fclose(AppDataF);
    load_datafile(&Session);
    fclose(Session.openfile);

    printf("Successfully loaded Saved Data from [ %s ]\n", filename);
    //printf("\n%s\n", filename);//#DEBUG
    fflush(stdin);
}



static void new_file()
{
    char *filename = Session.filename;
    FILE* AppDataF;

    AppDataF = fopen(APPDATA_FILENAME, "w");
    puts("Please Enter the name of the new Project File\n"
         "(Do NOT type the same name as the Old Project):");
    scanf("%127s", filename);

    while(strlen(filename) < 5 || strlen(filename) > 127)
    {
        printf("\n\n{!} Project Name should be at least 5 characters and at most %d characters long {!}\n"
             "Please Enter the name of the new Project File\n"
             "(Do NOT type the same name as the Old Project):>>  \n", MAX_FILENAME_LENGTH);
        scanf("%127s", filename);
    }

    fputs(filename, AppDataF);
    fclose(AppDataF);

    if((Session.openfile = fopen(filename, "r")) == NULL)
    {
        if((Session.openfile = fopen(filename, "w")) == NULL)
            error((AppError = FOPEN_CREATE_FAIL), filename);
        change_encryptedfile();
    } else {
        Initialize_Data();
    }
    fclose(Session.openfile);

}




void Data_Manager_UI()
{
    fflush(stdin);
    printf("\n\n=====================CURRENTLY SAVED DATA======================\n\n"
           "Current File: < %s >\n"
           "Saved Information:\n"
           "\tKey Length: %d\n\tIndex of Coincidence: %f\n\tKey Word: %s\n"
           "\tEncrypted File: < %s >",
           Session.filename, Session.keylength, Session.IOC, Session.keyword, Session.encryptedfilename);
    while(1)
    {
        char input;
        printf("\n\n======================MANAGE SAVED DATA=======================\n\n"
               "[1] Delete the old project and Start a New Project\n"
               "[2] Preserve the Old Project and Start/Load another Project\n"
               "[3] Change the Encrypted Text File that you are working with\n"
               "[-] Go Back to the Main Menu\n"
               ">>  ");
        scanf("%c", &input);
        fflush(stdin);

        switch(input)
        {
            case '1':
                Session.keylength = 0;
                Session.IOC = 0;
                strcpy(Session.keyword, "");
                save_datafile(&Session);
                puts("SUCCESS | ALL DATA RESET");
                return;
                break;
            case '2':
                printf("\n\n======================RESETTING DATA======================\n");
                Session.IOC = 0;
                Session.keylength = 0;
                Session.decrypted_text = NULL;
                strcpy(Session.encryptedfilename, "");
                strcpy(Session.filename, "");
                strcpy(Session.keyword, "");
                fclose(Session.openencryptedfile);
                fclose(Session.openfile);
                new_file();
                printf("SUCCESS | CREATED/LOADED PROJECT [ %s ]\n", Session.filename);
                return;
                break;
            case '3':
                change_encryptedfile();
                return;
                break;
            case '-':
                return;
                break;
            default:
                error((AppError = INCORRECT_INPUT), NULL);
                break;
        }
    }
}
