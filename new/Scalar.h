#ifndef _SCALAR_H_
#define _SCALAR_H_

#include"Variable.h"

class Scalar : public Variable
{
public:

	Scalar(int val) : val_(val){};
    Scalar(const Scalar& s);
    ~Scalar(){};


    virtual VarPtr Copy() const ;
    virtual VarPtr NumElems() const ;
    virtual VarPtr Size() const ;
    virtual VarPtr Size(int dim) const ;
    virtual VarPtr Transpose() const ;
	virtual VarPtr Conv(VarPtr rhs) const;
    virtual void print(ostream& ro) const;

    virtual int& operator[](const int idx);
    virtual const int& operator[](const int idx)const ;
    virtual int& operator[](const IdxVec v);
    virtual const int& operator[](const IdxVec v)const ;

    virtual VarPtr operator+(const Variable&)const ;
    virtual VarPtr operator+(const Scalar&)const ;
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



//private:
    int val_;
	
};

#endif // _SCALAR_H_
