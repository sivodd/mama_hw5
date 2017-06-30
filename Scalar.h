#ifndef _SCALAR_H_
#define _SCALAR_H_

#include"Variable.h"

class Scalar: public Variable{
public:
	Scalar(int val);
	~Scalar();
	VarPtr Copy() const ;
	Scalar* NumElems() const;
	Matrix* Size();
    Scalar* Size(int dim);
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
	void print(ostream& ro) const;

};

#endif // _SCALAR_H_
