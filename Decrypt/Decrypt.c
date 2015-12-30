#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../Functions/DataFunctions.h"
#include "../Functions/GeneralFunctions.h"
#include "../Functions/SharedMacros.h"

void decrypt_text_print(char *encrypted_text, char keyword[], int text_length, int keyword_length)
{
    int i, stage;
    stage = 0;

    for(i = 0; i < text_length; i++, stage= ((stage+1) % keyword_length))
    {
        int difference;
        char new_letter;
        difference = keyword[stage] - 'a';
        new_letter = (*encrypted_text - 'a') - difference;
        new_letter = (new_letter + 26) % 26;
        new_letter = new_letter + 'a';
        printf("%c", new_letter);
        encrypted_text++;
    }
}


char* decrypt_text_array(char *encrypted_text, char keyword[], int text_length, int keyword_length)
{
    int i, stage;
    char *decrypted_text, *final_text;

    final_text = decrypted_text = (char*)malloc(sizeof(char) * text_length + 1);
    if(final_text == NULL)
        error((AppError = MALLOC_FAIL), "decrypt_text_array");
    stage = 0;

    for(i = 0; i < text_length; i++, stage= ((stage+1) % keyword_length))
    {
        int difference;
        char new_letter;
        difference = keyword[stage] - 'a';
        new_letter = (*encrypted_text - 'a') - difference;
        new_letter = (new_letter + 26) % 26;
        new_letter = new_letter + 'a';
        *decrypted_text++ = new_letter;
        encrypted_text++;
    }
    *decrypted_text = '\0';
    return final_text;
}


void decrypt_file(const char keyword[], int toprint)
{
    FILE *newfile, *file;
    int stage, keyword_length;
    char new_letter;

    open_encryptedfile();
    newfile = create_outputfile(".decrypted", "a", 1);
    file = Session.openencryptedfile;
    keyword_length = strlen(keyword);

    fprintf(newfile, "[KEYWORD: %s]\n", keyword);

    fflush(NULL);

    stage = 0;
    new_letter = fgetc(file);

    while(!feof(file))
    {
        int difference;
        //calculuations:
        if(new_letter != '\n')
        {
            difference = keyword[stage] - 'a';
            new_letter = (new_letter - 'a') - difference;
            new_letter = (new_letter + 26) % 26;
            new_letter = new_letter + 'a';
        }
        //write to file:
        fputc(new_letter, newfile);
        //printing:
        if(toprint)
            fputc(new_letter, stdout);
        //iterate:
        new_letter = fgetc(file);
        stage = (stage+1) % keyword_length;
    }
    fputc('\n', newfile);
    fclose(newfile);
    fclose(file);
}
