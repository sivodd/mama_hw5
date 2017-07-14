#include"Matrix.h"
#include"ScriptExceptions.h"


// *************************************************************************************
//* Function name : Matrix
//* Description   : Constructor
//* Parameters    : rows - number of rows.
//					cols - number of columns.
//					val - the value we make all cells in matrix
//* Return value  : None.
//*************************************************************************************
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

// *************************************************************************************
//* Function name : Matrix
//* Description   : Constructor
//* Parameters    : startVal - the smallest value in matrix.
//					endVale - the largest value in the matrix.
//* Return value  : None.
//*************************************************************************************
Matrix :: Matrix(int startVal, int endVal){
	rows_=1;
	cols_= endVal-startVal+1;
	array2D.resize((unsigned long)rows_);
	//for (int i = 0; i < rows_; ++i)
	array2D[0].resize((unsigned long)cols_);
	for (int j = 0; j < cols_ ; ++j) {
			array2D[0][j] = startVal+j;// make sure the first val is start val.
		}
}

// *************************************************************************************
//* Function name : Matrix
//* Description   : Copy constructor
//* Parameters    : Matrix& rhs - the ref matrix we want to copy.
//* Return value  : None.
//*************************************************************************************
Matrix::Matrix(const Matrix& rhs) : Variable(rhs), rows_(rhs.rows_), cols_(rhs.cols_)
{
	array2D= rhs.array2D;
}

// *************************************************************************************
//* Function name : ~Matrix
//* Description   : Destructor
//* Parameters    : None.
//* Return value  : None.
//*************************************************************************************
Matrix::~Matrix() 
{
	//for (int i = 0; i < rows_; ++i)
	//	delete &(array2D[i]);
	//delete &array2D;
}

// *************************************************************************************
//* Function name : Copy
//* Description   : Creates a new Matrix.
//* Parameters    : None.
//* Return value  : VarPtr - matrix
//*************************************************************************************
VarPtr Matrix::Copy() const {
	return VarPtr(new Matrix(*this));
}

// *************************************************************************************
//* Function name : NumElems
//* Description   : return Matrix of Num of Elements
//* Parameters    : None.
//* Return value  : VarPtr - num of elements
//*************************************************************************************
VarPtr Matrix::NumElems() const {
	int value=cols_*rows_;
	return VarPtr(new Scalar(value));
}

// *************************************************************************************
//* Function name : Size
//* Description   : Return Matrix of dimension of the Matrix.
//* Parameters    : None.
//* Return value  : VarPtr - matrix of dimension of the Martix.
//*************************************************************************************
VarPtr Matrix::Size() const {
	Matrix* mat= new Matrix(1,2,cols_);
	mat->array2D[0][0]=rows_;
	return VarPtr(mat);
}

// *************************************************************************************
//* Function name : Size.
//* Description   : Return Matrix of dimension of the Matrix.
//* Parameters    : int dim - the dimension we want to know.
//* Return value  : VarPtr - scalar of relevant dimension of the matrix.
//*************************************************************************************
VarPtr Matrix::Size(int dim) const {
	if (dim>2 || dim<1)
		throw BAD_INPUT;
	if (dim==1)
		return VarPtr(new Scalar(rows_));
	return VarPtr(new Scalar(cols_));
}

// *************************************************************************************
//* Function name : Transpose
//* Description   : Returns a VarPtr to the transposed matrix
//* Parameters    : None.
//* Return value  : VarPtr - the transposed matrix
//*************************************************************************************
VarPtr Matrix::Transpose() const{
	Matrix* mat = new Matrix(cols_,rows_,0);
	for (int i = 0; i < rows_ ; ++i) {
		for (int j = 0; j <cols_ ; ++j) {
			mat->array2D[j][i]=this->array2D[i][j];
		}
	}
	return VarPtr(mat);
}

// *************************************************************************************
//* Function name : Print
//* Description   : Prints the matrix
//* Parameters    : Ostream& ro - reference to ostream.
//* Return value  : None.
//*************************************************************************************
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

// *************************************************************************************
//* Function name : operator []
//* Description   : overload operator [].
//* Parameters    : index of the relevant element in the matrix.
//* Return value  : int & - the value of the element in the matrix.
//*************************************************************************************
int& Matrix::operator[](const int idx){
	if (idx<1 || idx>(rows_*cols_)) //omer
		throw INDEX_OUT_OF_RANGE;
	int RowI = (idx - 1) % rows_;
	int ColI = (idx - 1) / rows_;
	return array2D[RowI][ColI];
}

