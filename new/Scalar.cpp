#include"Scalar.h"
#include"Matrix.h"
#include"ScriptExceptions.h"

using namespace std;

// *************************************************************************************
//* Function name : Scalar
//* Description   : Copy Constructor
//* Parameters    : const Scalar & rhs - input Scalar to copy.
//* Return value  : None.
//*************************************************************************************
Scalar::Scalar(const Scalar& rhs) : Variable(rhs), val_(rhs.val_){}

// *************************************************************************************
//* Function name : Copy
//* Description   : Creates a new Scalar.
//* Parameters    : None.
//* Return value  : VarPtr - scalar
//*************************************************************************************
VarPtr Scalar::Copy() const{
	VarPtr scalar_copy = VarPtr(new Scalar(*this));
	return scalar_copy;
}

// *************************************************************************************
//* Function name : NumElems
//* Description   : return Scalar of Num of Elements
//* Parameters    : None.
//* Return value  : VarPtr - num of elements
//*************************************************************************************
VarPtr Scalar::NumElems() const {
	return VarPtr(new Scalar(1));
}

// *************************************************************************************
//* Function name : Size
//* Description   : Return Matrix of dimension of the Scalar.
//* Parameters    : None.
//* Return value  : VarPtr - matrix of dimension of the Scalar.
//*************************************************************************************
VarPtr Scalar::Size() const {
	Matrix* mat= new Matrix(1,2,1);
	return VarPtr(mat);
}

// *************************************************************************************
//* Function name : Size.
//* Description   : Return Matrix of dimension of the Scalar.
//* Parameters    : int dim - the dimension we want to know.
//* Return value  : VarPtr - scalar of relevant dimension of the Scalar.
//*************************************************************************************
VarPtr Scalar::Size(int dim) const {
	return VarPtr(new Scalar(1));
}

// *************************************************************************************
//* Function name : Transpose
//* Description   : Returns a VarPtr to the transposed Scalar
//* Parameters    : None.
//* Return value  : VarPtr - the transposed Scalar
//*************************************************************************************
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

// *************************************************************************************
//* Function name : Print
//* Description   : Prints the scalar
//* Parameters    : Ostream& ro - reference to ostream.
//* Return value  : None.
//*************************************************************************************
void Scalar::print(ostream& ro) const{
	ro << val_;
}

// *************************************************************************************
//* Function name : operator []
//* Description   : overload operator [].
//* Parameters    : index of the relevant element in the matrix.
//* Return value  : int & - the value of the element in the matrix.
//*************************************************************************************
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
    int len = (int)v.size();
	for (int i = 0; i <len ; ++i) {
        if (v[i]!=1)
            throw INDEX_OUT_OF_RANGE;
    }
    return this->val_;
}


const int& Scalar::operator[](const IdxVec v)const {
	int len = (int)v.size();
	for (int i = 0; i <len ; ++i) {
		if (v[i]!=1)
			throw INDEX_OUT_OF_RANGE;
		}
	return this->val_;
}


// *************************************************************************************
//* Function name : Operator +.
//* Description   : Overloads operator +.
//* Parameters    : Const Variable/Matrix/Scalar & rhs - the variable add to scalar.
//* Return value  : VarPtr - Matrix/Scalar to the result of the operator.
//*************************************************************************************
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


// *************************************************************************************
//* Function name : Operator *.
//* Description   : Overloads operator *.
//* Parameters    : Const Variable/Matrix/Scalar & rhs - the variable multiply with scalar.
//* Return value  : VarPtr - Matrix/Scalar to the result of the operator.
//*************************************************************************************
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

// *************************************************************************************
//* Function name : Operator <.
//* Description   : Overloads operator <.
//* Parameters    : Const Variable/Matrix/Scalar & rhs - the variable we compare scalar to.
//* Return value  : VarPtr - Matrix/Scalar to the result of the operator.
//*************************************************************************************
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

// *************************************************************************************
//* Function name : Operator >.
//* Description   : Overloads operator >.
//* Parameters    : Const Variable/Matrix/Scalar & rhs - the variable we compare scalar to.
//* Return value  : VarPtr - Matrix/Scalar to the result of the operator.
//*************************************************************************************
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

// *************************************************************************************
//* Function name : Operator ==.
//* Description   : Overloads operator ==.
//* Parameters    : Const Variable/Matrix/Scalar & rhs - the variable we compare scalar to.
//* Return value  : VarPtr - Matrix/Scalar to the result of the operator.
//*************************************************************************************
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

// *************************************************************************************
//* Function name : Operator &&.
//* Description   : Overloads operator &&.
//* Parameters    : Const Variable/Matrix/Scalar & rhs - the variable we use the argument on.
//* Return value  : VarPtr - Matrix/Scalar to the result of the operator.
//*************************************************************************************
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

// *************************************************************************************
//* Function name : Operator ||.
//* Description   : Overloads operator ||.
//* Parameters    : Const Variable/Matrix/Scalar & rhs - the variable we use the argument on.
//* Return value  : VarPtr - Matrix/Scalar to the result of the operator.
//*************************************************************************************
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
