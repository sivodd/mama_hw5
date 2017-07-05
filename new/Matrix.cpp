#include"Matrix.h"
#include"ScriptExceptions.h"


Matrix :: Matrix(int rows, int cols, int val){
	rows_=rows;
	cols_= cols;
	array2D.resize((unsigned long)rows_);
	for (int i = 0; i < rows_; ++i)
		array2D[i].resize((unsigned long)cols_);
	for (int i =0; i<rows_; ++i){
		for (int j = 0; j < cols_ ; ++j) {
			array2D[i][j] = val;
		}
	}
}

Matrix :: Matrix(int startVal, int endVal){
	rows_=1;
	cols_= endVal-startVal+1;
	array2D.resize((unsigned long)rows_);
	for (int i = 0; i < rows_; ++i)
		array2D[i].resize((unsigned long)cols_);
	for (int j = 0; j < cols_ ; ++j) {
			array2D[0][j] = startVal+j;// make sure the first val is start val.
		}
}

Matrix::Matrix(const Matrix& rhs) : Variable(rhs), rows_(rhs.rows_), cols_(rhs.cols_)
{
	array2D= rhs.array2D;
}

VarPtr Matrix::Copy() const {
	return VarPtr(new Matrix(*this));
}

VarPtr Matrix::NumElems() const {
	int value=cols_*rows_;
	return VarPtr(new Scalar(value));
}

VarPtr Matrix::Size() const {
	Matrix* mat= new Matrix(1,2,cols_);
	mat->array2D[0][0]=rows_;
	return VarPtr(mat);
}

VarPtr Matrix::Size(int dim) const {
	if (dim>2 || dim<1)
		throw BAD_INPUT;
	if (dim==1)
		return VarPtr(new Scalar(rows_));
	if (dim==2)
		return VarPtr(new Scalar(cols_));
}

VarPtr Matrix::Transpose() const{
	Matrix* mat = new Matrix(cols_,rows_,0);
	for (int i = 0; i < rows_ ; ++i) {
		for (int j = 0; j <cols_ ; ++j) {
			mat->array2D[j][i]=this->array2D[i][j];
		}
	}
	return VarPtr(mat);
}

void Matrix::print(ostream& ro) const{
	for (int i = 0; i <rows_ ; ++i) {
		for (int j = 0; j < cols_; ++j) {
			ro << array2D[i][j]<< "\t";
		}
		if (i!=rows_-1)
			ro << "\n";
	}
}

//from staff
VarPtr Matrix::Conv(VarPtr rhs) const
{
	if ((*NumElems())[1] == 0)
		return VarPtr(new Matrix(*this));
	if ((*(rhs->NumElems()))[1] == 0)
		return VarPtr(new Matrix(rows_, cols_, 0));

	VarPtr pRet = VarPtr(new Matrix(rows_, cols_, 0));
	VarPtr rhsSize = rhs->Size();
	int rhsRows = (*rhsSize)[1], rhsCols = (*rhsSize)[2];
	IdxVec rhsCenter = { (rhsRows / 2) + 1,(rhsCols / 2) + 1 };
	int maxRowShift = rhsRows - rhsCenter[0];
	int minRowShift = 1 - rhsCenter[0];
	int maxColShift = rhsCols - rhsCenter[1];
	int minColShift = 1 - rhsCenter[1];
	for (int resRow = 1; resRow <= rows_; ++resRow)
		for (int resCol = 1; resCol <= cols_; ++resCol)
		{
			IdxVec resIdx = { resRow,resCol };
			for (int rowShift = minRowShift; rowShift <= maxRowShift; ++rowShift)
				for (int colShift = minColShift; colShift <= maxColShift; ++colShift)
				{
					try
					{
						(*pRet)[resIdx] += ((*this)[resIdx + IdxVec{ -rowShift,-colShift }] * (*rhs)[rhsCenter + IdxVec{rowShift,colShift}]);
					}
					catch (...)
					{
						// convolution is zero padded (no action required)
					}
				}
		}
	return pRet;
}

int& Matrix::operator[](const int idx){
	int count=1;
	if (idx<1 || idx<(rows_*cols_))
		throw INDEX_OUT_OF_RANGE;
	for (int i = 0; i < cols_; ++i) {
		for (int j = 0; j <rows_ ; ++j) {
			if (count==idx)
				return array2D[i][j];
			count++;
		}
	}
}

const int& Matrix::operator[](const int idx) const {
	int count=1;
	if (idx<1 || idx<(rows_*cols_))
		throw INDEX_OUT_OF_RANGE;
	for (int i = 0; i < cols_; ++i) {
		for (int j = 0; j <rows_ ; ++j) {
			if (count==idx)
				return array2D[i][j];
			count++;
		}
	}
}
int& Matrix::operator[](const IdxVec v) {
	if (v.size()!=2 || v[0]>rows_ || v[0]<1 || v[1]>cols_ || v[1]<1)
		throw INDEX_OUT_OF_RANGE;
	return array2D[v[0]-1][v[1]-1];
}

const int& Matrix::operator[](const IdxVec v) const {
	if (v.size()!=2 || v[0]>rows_ || v[0]<1 || v[1]>cols_ || v[1]<1)
		throw INDEX_OUT_OF_RANGE;
	return array2D[v[0]-1][v[1]-1];
}

VarPtr Matrix::operator+(const Variable& v) const {
	return (v + *this);
}

