#include "sinewave.h"
#include <math.h>

int init(sinewave *sine, double frequency, double samplerate)
{
    if (frequency >= samplerate/2.0) 
    {
        return 1;
    }

    double step = 2 * M_PI * frequency / samplerate;
    sine->previous = -sin(step);
    sine->current = 0.0;
    sine->cosine = cos(step);

    return 0;
 }

double nextsample(sinewave *sine)
{
    double next = 2 * sine->current * sine->cosine - sine->previous;
    sine->previous = sine->current;
    sine->current = next;
    return next;
}

void fill(sinewave *sine, double *buffer, int length)
{
    for (int i = 0; i < length; ++i)
    {
        buffer[i] = nextsample(sine);
    }
}
