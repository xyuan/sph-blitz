///\file glbfunc.cpp
///\ author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
///\author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>, 

//----------------------------------------------------------------------------------------
//      Define globle paremeters and functions
//		glbfunc.h
//----------------------------------------------------------------------------------------
// ***** system includes *****
#include <iostream>
#include <fstream>
#include <string>

#include <cstdio>
#include <cstdlib>
#include <cmath>

// ***** localincludes *****
#include "glbfunc.h"

using namespace std;

//----------------------------------------------------------------------------------------
//	a. Get the maximum
//----------------------------------------------------------------------------------------
double AMAX1(double a, double b){
	if(a > b) return a;
	return b;
}
//----------------------------------------------------------------------------------------
//	b. Get the minimum
//----------------------------------------------------------------------------------------
double AMIN1(double a, double b){
	if(a < b) return a;
	return b;
}
//----------------------------------------------------------------------------------------
//	c. Get the absolute
//----------------------------------------------------------------------------------------
/*
double ABS(double a){
	if(a > 0.0) return a;
	return -a;
}
*/
//----------------------------------------------------------------------------------------
//	d. Sign of the first value is determined by the secomax_species_number value's sign
//----------------------------------------------------------------------------------------
double SIGN(double a, double b){
	if(b > 0.0) return ABS(a);
	return -ABS(a);
}
//----------------------------------------------------------------------------------------
// e. Get the maximum from four
//----------------------------------------------------------------------------------------
double AMAX4(double a, double b, double c, double d){
	a = AMAX1(a, b);
	c = AMAX1(c, d);
	return AMAX1(a, c);
}
//----------------------------------------------------------------------------------------
//	f. Get the inverse of symmetric 3x3 array
//----------------------------------------------------------------------------------------
int SymmetricInverse3x3(double M[3][3]) {

	double z1, z2, z3, z4, z5, z6, z7, z8, z9, z10, z11, z12;
	double z13, z14, z15, z16;
	    
	double m00 = M[0][0];
	double m11 = M[1][1];
	double m22 = M[2][2];
	double m12 = M[1][2];
	double m02 = M[0][2];
	double m01 = M[0][1];
	     
	z1 = m01*m01;
	z2 = m01*m02;
	z3 = m02*m02;
	z4 = m00*m11;
	z5 = -m02*m11;
	z6 = -m00*m12;
	z7 = m01*m12;
	z8 = m02*m12;
	z9 = m12*m12;
	z10 = m00*m22;
	z11 = -m01*m22;
	z12 = m11*m22;
	z13 = 2.*m12*z2;
	z14 = m22*z4;
	z1 = -z1;
	z15 = m22*z1;
	z3 = -z3;
	z16 = m11*z3;
	z2 = z2 + z6;
	z5 = z5 + z7;
	z6 = z11 + z8;
	z7 = -z9;
	z8 = m00*z7;
	z3 = z10 + z3;
	z7 = z12 + z7;
	z8 = z13 + z14 + z15 + z16 + z8;
	
	// check the determinant
	 if (ABS(z8) < 1.0e-2)	return 0;
	    
	z1 = z1 + z4;
	z4 = 1./z8;
	z2 = z2*z4;
	z5 = z4*z5;
	z6 = z4*z6;
	z3 = z3*z4;
	z7 = z4*z7;
	z1 = z1*z4;
	   
	M[0][0] = z7;
	M[1][1] = z3;
	M[2][2] = z1;
	M[1][2] = M[2][1] = z2;
	M[0][2] = M[2][0] = z5;
	M[0][1] = M[1][0] = z6;
     
	return 1;
}
//----------------------------------------------------------------------------------------
//	g. Kronecker delta
//----------------------------------------------------------------------------------------
double Kronecker(int a, int b)
{
	return a == b ? 1.0 : 0.0;
}
//	g. Sign function
double K_sign(int a, int b)
{
	return a == b ? 1.0 : -1.0;
}
//	h. comparing
double compare(int a, int b)
{
	return a >= b ? 1.0 : 0.0;
}
//  i. square
double sq(double a)
{
	return a*a;
}
