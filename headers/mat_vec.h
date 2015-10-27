#ifndef GUARD_mat_vec_h
#define GUARD_mat_vec_h

VecDoub mat_vec_head(const MatDoub &mat, const VecDoub &v) {
	
	VecDoub out(v.size()/2);
	for(int i=0;i<out.size();i++) {
		out[i] = 0.0;
		for(int j=0;j<out.size();j++) {
			out[i] += mat[i][j]*v[j];
		}
	}
	return out;	
}

VecDoub mat_vec_tail(const MatDoub &mat, const VecDoub &v) {
	VecDoub out(v.size()/2);
	for(int i=0;i<out.size();i++) {
		out[i]=0.0;
		for(int j=0;j<out.size();j++) {
			out[i] += mat[i][j]*v[j];
		}
	}
	return out;
}




#endif

