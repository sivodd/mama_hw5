#ifndef _MATRIX_H_
#define _MATRIX_H_

#include"Variable.h"
#include"Scalar.h"


class Matrix : public Variable
{
public:
	Matrix(int rows, int cols, int val);
	Matrix(int startVal, int endVal);
	Matrix(const Matrix& rhs);

    virtual VarPtr Copy()const;
    virtual VarPtr NumElems() const ;
    virtual VarPtr Size()const ;
    virtual VarPtr Size(int dim)const ;
    virtual VarPtr Transpose()const ;
    virtual VarPtr Conv(VarPtr rhs) const;
    virtual void print(ostream& ro) const;

	virtual int& operator[](const int idx);
    virtual const int& operator[](const int idx)const ;
	virtual int& operator[](const IdxVec v);
    virtual const int& operator[](const IdxVec v)const ;


	virtual VarPtr operator+(const Variable&)const;
	virtual VarPtr operator+(const Scalar&)const;
	virtual VarPtr operator+(const Matrix&)const;

	virtual VarPtr operator*(const Variable&)const;
	virtual VarPtr operator*(const Scalar&)const;
	virtual VarPtr operator*(const Matrix&)const;

	virtual VarPtr operator<(const Variable&)const;
	virtual VarPtr operator<(const Scalar&)const;
	virtual VarPtr operator<(const Matrix&)const;

	virtual VarPtr operator>(const Variable&)const;
	virtual VarPtr operator>(const Scalar&)const;
	virtual VarPtr operator>(const Matrix&)const;

	virtual VarPtr operator==(const Variable&)const;
	virtual VarPtr operator==(const Scalar&)const;
	virtual VarPtr operator==(const Matrix&)const;

	virtual VarPtr operator&&(const Variable&)const;
	virtual VarPtr operator&&(const Scalar&)const;
	virtual VarPtr operator&&(const Matrix&)const;

	virtual VarPtr operator||(const Variable&)const;
	virtual VarPtr operator||(const Scalar&)const;
	virtual VarPtr operator||(const Matrix&)const;


//private: scalar uses this values is it ok to leave as public and use class methods like size() to get our info.
	int rows_;
    int cols_;
    vector<IdxVec> array2D; //http://www.cplusplus.com/forum/articles/7459/

};




#endif // _MATRIX_H_
