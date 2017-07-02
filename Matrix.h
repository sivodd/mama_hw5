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
	VarPtr Copy() const;
	VarPtr NumElems() const;
	VarPtr Size() const ;
	VarPtr Size(int dim) const;
	VarPtr Transpose() const ;

	const int& operator[](int idx) const ;
	int& operator[](IdxVec) const ;

	VarPtr operator+(const Variable&) const;
	VarPtr operator+(const Scalar&)const;
	VarPtr operator+(const Matrix&)const;
	VarPtr operator*(const Variable&)const;
	VarPtr operator*(const Scalar&)const;
	VarPtr operator*(const Matrix&)const;
	VarPtr operator<(const Variable&)const;
	VarPtr operator<(const Scalar&)const;
	VarPtr operator<(const Matrix&)const;
	VarPtr operator>(const Variable&)const;
	VarPtr operator>(const Scalar&)const;
	VarPtr operator>(const Matrix&)const;
	VarPtr operator==(const Variable&)const;
	VarPtr operator==(const Scalar&)const;
	VarPtr operator==(const Matrix&)const;
	VarPtr operator&&(const Variable&)const;
	VarPtr operator&&(const Scalar&)const;
	VarPtr operator&&(const Matrix&)const;
	VarPtr operator||(const Variable&)const;
	VarPtr operator||(const Scalar&)const;
	VarPtr operator||(const Matrix&)const;
	ostream& operator<<(ostream& ro);
	void print(ostream& ro) const;

	virtual VarPtr Conv(VarPtr rhs) const;
	
};




#endif // _MATRIX_H_
