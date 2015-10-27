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

	int N = pow(2,12);	// number of data points
	int SN = 256;		// number of points in a segment
	int sn = SN;		// number of points overlap in each segment
	double dt = 1.;	// time step size
	
	int seed = 123456;
	double pi = acos(-1);
	Ran r(seed);

	VecDoub x(N,0.0);
	VecDoub y(N,0.0);

	for(int i=0;i<(N-100);i++) {
		x[i] = (r.doub() - 1)*0.01 + sin(2*pi*i*10/N);
		y[i] = (r.doub() - 1)*0.01 + sin(2*pi*i*10/N);
	}

	VecDoub Sxx(SN,0.0);
	VecDoub Syy(SN,0.0);
	VecDoub Sxy(SN,0.0);	
	VecDoub ftx(SN,0.0);
	VecDoub fty(SN,0.0);

	for(int i=0;i*SN<N;i++) {
		VecDoub xtemp(SN,0.0);
		VecDoub ytemp(SN,0.0);

		for(int j=0;j<SN;j++) {
			xtemp[j] = x[j+i*sn]*hann(j,SN);
			ytemp[j] = y[j+i*sn]*hann(j,SN);
		}

		realft(xtemp,1);
		realft(ytemp,1);

		for(int k=0;k<SN;k+=2) {
			double xr = xtemp[k];
			double xi = xtemp[k+1];
			double yr = ytemp[k];
			double yi = ytemp[k+1];

			if(k==0) {
				Sxx[k] += xr*xr;
				Syy[k] += yr*yr;
				Sxy[k] += xr*yr;

				Sxx[k+1] += xi*xi;
				Syy[k+1] += yi*yi;
				Sxy[k+1] += xi*yi;

			} else {
				Sxx[k] += xr*xr + xi*xi;
				Sxx[k+1] += 0.0;
				Syy[k] += yr*yr + yi*yi;
				Syy[k+1] += 0.0;
				Sxy[k] += xr*yr+xi*yi;
				Sxy[k+1] += xi*yr - xr*yi;
			}
		}
	}


	VecDoub Sxx_real = remove_complex(Sxx,Sxx.size());
	VecDoub Syy_real = remove_complex(Syy,Syy.size());
	VecDoub Sxy_abs_sq = abs_sq_vec(Sxy,Sxy.size());

	
	VecDoub coh(SN/2,0.0);
	for(int i=0;i<SN/2;i++) coh[i] += Sxy_abs_sq[i]/(Sxx_real[i]*Syy_real[i]);

	VecDoub coh2 = coherence(x,y,N,SN);

	// calculate frequencies:
	VecDoub f(SN/2,0.0);
	frequencies(f,SN/2,1);


	ofstream coh_out("coh.csv");
	coh_out << setprecision(16);
	write_matrix(coh,coh.size(),coh_out);

	ofstream coh2_out("coh2.csv");
	coh2_out << setprecision(16);
	write_matrix(coh2,coh2.size(),coh2_out);

	ofstream x_out("x.csv");
	x_out << setprecision(16);
	write_matrix(x,x.size(),x_out);

	ofstream y_out("y.csv");
	y_out << setprecision(16);
	write_matrix(y,y.size(),y_out);

	ofstream Sxx_out("sxx.csv");
	Sxx_out << setprecision(16);
	write_matrix(Sxx_real,Sxx_real.size(),Sxx_out);

	ofstream Syy_out("syy.csv");
	Syy_out << setprecision(16);
	write_matrix(Syy_real,Syy_real.size(),Syy_out);

	ofstream Sxy_out("sxy_abs_sq.csv");
	Sxy_out << setprecision(16);
	write_matrix(Sxy_abs_sq,Sxy_abs_sq.size(),Sxy_out);

	ofstream f_out("f.csv");
	f_out << setprecision(16);
	write_matrix(f,f.size(),f_out);

	return 0;
}




