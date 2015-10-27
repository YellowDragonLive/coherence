#ifndef GUARD_vec_manip_h
#define GUARD_vec_manip_h


template<class V>
V remove_complex(const V &v, int size)
{
	V temp(size/2,0.0);
	for(int j=0;j<size/2-1;j++) temp[j] = v[j*2];
	temp[size/2 - 1] = v[1];
	return temp;
}


template<class V>
V abs_sq_vec(const V &v, int size)
{
	V temp(size/2);
	temp[0] = v[0]*v[0];
	for(int i=1;i<size/2;i++) {
		temp[i] = v[2*i]*v[2*i] + v[2*i+1]*v[2*i+1];
	}
	temp[size/2-1] = v[1]*v[1];
	return temp;
}
	

#endif

