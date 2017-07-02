#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include<iostream>
#include<vector>
#include"MySharedPtr.h"

class Variable;
class Scalar;
class Matrix;

using namespace std;

typedef MySharedPtr<Variable> VarPtr;
typedef vector<int> IdxVec;
typedef vector<IdxVec*> IdxIdx;

IdxVec operator+(const IdxVec& lhs, const IdxVec& rhs);


class Variable
{
public:
	//Variable();
	//~Variable();
	// ToDo: complete class definition
	
	virtual VarPtr Copy() const = 0;
	virtual VarPtr NumElems() const = 0;
	virtual VarPtr Size() const = 0;
	virtual VarPtr Size(int dim) const =0;
	virtual VarPtr Conv(VarPtr ptr) const = 0;
	virtual VarPtr Transpose() const = 0;

	virtual const int& operator[](int idx) const = 0;
	virtual int& operator[](IdxVec V) const = 0;

	virtual VarPtr operator+(const Variable&) const = 0;
	virtual VarPtr operator+(const Scalar&) const = 0;
	virtual VarPtr operator+(const Matrix&) const = 0;
	virtual VarPtr operator*(const Variable&) const = 0;
	virtual VarPtr operator*(const Scalar&) const = 0;
	virtual VarPtr operator*(const Matrix&) const = 0;
	virtual VarPtr operator<(const Variable&) const = 0;
	virtual VarPtr operator<(const Scalar&) const = 0;
	virtual VarPtr operator<(const Matrix&) const = 0;
	virtual VarPtr operator>(const Variable&) const = 0;
	virtual VarPtr operator>(const Scalar&) const = 0;
	virtual VarPtr operator>(const Matrix&) const = 0;
	virtual VarPtr operator==(const Variable&) const = 0;
	virtual VarPtr operator==(const Scalar&) const = 0;
	virtual VarPtr operator==(const Matrix&) const = 0;
	virtual VarPtr operator&&(const Variable&) const = 0 ;
	virtual VarPtr operator&&(const Scalar&) const = 0;
	virtual VarPtr operator&&(const Matrix&) const  =0;
	virtual VarPtr operator||(const Variable&) const  = 0;
	virtual VarPtr operator||(const Scalar&)const  = 0;
	virtual VarPtr operator||(const Matrix&) const = 0;
	virtual ostream& operator<<(ostream& ro) const = 0;
	virtual void print(ostream& ro) const=0;
};

#endif // _VARIABLE_H_
