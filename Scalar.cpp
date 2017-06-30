#include"Scalar.h"
#include"Matrix.h"
#include"ScriptExceptions.h"

using namespace std;



Scalar::Scalar(int val) :
	Variable(), Value_(val) {}

Scalar::~Scalar() {}

VarPtr Scalar::Copy()
{
	Scalar* x = new Scalar(Value_);
	return VarPtr(x);
}

Scalar* Scalar::NumElems()
{
	return new Scalar(1);
} 

Matrix* Scalar::Size()
{
	return new Matrix(1, 2, 1);
}

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

VarPtr Scalar::Transpose()
{
	Scalar* x = new Scalar(Value_);
	return VarPtr(x);
}

int& Scalar::operator[](int idx)
{
	if (idx != 1)
		throw(INDEX_OUT_OF_RANGE);
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

VarPtr Scalar::operator+(const Variable& V)
{
	if(typeid(V)== typeid(Matrix))
	{
		Matrix* x = (Matrix)V;
		return (this + x);
	}
	Scalar* y  = (Scalar)V;
	return (this + y);
}

VarPtr Scalar::operator+(const Scalar& s)
{
	Scalar* x = new Scalar(Value_ + s.Value_);
	return VarPtr(x);
}

VarPtr Scalar::operator+(const Matrix& m)
{
	Matrix* M = new Matrix(m.Row_,m.Col_,0);
	for (int i = 1; i < m.Row_ + 1; i++)
	{
		for (int j = 1; j < m.cols + 1; j++)
		{
			M->matrix_[i][j] = m.matrix[i][j] + Value_;
		}
	}
	return  VarPtr(M);
}

VarPtr operator*(const Variable& V)
{
	if(typeid(V)== typeid(Matrix))
	{
		Matrix* x = (Matrix)V;
		return (this * x);
	}
	Scalar* y  = (Scalar)V;
	return (this * y);
}

VarPtr operator*(const Scalar& s)
{
	Scalar *x = new Scalar(Value_ + s.Value_);
	return VarPtr(x);
}

VarPtr operator*(const Matrix& m)
{
	VarPtr* V = m.Copy();
	Matrix* M = (Matrix)(V->pointer_);
	for (int i =1; i<M->Row_+1;i++)
	{
		for (int j=1;i<M->Col_+1;j++)
			M->matrix_[i][j] *= Value_;
	}
	return V;
}

VarPtr operator<(const Variable& V)
{
	if(typeid(V)== typeid(Matrix))
	{
		Matrix* x = (Matrix)V;
		return (this < x);
	}
	Scalar* y  = (Scalar)V;
	return (this < y);
}

VarPtr operator<(const Scalar& s)
{
	Scalar* S = new Scalar(Value_ < s.Value_);
	return VarPtr(S);
}

VarPtr operator<(const Matrix& m)
{
	Matrix* M = new Matrix (m.Row_,m.Col_,0);
	for (int i=1; i<m.Row_+1;i++)
	{
		for(int j=1;j<m.Col_+1;j++)
		{
			M->matrix_[i][j] = (Value_<m.matrix_[i][j]);
		}
	}
	return VarPtr(M);
}

VarPtr operator>(const Variable& V)
{
	if(typeid(V)== typeid(Matrix))
	{
		Matrix* x = (Matrix)V;
		return (this > x);
	}
	Scalar* y  = (Scalar)V;
	return (this > y);
}

VarPtr operator>(const Scalar& s)
{
	Scalar* S = new Scalar(Value_ > s.Value_);
	return VarPtr(S);
}

VarPtr operator>(const Matrix& m)
{
	Matrix* M = new Matrix (m.Row_,m.Col_,0);
	for (int i=1; i<m.Row_+1;i++)
	{
		for(int j=1;j<m.Col_+1;j++)
		{
			M->matrix_[i][j] = (Value_ > m.matrix_[i][j]);
		}
	}
	return VarPtr(M);
}

VarPtr operator==(const Variable& V)
{
	if(typeid(V)== typeid(Matrix))
	{
		Matrix* x = (Matrix)V;
		return (this == x);
	}
	Scalar* y  = (Scalar)V;
	return (this == y);
}

VarPtr operator==(const Scalar& s)
{
	Scalar* S = new Scalar(Value_==s.Value_);
	return VarPtr(S);
}

VarPtr operator==(const Matrix& m)
{
	Matrix* M = new Matrix (m.Row_,m.Col_,0);
	for (int i=1; i<m.Row_+1;i++)
	{
		for(int j=1;j<m.Col_+1;j++)
		{
			M->matrix_[i][j] = (Value_ == m.matrix_[i][j]);
		}
	}
	return VarPtr(M);
}

VarPtr operator&&(const Variable&)
{
	if(typeid(V)== typeid(Matrix))
	{
		Matrix* x = (Matrix)V;
		return (this && x);
	}
	Scalar* y  = (Scalar)V;
	return (this && y);
}

VarPtr operator&&(const Scalar&)
{
	Scalar* S = new Scalar(Value_&&s.Value_);
	return VarPtr(S);
}

VarPtr operator&&(const Matrix&)
{
	throw (BAD_INPUT);
}

VarPtr operator||(const Variable&)
{
	if(typeid(V)== typeid(Matrix))
	{
		Matrix* x = (Matrix)V;
		return (this || x);
	}
	Scalar* y  = (Scalar)V;
	return (this || y);
}

VarPtr operator||(const Scalar&)
{
	Scalar* S = new Scalar(Value_||s.Value_);
	return VarPtr(S);
}

VarPtr operator||(const Matrix&)
{
	throw (BAD_INPUT);
}