#ifndef _SCALAR_H_
#define _SCALAR_H_

#include"Variable.h"

class Scalar: public Variable{
public:
	Scalar(int val);
	~Scalar();
	VarPtr Copy();
	Scalar* NumElems();
	Matrix* Size();
	VarPtr Conv(VarPtr ptr);
	VarPtr Transpose();
    int Value_;

	int& operator[](int idx);
	int& operator[](IdxVec);

	VarPtr operator+(const Variable&);
	VarPtr operator+(const Scalar&);
	VarPtr operator+(const Matrix&);
	VarPtr operator*(const Variable&);
	VarPtr operator*(const Scalar&);
	VarPtr operator*(const Matrix&);
	VarPtr operator<(const Variable&);
	VarPtr operator<(const Scalar&);
	VarPtr operator<(const Matrix&);
	VarPtr operator>(const Variable&);
	VarPtr operator>(const Scalar&);
	VarPtr operator>(const Matrix&);
	VarPtr operator==(const Variable&);
	VarPtr operator==(const Scalar&);
	VarPtr operator==(const Matrix&);
	VarPtr operator&&(const Variable&);
	VarPtr operator&&(const Scalar&);
	VarPtr operator&&(const Matrix&);
	VarPtr operator||(const Variable&);
	VarPtr operator||(const Scalar&);
	VarPtr operator||(const Matrix&);

	// ToDo: complete class definition
	
	virtual VarPtr Conv(VarPtr rhs) const; //why?

};

#endif // _SCALAR_H_
