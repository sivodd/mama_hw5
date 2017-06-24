#include"Matrix.h"
#include"ScriptExceptions.h"

Matrix ::Matrix(int rows, int cols, int val) :
	Variable(), Row_(rows), Col_(cols)
{
	matrix_ = new IdxVec(rows);
	for (int i = 1; i < rows + 1; i++)
	{
		matrix_[i] = new IdxVec(cols);
		for (int j = 1; j < cols+1; j++)
		{
			matrix_[i][j] = val;
		}
	}
}



//Matrix::Matrix(int startVal, int endVal) :
//	Variable(), Row_(1), Col_(endVal - startVal+1)
//{
//	matrix_ = new IdxVec(Col_);
//	for (int i = 1; i < Col_ + 1; i++)
//	{
//		matrix_[i] = startVal + i - 1;
//	}
//}

VarPtr Copy()
{
	Matrix* m = new Matrix(matrix_);
	return VarPtr(m);
}

int NumElems()
{
	return Scalar(Row_*Col_);
}

Matrix Size()
{
	Matrix m = new Matrix(1, 2);
	m.matrix_[1][2] = 2;
	return m;
}

VarPtr Transpose()
{
	Matrix m = new Matrix(Col_, Row_, 0);
	for (int i = 1; i < Row_ + 1; i++)
	{
		for (int j = 1; j < Col_ + 1; J++)
		{
			m[j][i] = matrix_[i][j]
		}
	}
	return m;
}

int& operator[](int idx)
{
	if ((idx < 1) || (idx < this.size))
		throw (INDEX_OUT_OF_RANGE);
	int col = 1;
	while ((idx%Row_) > 1)
	{
		idx -= Row_;
		col++;
	}
	return matrix[idx][col];	
}

int& operator[](IdxVec V)
{
	if ((V.size != 2) || (V[0]>Row_) || (V[0]<1) ||
		(V[1]>Col_) || (V[1]<1))
	{
		throw(INDEX_OUT_OF_RANGE);
	}
	return matrix[V[0]][V[1]];
}

VarPtr operator+(const Variable&)
{
	return 0;
}

VarPtr operator+(const Scalar& s)
{
	for (int i = 1; i < Row_ + 1; i++)
	{
		for (int j = 1; j < Col_ + 1; J++)
		{
			matrix_[i][j] += s;
		}
	}
	return VarPtr(this);
}

VarPtr operator+(const Matrix& m)
{
	if ((m.Row_ != Row_) || (m.Col_ != Col_))
		throw (BAD_MAT_DIMS);
	for (int i = 1; i < Row_ + 1; i++)
	{
		for (int j = 1; j < Col_ + 1; J++)
		{
			matrix_[i][j] += m.matrix_[i][j];
		}
	}
	return VarPtr(this);
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