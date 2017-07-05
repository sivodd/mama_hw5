#include"Scalar.h"
#include"Matrix.h"
#include"ScriptExceptions.h"

using namespace std;

//Scalar::Scalar(int val) : Variable(1, 1), val_(val){}

Scalar::Scalar(const Scalar& rhs) : Variable(rhs), val_(rhs.val_){}


VarPtr Scalar::Copy() const{
	VarPtr scalar_copy = VarPtr(new Scalar(*this));
//	Scalar* scalar_copy= new Scalar(val_);
	return scalar_copy;
}

VarPtr Scalar::NumElems() const {
	return VarPtr(new Scalar(1));
}

VarPtr Scalar::Size() const {
	Matrix* mat= new Matrix(1,2,1);
	return VarPtr(mat);
}

VarPtr Scalar::Size(int dim) const {
	return VarPtr(new Scalar(1));
}

VarPtr Scalar::Transpose() const {
	VarPtr scalar_copy = VarPtr(new Scalar(*this));
	return scalar_copy;
}

//from staff
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

void Scalar::print(ostream& ro) const{
	ro << val_;
}

int& Scalar::operator[](const int idx){
    if (idx!=1)
        throw INDEX_OUT_OF_RANGE;
    return this->val_;
}

const int& Scalar::operator[](const int idx)const {
	if (idx!=1)
		throw INDEX_OUT_OF_RANGE;
	return this->val_;
}

int& Scalar::operator[](const IdxVec v) {
    for (int i = 0; i <v.size() ; ++i) {
        if (v[i]!=1)
            throw INDEX_OUT_OF_RANGE;
    }
    return this->val_;
}


const int& Scalar::operator[](const IdxVec v)const {
	for (int i = 0; i <v.size() ; ++i) {
		if (v[i]!=1)
			throw INDEX_OUT_OF_RANGE;
		}
	return this->val_;
}


VarPtr Scalar::operator+(const Variable& v)const{
	return (v + *this);
}

VarPtr Scalar::operator+(const Scalar& s)const{
	Scalar* new_scalar=new Scalar(this->val_+s.val_);
	return VarPtr(new_scalar);
}

VarPtr Scalar::operator+(const Matrix& m)const{
	Matrix* new_mat=new Matrix(m.rows_,m.cols_,0);
	for (int i = 0; i <new_mat->rows_ ; ++i) {
		for (int j = 0; j <new_mat->cols_ ; ++j) {
			new_mat->array2D[i][j]=val_+m.array2D[i][j];
		}
	}
	return VarPtr(new_mat);
}

VarPtr Scalar::operator*(const Variable& v)const{
	return (v * *this);
}
VarPtr Scalar::operator*(const Scalar& s)const{
	int new_val= s.val_*val_;
	Scalar* new_scalar=new Scalar(new_val);
	return VarPtr(new_scalar);
}

VarPtr Scalar::operator*(const Matrix& m)const{
	Matrix* mat=new Matrix(m.rows_,m.cols_,0);
	for (int i = 0; i < mat->rows_ ; ++i) {
		for (int j = 0; j < mat->cols_ ; ++j) {
			mat->array2D[i][j]=val_*m.array2D[i][j];
		}
	}
	return VarPtr(mat);
}

VarPtr Scalar::operator<(const Variable& v)const{
	return (v > *this);
}

VarPtr Scalar::operator<(const Scalar& s)const{
	Scalar* new_scalar = new Scalar(val_<s.val_);
	return VarPtr(new_scalar);
}

VarPtr Scalar::operator<(const Matrix& m)const{
	Matrix* mat= new Matrix(m.rows_, m.cols_,0);
	for (int i = 0; i <mat->rows_ ; ++i) {
		for (int j = 0; j <mat->cols_ ; ++j) {
			mat->array2D[i][j]=val_<m.array2D[i][j];
		}
	}
	return VarPtr(mat);
}

VarPtr Scalar::operator>(const Variable& v)const{
	return (v < *this);
}

VarPtr Scalar::operator>(const Scalar& s)const{
	Scalar* new_scalar = new Scalar(val_>s.val_);
	return VarPtr(new_scalar);
}

VarPtr Scalar::operator>(const Matrix& m)const{
	Matrix* mat= new Matrix(m.rows_, m.cols_,0);
	for (int i = 0; i <mat->rows_ ; ++i) {
		for (int j = 0; j <mat->cols_ ; ++j) {
			mat->array2D[i][j]=val_>m.array2D[i][j];
		}
	}
	return VarPtr(mat);
}

VarPtr Scalar::operator==(const Variable& v)const{
	return (v == *this);
}

VarPtr Scalar::operator==(const Scalar& s)const{
	Scalar* new_scalar = new Scalar(val_==s.val_);
	return VarPtr(new_scalar);
}

VarPtr Scalar::operator==(const Matrix& m)const{
	Matrix* mat= new Matrix(m.rows_, m.cols_,0);
	for (int i = 0; i <mat->rows_ ; ++i) {
		for (int j = 0; j <mat->cols_ ; ++j) {
			mat->array2D[i][j]=val_==m.array2D[i][j];
		}
	}
	return VarPtr(mat);
}

VarPtr Scalar::operator&&(const Variable& v)const{
	return (v && *this);
}

VarPtr Scalar::operator&&(const Scalar& s)const{
	Scalar* new_scalar = new Scalar(val_ && s.val_);
	return VarPtr(new_scalar);
}

VarPtr Scalar::operator&&(const Matrix& m)const{
	throw BAD_INPUT;
}

VarPtr Scalar::operator||(const Variable& v)const{
	return (v || *this);
}

VarPtr Scalar::operator||(const Scalar& s)const{
	Scalar* new_scalar = new Scalar(val_ || s.val_);
	return VarPtr(new_scalar);
}

VarPtr Scalar::operator||(const Matrix& m)const{
	throw BAD_INPUT;
}
