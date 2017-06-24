#include"Scalar.h"
#include"Matrix.h"
#include"ScriptExceptions.h"

using namespace std;


VarPtr Scalar::Conv(VarPtr rhs) const
{
	if ((*(rhs->NumElems()))[1] == 0)
		return VarPtr(new Scalar(0));
	VarPtr pRet = VarPtr(new Scalar(*this));
	VarPtr rhsSize = rhs->Size();
	int rhsRows = (*rhsSize)[1], rhsCols = (*rhsSize)[2];
	IdxVec rhsCenter = { (rhsRows / 2) + 1,(rhsCols / 2) + 1 };
	(*pRet)[1] *= (*rhs)[rhsCenter];
	return pRet;
}

Scalar::Scalar(int val) :
	Variable(), Value_(val) {}

Scalar::~Scalar() {}

VarPtr Scalar::Copy()
{
	Scalar* x = new Scalar(Value_);
	return VarPtr(x);
}

int Scalar::NumElems()
{
	return new Scalar(1);
} 

Matrix Scalar::Size()
{
	return new Matrix(1, 2, 1);
}

VarPtr Scalar::Conv(VarPtr ptr)
{
	return new Scalar(1);
}

VarPtr Scalar::Transpose()
{
	Scalar* x = new Scalar(Value_);
	return VarPtr(x);
}

int& Scalar::operator[](int idx)
{
	if (idx != 1)
		throw("INDEX_OUT_OF_RANGE");
	return Value_;
}

int& Scalar::operator[](IdxVec V)
{
	int size = V.size;
	bool dif = false; //omer-  what the mean of throw
	for (int i = 1; i < size + 1; i++)
	{
		if (V[i] != 1)
			dif = true;
	}
	if (dif)
		throw(INDEX_OUT_OF_RANGE);
	return Value_;
}

VarPtr Scalar::operator+(const Variable&)
{
	return 0;
}

VarPtr Scalar::operator+(const Scalar& s)
{
	Scalar* x = new Scalar(Value_ + s.Value_);
	return VarPtr(x);
}
VarPtr Scalar::operator+(const Matrix& m)
{
	for (int i = 1; i < m + 1; i++)
	{
		for (int j = 1; j < cols + 1; j++)
		{
			m.matrix[i][j] += val;
		}
	}
}