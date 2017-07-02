#include"Matrix.h"
#include"ScriptExceptions.h"

Matrix :: Matrix(int rows, int cols, int val) :
	rows_(rows), cols_(cols) //Variable(), 
{
	matrix_ = new IdxIdx(rows+1);
	for (int i = 1; i <= rows + 1; i++)
	{
		(*matrix_)[i] = new IdxVec(cols+1);
		for (int j = 1; j <= cols+1; j++)
		{
			(*(*matrix_)[i])[j] = val;
		}
	}
}

Matrix::Matrix(int startVal, int endVal) :
	Variable(), rows_(1), cols_(endVal - startVal+1)
{
	matrix_ = new IdxIdx(2);
	(*matrix_)[1] = new IdxVec(cols_+1);
	for (int i = 1; i < cols_ + 1; i++)
	{
		(*(*matrix_)[1])[i] = startVal + i - 1;
	}
}

Matrix::~Matrix()
{
	for (int i = 1; i<rows_+1;i++)
	{
		free((*matrix_)[i]);
	}
	free(matrix_);
}

VarPtr Matrix :: Copy() const
{
	Matrix* m = new Matrix(rows_,cols_,1);
	for (int i =1; i< rows_+1;i++)
	{
		for (int j=1;j< cols_+1;j++)
		{
			m->matrix_[i][j] = matrix_[i][j];
		}
	}
	return VarPtr(m);
}

VarPtr Matrix :: NumElems() const
{
	return VarPtr(new Scalar(rows_*cols_));
}

VarPtr Matrix :: Size() const
{
	Matrix* m = new Matrix(1, 2);
	(*(*m->matrix_)[1])[1] = rows_;
	(*(*m->matrix_)[1])[2] = cols_;
	return VarPtr(m);
}

VarPtr Matrix::Size(int dim) const
{
	if ((dim>2)||(dim<1))
	{
		throw BAD_INPUT;
	}
	return VarPtr(new Scalar(rows_*cols_));
}

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

VarPtr Matrix :: Transpose() const
{
	Matrix* m = new Matrix(cols_, rows_, 0);
	for (int i = 1; i < rows_ + 1; i++)
	{
		for (int j = 1; j < cols_ + 1; j++)
		{
			(*(*m->matrix_)[j])[i] = (*(*matrix_)[i])[j];
		}
	}
	return VarPtr(m);
}

const int& Matrix :: operator[](int idx) const
{
	if ((idx < 1) || (idx > rows_*cols_))
		throw (INDEX_OUT_OF_RANGE);
	int col = 1;
	while ((idx%rows_) > 1)
	{
		idx -= rows_;
		col++;
	}
	return (*(*matrix_)[idx])[col];
}

int& Matrix::operator[](IdxVec V) const
{
	if ((V.size() != 2) || (V[0]>rows_) || (V[0]<1) ||
		(V[1]>cols_) || (V[1]<1))
		throw(INDEX_OUT_OF_RANGE);
	return (*(*matrix_)[V[0]])[V[1]];
}

VarPtr Matrix::operator+(const Variable& V) const
{
	return (V+ *this);
}

VarPtr Matrix :: operator+(const Scalar& s)const
{
	Matrix* M = new Matrix(rows_,cols_,1);
	for (int i = 1; i < rows_ + 1; i++)
	{
		for (int j = 1; j < cols_ + 1; j++)
		{
			(*(*M->matrix_)[i])[j] = (*(*matrix_)[i])[j] + s.Value_;
		}
	}
	return VarPtr(M);
}

VarPtr Matrix::operator+(const Matrix& m)const
{
	if ((m.rows_ != rows_) || (m.cols_ != cols_))
		throw (BAD_MAT_DIMS("+"));
	Matrix* M = new Matrix(rows_,cols_,1);
	for (int i = 1; i < rows_ + 1; i++)
	{
		for (int j = 1; j < cols_ + 1; j++)
		{
			(*(*M->matrix_)[i])[j] = (*(*matrix_)[i])[j] + (*(*m.matrix_)[i])[j];
		}
	}
	return VarPtr(M);
}

VarPtr Matrix :: operator*(const Variable& V) const
{
	return (V * (*this));
}

VarPtr Matrix :: operator*(const Scalar& s) const
{
	Matrix* m = new Matrix(rows_,cols_,0);
	for (int i=1; 1 < m->rows_+1 ; i++)
	{
		for (int j=1; 1 < m->cols_+1 ; j++)
		{
			(*(*m->matrix_)[i])[j] = s.Value_*((*(*matrix_)[i])[j]);
		}
	}
	return VarPtr(m);
}

VarPtr Matrix :: operator*(const Matrix& m)const
{
	if (rows_!= m.cols_)
		throw(BAD_MAT_PROD);
	Matrix* M = new Matrix(rows_,m.cols_,1);
	for (int i=1; 1 < M->rows_+1 ; i++)
	{
		for (int j=1; 1 < M->cols_+1 ; j++)
		{
			int sum =0;
			for(int k=1; k < cols_+1 ; k++)
			{
				sum += ((*(*matrix_)[i])[k])*((*(*m.matrix_)[k])[j]);
			}
			(*(*M->matrix_)[i])[j] = sum;
		}
	}
	return VarPtr(M);
}

