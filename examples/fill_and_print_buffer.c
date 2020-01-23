#include <stdio.h>
#include <stdlib.h>
#include "sinewave.h"

int main()
{
    sinewave *sine = malloc(sizeof(sinewave));
    int res = init(sine, 440, 48000);
    if (res != 0)
        printf("Init failed for given args\n");

    printf("\nCurrent sample: %lf\n", sine->current);

    size_t length = 64;
    double *buffer = malloc(length * sizeof(double));
    if (buffer == NULL)
        printf("Memory allocation failed\n");
    
    fill(sine, buffer, length);

    printf("\nBuffer content: \n");
    for (int i = 0; i < length; ++i)
        printf("%lf, %s", buffer[i], (i+1) % 8 ? "" : "\n");

    printf("\n\nCurrent sample: %lf\n\n", sine->current);

    return 0;
}