VarPtr Matrix::operator+(const Scalar& s) const {
	Matrix* new_mat=new Matrix(rows_,cols_,0);
	for (int i = 0; i <new_mat->rows_ ; ++i) {
		for (int j = 0; j <new_mat->cols_ ; ++j) {
			new_mat->array2D[i][j]=s.val_+array2D[i][j];
		}
	}
	return VarPtr(new_mat);
}


VarPtr Matrix::operator+(const Matrix& m) const {
	if (m.rows_ != rows_ || m.cols_!=cols_)
		throw BAD_MAT_DIMS("+");
	Matrix* new_mat=new Matrix(rows_,cols_,0);
	for (int i = 0; i <rows_ ; ++i) {
		for (int j = 0; j <cols_ ; ++j) {
			new_mat->array2D[i][j]=m.array2D[i][j]+array2D[i][j];
		}
	}
	return VarPtr(new_mat);
}

VarPtr Matrix::operator*(const Variable& v) const {
	return (v * *this);
}

VarPtr Matrix::operator*(const Scalar& s) const {
	Matrix* mat= new Matrix(rows_,cols_,0);
	for (int i = 0; i <mat->rows_ ; ++i) {
		for (int j = 0; j < mat->cols_ ; ++j) {
			mat->array2D[i][j]=s.val_*array2D[i][j];
		}
	}
	return VarPtr(mat);
}

VarPtr Matrix::operator*(const Matrix& m) const {
	if (m.rows_ != rows_ || m.cols_ !=cols_)
		throw BAD_MAT_PROD;
	Matrix* new_mat = new Matrix(rows_, cols_, 0);
	int sum=0;
	for (int i = 0; i <new_mat->rows_ ; ++i) {
		for (int j = 0; j <new_mat->cols_ ; ++j) {
			for (int k = 0; k <rows_ ; ++k) {
				sum+=m.array2D[i][k]*array2D[k][j];
			}
			new_mat->array2D[i][j]= sum;
			sum=0;
		}
	}
	return VarPtr(new_mat);
}

VarPtr Matrix::operator<(const Variable& v) const {
	return (v > *this);
}

VarPtr Matrix::operator<(const Scalar& s) const {
	Matrix* new_mat= new Matrix(rows_,cols_,0);
	for (int i = 0; i <new_mat->rows_ ; ++i) {
		for (int j = 0; j <new_mat->cols_ ; ++j) {
			new_mat->array2D[i][j]=array2D[i][j]<s.val_;
		}
	}
	return VarPtr(new_mat);
}

VarPtr Matrix::operator<(const Matrix& m) const {
	if (m.rows_ != rows_ || m.cols_ !=cols_)
		throw BAD_MAT_DIMS(">/<");
	Matrix* new_mat= new Matrix(rows_,cols_,0);
	for (int i = 0; i <new_mat->rows_ ; ++i) {
		for (int j = 0; j <new_mat->cols_ ; ++j) {
			new_mat->array2D[i][j]=array2D[i][j]<m.array2D[i][j];
		}
	}
	return VarPtr(new_mat);
}

VarPtr Matrix::operator>(const Variable& v) const {
	return (v < *this);
}

VarPtr Matrix::operator>(const Scalar& s) const {

	Matrix* new_mat= new Matrix(rows_,cols_,0);
	for (int i = 0; i <new_mat->rows_ ; ++i) {
		for (int j = 0; j <new_mat->cols_ ; ++j) {
			new_mat->array2D[i][j]=array2D[i][j]>s.val_;
		}
	}
	return VarPtr(new_mat);
}

VarPtr Matrix::operator>(const Matrix& m) const {
	if (m.rows_ != rows_ || m.cols_ !=cols_)
		throw BAD_MAT_DIMS(">/<");
	Matrix* new_mat= new Matrix(rows_,cols_,0);
	for (int i = 0; i <new_mat->rows_ ; ++i) {
		for (int j = 0; j <new_mat->cols_ ; ++j) {
			new_mat->array2D[i][j]=array2D[i][j]>m.array2D[i][j];
		}
	}
	return VarPtr(new_mat);
}

VarPtr Matrix::operator==(const Variable& v) const {
	return (v == *this);
}

VarPtr Matrix::operator==(const Scalar& s) const {

	Matrix* new_mat= new Matrix(rows_,cols_,0);
	for (int i = 0; i <new_mat->rows_ ; ++i) {
		for (int j = 0; j <new_mat->cols_ ; ++j) {
			new_mat->array2D[i][j]=array2D[i][j]==s.val_;
		}
	}
	return VarPtr(new_mat);
}

VarPtr Matrix::operator==(const Matrix& m) const {
	if (m.rows_ != rows_ || m.cols_ !=cols_)
		throw BAD_MAT_DIMS("==");
	Matrix* new_mat= new Matrix(rows_,cols_,0);
	for (int i = 0; i <new_mat->rows_ ; ++i) {
		for (int j = 0; j <new_mat->cols_ ; ++j) {
			new_mat->array2D[i][j]=array2D[i][j]==m.array2D[i][j];
		}
	}
	return VarPtr(new_mat);
}

VarPtr Matrix::operator&&(const Variable& v) const {
	return (v && *this);
}

VarPtr Matrix::operator&&(const Scalar& s) const {
	throw BAD_INPUT;
}

VarPtr Matrix::operator&&(const Matrix& m) const {
	throw BAD_INPUT;
}

VarPtr Matrix::operator||(const Variable& v) const {
	return (v || *this);
}

VarPtr Matrix::operator||(const Scalar& s) const {
	throw BAD_INPUT;
}

VarPtr Matrix::operator||(const Matrix& m) const {
	throw BAD_INPUT;
}