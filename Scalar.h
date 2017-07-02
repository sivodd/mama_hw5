#ifndef _SCALAR_H_
#define _SCALAR_H_

#include"Variable.h"

class Scalar: public Variable{
public:
	Scalar(int val);
	~Scalar();
	VarPtr Copy() const ;
	VarPtr NumElems() const;
	VarPtr Size() const ;
	VarPtr Size(int dim) const;
	//VarPtr Conv(VarPtr ptr) const;
	VarPtr Transpose() const;
    int Value_;

	const int& operator[](int idx) const ;
	int& operator[](IdxVec)const ;

	VarPtr operator+(const Variable&) const ;
	VarPtr operator+(const Scalar&) const ;
	VarPtr operator+(const Matrix&) const;
	VarPtr operator*(const Variable&) const;
	VarPtr operator*(const Scalar&) const;
	VarPtr operator*(const Matrix&) const;
	VarPtr operator<(const Variable&) const;
	VarPtr operator<(const Scalar&) const;
	VarPtr operator<(const Matrix&) const;
	VarPtr operator>(const Variable&) const;
	VarPtr operator>(const Scalar&) const;
	VarPtr operator>(const Matrix&) const;
	VarPtr operator==(const Variable&) const;
	VarPtr operator==(const Scalar&) const;
	VarPtr operator==(const Matrix&) const;
	VarPtr operator&&(const Variable&) const;
	VarPtr operator&&(const Scalar&)const;
	VarPtr operator&&(const Matrix&)const;
	VarPtr operator||(const Variable&)const;
	VarPtr operator||(const Scalar&)const;
	VarPtr operator||(const Matrix&)const;
	ostream& operator<<(ostream& ro);
	void print(ostream& ro) const;

	virtual VarPtr Conv(VarPtr rhs) const; 
	

};

#endif // _SCALAR_H_
