#ifndef GUARD_auto_correlation_h
#define GUARD_auto_correlation_h

//calculates the auto corelation of the rows in the matrix yt
void auto_correlation( const MatDoub &yt, MatDoub &corr){
	int nareas = yt.nrows();	// number of areas 
	int nt = yt.ncols(); 		// number of time steps

	for(int n=0;n<nareas;n++){
		for(int i=0;i<nt;i++){
			for(int j=0;j<(nt-i);j++){
				corr[n][i] += yt[n][j]*yt[n][j+i];
			}
//			corr[n][i] /= nt-i;
		}
	}
	// normalize correlation w.r.t corr[n][0]
	for(int n=0;n<nareas;n++) {
		double corr0 = corr[n][0];
		for(int i=0;i<nt;i++) {
			corr[n][i] /= corr0;
		}
	}

}




#endif