VarPtr Matrix :: operator<(const Variable& V)const
{
	return (V > *this);
}

VarPtr Matrix :: operator<(const Scalar& s)const
{
	Matrix* M = new Matrix(rows_,cols_,1);
	for (int i =1; i<rows_+1;i++)
	{
		for (int j =1; j<cols_+1;j++)
		{
			(*(*M->matrix_)[i])[j] = (*(*matrix_)[i])[j] < s.Value_;
		}
	}
	return VarPtr(M);
}

VarPtr Matrix :: operator<(const Matrix& m)const
{
	Matrix* M = new Matrix(rows_,cols_,0);
	if ((rows_!= m.rows_) || (cols_!=m.cols_))
		throw (BAD_MAT_DIMS(">/<"));
	for (int i =1; i<rows_+1;i++)
	{
		for (int j =1; j<cols_+1;j++)
		{
			(*(*M->matrix_)[i])[j] = (*(*matrix_)[i])[j] < (*(*m.matrix_)[i])[j];
		}
	}
	return VarPtr(M);
}

VarPtr Matrix :: operator>(const Variable& V)const
{
	return (V < *this);
}

VarPtr Matrix :: operator>(const Scalar& s)const
{
	Matrix* M = new Matrix(rows_,cols_,0);
	for (int i =1; i<rows_+1;i++)
	{
		for (int j =1; j<cols_+1;j++)
		{
			(*(*M->matrix_)[i])[j] = (*(*matrix_)[i])[j] > s.Value_;
		}
	}
	return VarPtr(M);
}

VarPtr Matrix :: operator>(const Matrix& m)const
{
	Matrix* M = new Matrix(rows_,cols_,0);
	if ((rows_!= M->rows_) || (cols_!=M->cols_))
		throw (BAD_MAT_DIMS(">/<"));
	for (int i =1; i<rows_+1;i++)
	{
		for (int j =1; j<cols_+1;j++)
		{
			(*(*M->matrix_)[i])[j] = (*(*matrix_)[i])[j] > (*(*m.matrix_)[i])[j];
		}
	}
	return VarPtr(M);
}

VarPtr Matrix :: operator==(const Variable& V)const
{
	return (V == *this);
}

VarPtr Matrix :: operator==(const Scalar& s)const
{
	Matrix* M = new Matrix(rows_,cols_,0);
	for (int i =1; i<rows_+1;i++)
	{
		for (int j =1; j<cols_+1;j++)
		{
			(*(*M->matrix_)[i])[j] = (*(*matrix_)[i])[j] == s.Value_;
		}
	}
	return VarPtr(M);
}

VarPtr Matrix :: operator==(const Matrix& m)const
{
	Matrix* M = new Matrix(rows_,cols_,0);
	if ((rows_!= m.rows_) || (cols_!=m.cols_))
		throw (BAD_MAT_DIMS("=="));
	for (int i =1; i<rows_+1;i++)
	{
		for (int j =1; j<cols_+1;j++)
		{
			(*(*M->matrix_)[i])[j] = (*(*matrix_)[i])[j] == (*(*m.matrix_)[i])[j];
		}
	}
	return VarPtr(M);
}

VarPtr Matrix :: operator&&(const Variable& V)const
{
	throw (BAD_INPUT);
}

VarPtr Matrix :: operator&&(const Scalar&)const
{
	throw (BAD_INPUT);
}

VarPtr Matrix :: operator&&(const Matrix&)const
{
	throw (BAD_INPUT);
}

VarPtr Matrix :: operator||(const Variable& V)const
{
	throw (BAD_INPUT);
}

VarPtr Matrix :: operator||(const Scalar&)const
{
	throw (BAD_INPUT);
}

VarPtr Matrix :: operator||(const Matrix&)const
{
	throw (BAD_INPUT);
}

ostream& Matrix::operator<<(ostream& ro)
{
	print(ro);
	return ro;
}

void Matrix::print(ostream& ro) const
{
		for (int i = 1; i < rows_ + 1; i++)
		{
			for (int j = 1; j < cols_ + 1; j++)
			{
				ro << (*(*matrix_)[i])[j] << " ";
			}
		
			ro << endl;
		}
}

//void Matrix :: operator << (const Variable&) const
//{
//	for (int i = 1; i < rows_ + 1; i++)
//	{
//		for (int j = 1; j < cols_ + 1; j++)
//		{
//			cout << (*(*matrix_)[i])[j] << " ";
//		}
//	
//		cout << endl;
//	}
//}

//void Matrix :: print(ostream& ro) const{
//	for (int i=0; i< rows_; i++){
//		for (int j=0; j<cols_; j++){
//			ro << (*(*matrix_)[i])[j] << '\t';
//		}
//		if (i!=rows_-1)
//			ro << '\n';
//	}
//}