const int& Matrix::operator[](const int idx) const {
	if (idx<1 || idx>(rows_*cols_)) //omer
		throw INDEX_OUT_OF_RANGE;
	int RowI = (idx - 1) % rows_;
	int ColI = (idx - 1) / rows_;
	return array2D[RowI][ColI];
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

// *************************************************************************************
//* Function name : Operator +.
//* Description   : Overloads operator +.
//* Parameters    : Const Variable/Matrix/Scalar & rhs - the variable add to matrix.
//* Return value  : VarPtr - Matrix/Scalar to the result of the operator.
//*************************************************************************************
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

// *************************************************************************************
//* Function name : Operator *.
//* Description   : Overloads operator *.
//* Parameters    : Const Variable/Matrix/Scalar & rhs - the variable multiply with matrix.
//* Return value  : VarPtr - Matrix/Scalar to the result of the operator.
//*************************************************************************************
VarPtr Matrix::operator*(const Variable& v) const {
	if (typeid(v) == typeid(Matrix)) {
		if (cols_ != v.row_val())
		{
			throw BAD_MAT_PROD;
		}
		Matrix* m = new Matrix(cols_, rows_, 0);
		for (int i = 0; i < cols_; i++)
		{
			for (int j = 0; j < rows_; j++)
				m->array2D[i][j] = array2D[j][i];
		}
		VarPtr result = (*((*(v.Transpose()))*(*m))).Transpose();
		delete m;
		return result;
	}
	return (v * (*this));
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
	if (m.rows_ != cols_)
		throw BAD_MAT_PROD;
	Matrix* new_mat = new Matrix(rows_, m.cols_, 0);//(rows_, cols_, 0);
	int sum=0;
	for (int i = 0; i <new_mat->rows_ ; ++i) {
		for (int j = 0; j <new_mat->cols_ ; ++j) {
			for (int k = 0; k <m.rows_ ; ++k) {// k <rows_
				sum+=m.array2D[k][j]*array2D[i][k];
			}
			new_mat->array2D[i][j]= sum;
			sum=0;
		}
	}
	return VarPtr(new_mat);
}

// *************************************************************************************
//* Function name : Operator <.
//* Description   : Overloads operator <.
//* Parameters    : Const Variable/Matrix/Scalar & rhs - the variable we compare matrix to.
//* Return value  : VarPtr - Matrix/Scalar to the result of the operator.
//*************************************************************************************
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

// *************************************************************************************
//* Function name : Operator >.
//* Description   : Overloads operator >.
//* Parameters    : Const Variable/Matrix/Scalar & rhs - the variable we compare matrix to.
//* Return value  : VarPtr - Matrix/Scalar to the result of the operator.
//*************************************************************************************
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

// *************************************************************************************
//* Function name : Operator ==.
//* Description   : Overloads operator ==.
//* Parameters    : Const Variable/Matrix/Scalar & rhs - the variable we compare matrix to.
//* Return value  : VarPtr - Matrix/Scalar to the result of the operator.
//*************************************************************************************
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

// *************************************************************************************
//* Function name : Operator &&.
//* Description   : Overloads operator &&.
//* Parameters    : Const Variable/Matrix/Scalar & rhs - the variable we use the argument on.
//* Return value  : VarPtr - Matrix/Scalar to the result of the operator.
//*************************************************************************************
VarPtr Matrix::operator&&(const Variable& v) const {
	return (v && *this);
}

VarPtr Matrix::operator&&(const Scalar& s) const {
	throw BAD_INPUT;
}

VarPtr Matrix::operator&&(const Matrix& m) const {
	throw BAD_INPUT;
}

// *************************************************************************************
//* Function name : Operator ||.
//* Description   : Overloads operator ||.
//* Parameters    : Const Variable/Matrix/Scalar & rhs - the variable we use the argument on.
//* Return value  : VarPtr - Matrix/Scalar to the result of the operator.
//*************************************************************************************
VarPtr Matrix::operator||(const Variable& v) const {
	return (v || *this);
}

VarPtr Matrix::operator||(const Scalar& s) const {
	throw BAD_INPUT;
}

VarPtr Matrix::operator||(const Matrix& m) const {
	throw BAD_INPUT;
}

int Matrix::row_val() const {
	return rows_;
}


