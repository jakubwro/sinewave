#include <stdio.h>
#include <stdlib.h>
#include "sinewave.h"

int main()
{
    sinewave *sine = malloc(sizeof(sinewave));
    init(sine, 440, 48000);
    printf("\nCurrent sample: %lf\n", sine->current);

    size_t length = 64;
    double *buffer = malloc(length * sizeof(double));
    fill(sine, buffer, length);

    printf("\nBuffer content: \n");
    for (int i = 0; i < length; ++i)
        printf("%lf, ", buffer[i]);

    printf("\n\nCurrent sample: %lf\n\n", sine->current);

    return 0;
}