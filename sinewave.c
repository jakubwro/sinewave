#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>
#include "sinewave.h"

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

double* powerspectrum(fftw_complex* spectr, int length)
{
    double* result = (double*)malloc((length/2+1) * sizeof(double));
    if (result == NULL)
        return NULL;

    for (int i = 0; i < length/2+1; i++)
    {
        double real = creal(spectr[i]);
        double imag = cimag(spectr[i]);
        result[i] = sqrt(real*real + imag*imag);
    }
    return result;
}

double* spectrum(double *buffer, int length)
{ 
    fftw_complex* out = fftw_malloc(((length/2)+1)*sizeof(fftw_complex));
    if (out == NULL)
        return NULL;

    fftw_plan plan = fftw_plan_dft_r2c_1d(length, buffer, out, FFTW_ESTIMATE);
    fftw_execute(plan);
    double* result = powerspectrum(out, length);
    fftw_destroy_plan(plan);
    fftw_free(out);
    return result;
}