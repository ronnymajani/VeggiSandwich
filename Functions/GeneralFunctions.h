#ifndef GENERALFUNCTIONS_H_INCLUDED
#define GENERALFUNCTIONS_H_INCLUDED

typedef enum{INCORRECT_INPUT, MALLOC_FAIL, FOPEN_READ_FAIL, FOPEN_WRITE_FAIL, FOPEN_OPEN_FAIL, FOPEN_CREATE_FAIL,
CUSTOM_EXIT, CUSTOM} errorE;

errorE AppError;

void error(errorE error_type, void *description);//Handles Errors
void ExitApp(int status);//Saves Data and closes all Files and Frees allocated memory then Closes App
void input_pause();//pauses app until user inputs
void fill_array_with(int arr[], const int value, const int arrLength);//fills array with given value
void fill_doublearray_with(double arr[], const double value, const int arrLength);//fills array with given value

int maximum_int(int arr[], int arrLength);//returns index of maximum number
int maximum_double(double arr[], int arrLength);//return index of maximum double

#endif // GENERALFUNCTIONS_H_INCLUDED
