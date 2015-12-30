#ifndef SHAREDMACROS_H_INCLUDED
#define SHAREDMACROS_H_INCLUDED

#include <stdio.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_KEYWORD_LENGTH 20
#define APPDATA_FILENAME "VEGGIE.SAVE"
#define English_Kappa 0.0667
#define English_Max_Frequency 12.702
/**
Character Frequencies defined according to:
    http://www.csm.astate.edu/~rossa/datasec/frequency.html
**/

struct Data{
    FILE *openfile;
    FILE *openencryptedfile;
    char filename[MAX_FILENAME_LENGTH + 1];
    char encryptedfilename[MAX_FILENAME_LENGTH + 1];
    int keylength;
    int letterCount;
    double IOC;
    char keyword[MAX_KEYWORD_LENGTH];
    char *decrypted_text;
    char *encrypted_text;
} Session;

//double English_Kappa = 0.0667;
//FILE* AppDataF;

#endif // SHAREDMACROS_H_INCLUDED
