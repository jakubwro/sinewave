typedef struct sinewave
{
    double previous;
    double current;
    double cosine;
} sinewave;

/*
    Inits internal structure of sine wave generator for given frequency and
    samplerate. Generator is stable if they met a constraint.
*/
int init(sinewave *sine, double frequency, double samplerate);

/*
    Fills 'buffer' array with a number of samples specified by 'length'
    parameter.
*/
void fill(sinewave *sine, double *buffer, int length);

/*
    Generates frequency power spectrum of the given buffer 
*/
double* spectrum(double *buffer, int length);
