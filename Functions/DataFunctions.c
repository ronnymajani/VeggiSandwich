#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "SharedMacros.h"
#include "GeneralFunctions.h"
#include "DataFunctions.h"
#include "../Key_Word/Frequency.h"

/**
Files will be organized the following way:
> KeyLength
> Index of Coincidence
> KeyWord
> Encrypted Text File Name
**/

void change_encryptedfile()
{
    fflush(stdin);
    fclose(Session.openencryptedfile);
    free(Session.encrypted_text);
    Session.encrypted_text = NULL;

    puts("------<SELECT FILE>-------");
    puts("Please Type the name of the file you wish to decrypt\n(with FULL Path if it's in a separate directory):");
    scanf("%s", Session.encryptedfilename);
    while(!(Session.openencryptedfile = fopen(Session.encryptedfilename, "r")))
    {
        fflush(stdin);
        printf("\n{!} FAILED to OPEN FILE {!}\nPlease type the name of the file again:>> ");
        scanf("%s", Session.encryptedfilename);
    }
    fflush(stdin);
}

void open_encryptedfile()
{
    fflush(stdin);
    fclose(Session.openencryptedfile);
    while(!(Session.openencryptedfile = fopen(Session.encryptedfilename, "r")))
    {
        fflush(stdin);
        printf("\n{!} FAILED to OPEN FILE < %s > {!}\nPlease type the correct name of the file again:>> ", Session.encryptedfilename);
        scanf("%s", Session.encryptedfilename);
    }
    fflush(stdin);
}

void load_datafile()
{
    open_sessionFile();
    if(fscanf(Session.openfile, "%d\n", &(Session.keylength)) != 1)
        Session.keylength = 0;
    if(fscanf(Session.openfile, "%lf\n", &(Session.IOC)) != 1)
        Session.IOC = 0;
    if(fscanf(Session.openfile, "%s", Session.keyword)!= 1);
    if(fscanf(Session.openfile, "%s", Session.encryptedfilename)!= 1)
        change_encryptedfile();
    else
        open_encryptedfile();
    fclose(Session.openfile);
    fclose(Session.openencryptedfile);
    printf("Successfully loaded Encrypted Text file [ %s ]\n", Session.encryptedfilename);

}

void save_datafile()
{
    if((Session.openfile = fopen(Session.filename, "w")) == NULL)
        error((AppError = FOPEN_CREATE_FAIL), Session.filename);

    if(!fprintf(Session.openfile, "%d\n", Session.keylength))
        error((AppError = FOPEN_CREATE_FAIL), "Save File");
    else if(!fprintf(Session.openfile, "%f\n", Session.IOC))
        error((AppError = FOPEN_CREATE_FAIL), "Save File");
    else
    {
        if(!fprintf(Session.openfile, "%s\n", Session.keyword))
            error((AppError = FOPEN_CREATE_FAIL), "Save File");
        if(!fprintf(Session.openfile, "%s\n", Session.encryptedfilename))
            error((AppError = FOPEN_CREATE_FAIL), "Save File");
    }

    fclose(Session.openfile);
}


void open_sessionFile()
{
    if((Session.openfile = fopen(Session.filename, "r")) == NULL)
    {
        //puts("doesnt exist");//#DEBUG
        fclose(Session.openfile);
        printf("File [%s] Does Not Exits!\n"
               "New file is being created...\n", Session.filename);
        if((Session.openfile = fopen(Session.filename, "w")) == NULL)
        {
            error((AppError = FOPEN_CREATE_FAIL), Session.filename);
        }

    }
}


FILE *create_outputfile(char filename_suffix[], char mode[], int addTimeStamp)
{
    FILE *newfile;
    time_t timer;
    char buffer[26];
    struct tm *tm_info;
    char newfilename[MAX_FILENAME_LENGTH + strlen(filename_suffix) + 1];

    strcpy(newfilename, Session.encryptedfilename);
    strcat(newfilename, filename_suffix);

    newfile = fopen(newfilename, mode);

    //add timestamp to file:
    if(addTimeStamp)
    {
        time(&timer);
        tm_info = localtime(&timer);
        strftime(buffer, 26, "<%Y/%m/%d/%H:%M:%S>", tm_info);
        fprintf(newfile, "%s\n", buffer);
    }
    return newfile;
}


char *load_into_array()
{
    if(Session.encrypted_text != NULL)
        return Session.encrypted_text;

    register char c;
    register int i;
    int len;
    char *newArray;

    len = letter_count() + 2;
    newArray = (char *)malloc(len * sizeof(char));
    if(newArray == NULL)
        error((AppError = MALLOC_FAIL), "load_into_array");

    open_encryptedfile();
    FILE *file = Session.openencryptedfile;
    i = 0;

    while ((c = fgetc(file)) != EOF)
    {
        if(isalpha(c))
            newArray[i++] = c;
    }
    newArray[i] = '\0';

    fclose(file);
    free(Session.encrypted_text);
    Session.encrypted_text = newArray;
    return newArray;
}
