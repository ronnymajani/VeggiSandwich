#ifndef DECRYPT_H_INCLUDED
#define DECRYPT_H_INCLUDED

void decrypt_text_print(char *encrypted_text, char keyword[], int text_length, int keyword_length);
char* decrypt_text_array(char *encrypted_text, char keyword[], int text_length, int keyword_length);
void decrypt_file(const char keyword[], int toprint);

#endif // DECRYPT_H_INCLUDED
