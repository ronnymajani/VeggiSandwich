#ifndef FREQUENCY_H_INCLUDED
#define FREQUENCY_H_INCLUDED

void run_FrequencyMenu();
void frequency_analysis(int length);

void file_letter_frequencies(int empty_array[][27], int length);

void letter_permutations(double empty_array[26], char partial_array[], int text_length);
void scale_frequencies(double frequencies[26]);
double sum_residual_error(double scaled_frequencies[26]);

int letter_count();


#endif // FREQUENCY_H_INCLUDED
