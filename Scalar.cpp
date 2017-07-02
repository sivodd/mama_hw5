#include"Scalar.h"
#include"Matrix.h"
#include"ScriptExceptions.h"

using namespace std;

Scalar::Scalar(int val) :
	Value_(val) {} //Variable(), 

Scalar::~Scalar() {}

VarPtr Scalar::Copy() const
{
	Scalar* x = new Scalar(Value_);
	return VarPtr(x);
}

VarPtr Scalar::NumElems() const
{
	return VarPtr(new Scalar(1));
}

VarPtr Scalar::Size() const
{
	return VarPtr(new Matrix(1, 2, 1));
}

VarPtr Scalar::Size(int dim) const
{
	return VarPtr(new Scalar(1));
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

VarPtr Scalar::Transpose() const
{
	Scalar* x = new Scalar(Value_);
	return VarPtr(x);
}

const int& Scalar::operator[](int idx) const
{
	if (idx != 1)
		throw(INDEX_OUT_OF_RANGE);
	return Value_;
}

int& Scalar::operator[](IdxVec V) const
{
	int size = (int)V.size();
	bool dif = false; 
	for (int i = 1; i < size + 1; i++)
	{
		if (V[i] != 1)
			dif = true;
	}
	if (dif)
		throw(INDEX_OUT_OF_RANGE);
	int x = Value_;//omer
	return x;
}

VarPtr Scalar::operator+(const Variable& V) const
{
	return (V + *this);
}

VarPtr Scalar::operator+(const Scalar& s) const
{
	Scalar* x = new Scalar(Value_ + s.Value_);
	return VarPtr(x);
}

VarPtr Scalar::operator+(const Matrix& m) const
{
	Matrix* M = new Matrix(m.rows_,m.cols_,0);
	for (int i = 1; i < M->rows_ + 1; i++)
	{
		for (int j = 1; j < M->cols_ + 1; j++)
		{
			(*(*M->matrix_)[i])[j] = (*(*M->matrix_)[i])[j] + Value_;
		}
	}
	return  VarPtr(M);
}

VarPtr Scalar::operator*(const Variable& V) const
{
	return (V * (*this));
}

VarPtr Scalar::operator*(const Scalar& s) const
{
	Scalar *x = new Scalar(Value_ + s.Value_);
	return VarPtr(x);
}

VarPtr Scalar::operator*(const Matrix& m) const
{
	Matrix* M = new Matrix(m.rows_,m.cols_,1);
	for (int i =1; i<M->rows_+1;i++)
	{
		for (int j=1;i<M->cols_+1;j++)
			(*(*M->matrix_)[i])[j] *= Value_;
	}
	return VarPtr(M);
}

VarPtr Scalar::operator<(const Variable& V) const
{
	return (V > *this);
}

VarPtr Scalar::operator<(const Scalar& s) const
{
	Scalar* S = new Scalar(Value_ < s.Value_);
	return VarPtr(S);
}

VarPtr Scalar::operator<(const Matrix& m) const
{
	Matrix* M = new Matrix (m.rows_,m.cols_,0);
	for (int i=1; i<m.rows_+1;i++)
	{
		for(int j=1;j<m.cols_+1;j++)
		{
			(*(*M->matrix_)[i])[j] = (Value_<((*(*m.matrix_)[i])[j]));
		}
	}
	return VarPtr(M);
}

VarPtr Scalar::operator>(const Variable& V) const
{
	return (V > *this);
}

VarPtr Scalar::operator>(const Scalar& s) const
{
	Scalar* S = new Scalar(Value_ > s.Value_);
	return VarPtr(S);
}

VarPtr Scalar::operator>(const Matrix& m) const
{
	Matrix* M = new Matrix (m.rows_,m.cols_,0);
	for (int i=1; i<m.rows_+1;i++)
	{
		for(int j=1;j<m.cols_+1;j++)
		{
			(*(*M->matrix_)[i])[j] = (Value_ > ((*(*m.matrix_)[i])[j]));
		}
	}
	return VarPtr(M);
}

VarPtr Scalar::operator==(const Variable& V) const
{
	return (V == *this);
}

VarPtr Scalar::operator==(const Scalar& s) const
{
	Scalar* S = new Scalar(Value_==s.Value_);
	return VarPtr(S);
}

VarPtr Scalar::operator==(const Matrix& m) const
{
	Matrix* M = new Matrix (m.rows_,m.cols_,0);
	for (int i=1; i<m.rows_+1;i++)
	{
		for(int j=1;j<m.cols_+1;j++)
		{
			(*(*M->matrix_)[i])[j] = (Value_ == (*(*m.matrix_)[i])[j]);
		}
	}
	return VarPtr(M);
}

VarPtr Scalar::operator&&(const Variable& V) const
{
	return (V && *this);
}

VarPtr Scalar::operator&&(const Scalar& s) const
{
	Scalar* S = new Scalar(Value_&&s.Value_);
	return VarPtr(S);
}

VarPtr Scalar::operator&&(const Matrix&) const
{
	throw (BAD_INPUT);
}

VarPtr Scalar::operator||(const Variable& V) const
{
	return (V || *this);
}

VarPtr Scalar::operator||(const Scalar& s) const
{
	Scalar* S = new Scalar(Value_||s.Value_);
	return VarPtr(S);
}

VarPtr Scalar::operator||(const Matrix&) const
{
	throw (BAD_INPUT);
}

ostream& Scalar::operator<<(ostream& ro) {
	print(ro);
	return ro;
}

void Scalar::print(ostream& ro) const {
	ro << Value_;
}

//void Scalar::operator<<(const Variable&) const;
//{
//	cout << Value_ << endl;
//}


//
//void Scalar :: print(ostream& ro) const{
//    ro << Value_;
//
//}