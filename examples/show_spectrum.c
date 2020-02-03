#include <stdio.h>
#include <stdlib.h>
#include "sinewave.h"

int main()
{
    sinewave *sine = malloc(sizeof(sinewave));
    int res = init(sine, 440, 48000);
    if (res != 0)
        printf("Init failed for given args\n");

    size_t length = 256;
    double *buffer = malloc(length * sizeof(double));
    if (buffer == NULL)
        printf("Memory allocation failed\n");
    
    fill(sine, buffer, length);
    double* spectr = spectrum(buffer, length);

    printf("\nSpectrum: \n");
    for (int i = 0; i < length/2+1; ++i)
        printf("%lf, %s", spectr[i], (i+1) % 8 ? "" : "\n");

    printf("\n\nCurrent sample: %lf\n\n", sine->current);

    free(buffer);
    free(sine);
    free(spectr);
    
    return 0;
}