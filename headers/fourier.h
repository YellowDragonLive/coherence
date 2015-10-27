#ifndef GUARD_fourier_h
#define GUARD_fourier_h

#include <math.h>
#include "constants.h"

template<class V>
void ft(const V &v, int size, V &ftv) {
	for(int k=0;k<size;k++) {
		ftv[2*k] = v[k]*cos(2*PI*k*(-2./size + k)/size);
		ftv[2*k+1] = v[k]*sin(2*PI*k*(-2./size + k)/size);
	}
}

//return hanning window, indix i, total size N
double hann(int i, int N)
{
	return 0.5*(1-cos(2*PI*i/N));
}



#endif





