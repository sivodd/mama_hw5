#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>

#include<iostream>
#include<vector>
#include"MySharedPtr.h"

using namespace std;
class Variable;
class Scalar;
class Matrix;

typedef MySharedPtr<Variable> VarPtr;
typedef vector<int> IdxVec;

IdxVec operator+(const IdxVec& lhs, const IdxVec& rhs);

ostream& operator<<(ostream& re, const VarPtr& var_ptr);

class Variable
{
//protected:
//    int rows_;
//    int cols_;

public:

//	Variable(int rows, int columns);
    Variable(){};
    Variable(VarPtr){};
	virtual ~Variable(){};

	virtual void print(ostream& ro) const=0;
	
	virtual VarPtr Copy() const = 0;//staff

    virtual VarPtr NumElems() const =0;
    virtual VarPtr Size() const=0;
    virtual VarPtr Size(int dim) const=0;
    virtual VarPtr Conv(VarPtr var_ptr) const =0;
    virtual VarPtr Transpose() const =0;

    virtual int& operator[](const int idx) = 0;
    virtual const int& operator[](const int idx) const = 0;
    virtual int& operator[](const IdxVec v) = 0;
    virtual const int& operator[](const IdxVec v) const = 0;

	virtual VarPtr operator+(const Variable&) const = 0;//staff
	virtual VarPtr operator+(const Scalar&) const = 0;//staff
	virtual VarPtr operator+(const Matrix&) const = 0;//staff

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

	virtual VarPtr operator&&(const Variable&) const = 0;
	virtual VarPtr operator&&(const Scalar&) const = 0;
	virtual VarPtr operator&&(const Matrix&) const = 0;

	virtual VarPtr operator||(const Variable&) const = 0;
	virtual VarPtr operator||(const Scalar&) const = 0;
	virtual VarPtr operator||(const Matrix&) const = 0;

};




#endif // _VARIABLE_H_
