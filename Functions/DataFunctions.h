#ifndef DATAFUNCTIONS_H_INCLUDED
#define DATAFUNCTIONS_H_INCLUDED

void open_sessionFile();

void load_datafile();
void save_datafile();

void change_encryptedfile();
void open_encryptedfile();

char *load_into_array();

FILE *create_outputfile(char filename_suffix[], char mode[], int addTimeStamp);

#endif // DATAFUNCTIONS_H_INCLUDED
