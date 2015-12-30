#include "Friedman.h"
#include "../Key_Word/Frequency.h"
#include "../Functions/SharedMacros.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

double index_of_coincidence()
{
     int frequencies[1][27];
    register int i;
    double totalLetters, IOC;
     int totalFrequency;

    //get total letter count:
    totalLetters = letter_count();

    //get letter frequencies:
    totalFrequency = 0;
    file_letter_frequencies(frequencies, 1);

    //calculate total frequencies:
    for(i = 0; i < 26; i++)
        totalFrequency += (frequencies[0][i] * (frequencies[0][i] - 1));

    //calculate IOC:
    IOC = (totalFrequency / (totalLetters * (totalLetters - 1)));

    Session.IOC = IOC;
    return IOC;
}


double friedman_test()
{
    double keylength, totalLetters, IOC;
    IOC = index_of_coincidence();

    //get total letter count:
    totalLetters = letter_count();

    //calculate keylength:
    //keylength = ((0.0265 * totalLetters) / ((0.065 - IOC) + (totalLetters * (IOC - 0.085))));
    keylength = ((0.027 * totalLetters) / ((IOC * (totalLetters - 1)) + English_Kappa - (0.038 * totalLetters)));

    //return keylength:
    Session.keylength = (int)round(keylength);
    return keylength;
}
