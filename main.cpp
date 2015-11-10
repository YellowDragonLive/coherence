#include "nr_headers/nr3.h"
#include "nr_headers/ran.h"
#include "nr_headers/fourier.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <vector>


#include "headers/constants.h"
#include "headers/fourier.h"
#include "headers/write_matrix.h"
#include "headers/vec_manip.h"
#include "headers/coherence.h"

using namespace::std;

int main()
{

	int N = pow(2,15);	// number of data points
	int SN = 256*4;		// number of points in a segment
	int D = 0;		// number of points overlap in each segment
	double dt = 1.;	// time step size
	
	int seed = 123456;
	double pi = acos(-1);
	Ran r(seed);

	VecDoub x(N,0.0);
	VecDoub y(N,0.0);

	for(int i=0;i<N;i++) {
		x[i] = (r.doub() - 1)*0.01 + sin(5000*2.*pi*i/N) + sin(8000*2.*pi*i/N);
		y[i] = (r.doub() - 1)*0.01 + sin(5000*2.*pi*i/N) + sin(8000*2.*pi*i/N);
//		x[i] = (r.doub() - 1)*2.;
//		y[i] = (r.doub() - 1)*2.;
	}

	VecDoub coh = coherence(x,y,N,SN,D,coh::hann);

	// calculate frequencies:
	VecDoub f(SN/2,0.0);
	frequencies(f,SN/2,1);


	// output
	ofstream coh_out("coh.csv");
	coh_out << setprecision(16);
	write_matrix(coh,coh.size(),coh_out);

	ofstream x_out("x.csv");
	x_out << setprecision(16);
	write_matrix(x,x.size(),x_out);

	ofstream y_out("y.csv");
	y_out << setprecision(16);
	write_matrix(y,y.size(),y_out);

	ofstream f_out("f.csv");
	f_out << setprecision(16);
	write_matrix(f,f.size(),f_out);

	return 0;
}




