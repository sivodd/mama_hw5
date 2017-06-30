#ifndef _MATRIX_H_
#define _MATRIX_H_

#include"Variable.h"
#include"Scalar.h"


class Matrix :public Variable
{
public:
	int rows_;
	int cols_;
	IdxIdx* matrix_;

	Matrix(int rows, int cols, int val);
	Matrix(int startVal, int endVal);
	~Matrix();
	VarPtr Copy();
	Scalar* NumElems() const;
	Matrix* Size();
	Scalar* Size(int dim) const
	VarPtr Conv(VarPtr ptr);
	VarPtr Transpose();

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
	
	virtual VarPtr Conv(VarPtr rhs) const;
private:
	
};




#endif // _MATRIX_H_
