#ifndef GUARD_write_matrix_h
#define GUARD_write_matrix_h



#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

template<typename Vec>
void write_matrix(const Vec &v, const int size, std::ostream &outstream, char delimiter='\n')
{
	for(int i=0;i<size;i++) outstream << v[i] << delimiter;
}

template<typename Mat>
void write_matrix(const Mat &m, const int cols, const int rows, std::ostream &outstream,
				char delimiter1=';', char delimiter2='\n')
{
	for(int r=0;r<rows;r++){
		for(int c=0;c<cols;c++) {
			outstream << m[r][c];
			if( c<(cols-1) ) outstream << delimiter1;
		}
		outstream << delimiter2;
	}
}

template<typename Vec>
void write_matrix(const Vec &v,const int size, std::string out_name, char delimiter='\n', int prec = 16)
{
	std::ofstream out(out_name);
	out <<  std::setprecision(prec);
	for(int i=0;i<size;i++) out << v[i] << delimiter;
}	

#endif

