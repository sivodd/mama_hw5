#include"Commands.h"
#include"Scalar.h"
#include"Matrix.h"
#include"LineParser.h"
#include"ScriptExceptions.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>


void ReplaceCommandByTmpVar(string& tmpVarName, vector<string>& lineSegments, int firstVarIdx, int numVars);





Commands::Commands(VariablesMap& varMap) : firstVarIdx_(0), numVars_(0), varToAssign_(), varMap_(varMap)
{
	// Do nothing
}


void Commands::Execute(int comType, vector<string>& lineSegments, int firstVarIdx, int numVars, const string varToAssign)
{
	firstVarIdx_ = firstVarIdx;
	numVars_ = numVars;
	varToAssign_ = varToAssign;

	switch (comType)
	{
	case NUMEL:
		NumEl(lineSegments);
		break;
	case SIZE:
		Size(lineSegments);
		break;
	case CONV:
		Conv(lineSegments);
		break;
	case ZEROS:
		Zeros(lineSegments);
		break;
	case TRANSPOSE:
		Transpose(lineSegments);
		break;


	case SUBSCRIPT:
		if (varToAssign_.compare("") == 0)
			Subscript(lineSegments);
		else
			SubscriptAssignment(lineSegments);
		break;
	case PAREN:
		if (numVars != 1)
			throw SYNTAX_INCOMPLETE;
		break;


	case MULT:
		Mult(lineSegments);
		break;
	case ADD:
		Add(lineSegments);
		break;


	case LIN_VEC:
		LinVec(lineSegments);
		break;


	case LESS_THAN:
		LessThan(lineSegments);
		break;
	case EQUAL:
		Equal(lineSegments);
		break;


	case AND:
		And(lineSegments);
		break;
	case OR:
		Or(lineSegments);
		break;


	default:
		throw UNEXPECTED("Parser error - Unexpected command type.");
		break;
	}
}


void Commands::NumEl(vector<string>& lineSegments)
{
	string tmpVarName = varMap_.GetTmpVariable();
	if (numVars_ != 1)
		throw BAD_VAR_NUM;

	varMap_[tmpVarName] = varMap_.at(lineSegments[firstVarIdx_])->NumElems();
	ReplaceCommandByTmpVar(tmpVarName, lineSegments, firstVarIdx_, numVars_);
}



void Commands::Size(vector<string>& lineSegments)
{
	string tmpVarName = varMap_.GetTmpVariable();
	if (numVars_ < 1 && numVars_ > 2)
		throw BAD_VAR_NUM;
	if (numVars_ == 1)
		varMap_[tmpVarName] = varMap_.at(lineSegments[firstVarIdx_])->Size();
	else if (numVars_ == 2 && (*(varMap_.at(lineSegments[firstVarIdx_ + 1])->NumElems()))[1] == 1)
		varMap_[tmpVarName] = varMap_.at(lineSegments[firstVarIdx_])->Size((*(varMap_.at(lineSegments[firstVarIdx_ + 1])))[1]);
	else
		throw BAD_INPUT;
	ReplaceCommandByTmpVar(tmpVarName, lineSegments, firstVarIdx_, numVars_);
}



void Commands::Conv(vector<string>& lineSegments)
{
	string tmpVarName = varMap_.GetTmpVariable();
	if (numVars_ != 2)
		throw BAD_VAR_NUM;

	varMap_[tmpVarName] = varMap_.at(lineSegments[firstVarIdx_])->Conv(varMap_.at(lineSegments[firstVarIdx_ + 1]));
	ReplaceCommandByTmpVar(tmpVarName, lineSegments, firstVarIdx_, numVars_);
}



void Commands::Zeros(vector<string>& lineSegments)
{
	int rows, cols, numInputDims = 0;
	bool isValidVars = true;
	string tmpVarName = varMap_.GetTmpVariable();

	for (int ii = 0; ii < numVars_; ++ii)
	{
		int curVarLength = (*(varMap_.at(lineSegments[firstVarIdx_ + ii])->NumElems()))[1];
		numInputDims += curVarLength;
		if (curVarLength == 0)
			isValidVars = false;
	}

	if (isValidVars == false || numInputDims < 1 || numInputDims > 2)
		throw BAD_VAR_NUM;

	rows = (*varMap_.at(lineSegments[firstVarIdx_]))[1];
	cols = rows;
	if (numInputDims == 2)
	{
		if (numVars_ == 1)
			cols = (*varMap_.at(lineSegments[firstVarIdx_]))[2];
		else
			cols = (*varMap_.at(lineSegments[firstVarIdx_ + 1]))[1];
	}
	varMap_[tmpVarName] = VarPtr(new Matrix(rows, cols, 0));
	ReplaceCommandByTmpVar(tmpVarName, lineSegments, firstVarIdx_, numVars_);
}



void Commands::Transpose(vector<string>& lineSegments)
{
	string tmpVarName = varMap_.GetTmpVariable();
	if (numVars_ != 1)
		throw BAD_VAR_NUM;

	varMap_[tmpVarName] = varMap_.at(lineSegments[firstVarIdx_])->Transpose();
	ReplaceCommandByTmpVar(tmpVarName, lineSegments, firstVarIdx_, numVars_);
}



void Commands::Subscript(vector<string>& lineSegments)
{
	string tmpVarName = varMap_.GetTmpVariable();
	VarPtr res;
	if (numVars_ < 2 || numVars_ > 3)
		throw BAD_VAR_NUM;

	try
	{
		VarPtr var = varMap_.at(lineSegments[firstVarIdx_]);
		VarPtr idxVec1 = varMap_.at(lineSegments[firstVarIdx_ + 1]);

		if (numVars_ == 2)
		{
			VarPtr sizeVec1 = idxVec1->Size();
			res = VarPtr(new Matrix((*sizeVec1)[1], (*sizeVec1)[2], 0));
			for (int iIdx = 1; iIdx <= (*(idxVec1->NumElems()))[1]; ++iIdx)
				(*res)[iIdx] = (*var)[iIdx];
		}
		else // numVars == 3
		{
			VarPtr idxVec2 = varMap_.at(lineSegments[firstVarIdx_ + 2]);
			int numRows = (*(idxVec1->NumElems()))[1];
			int numCols = (*(idxVec2->NumElems()))[1];
			res = VarPtr(new Matrix(numRows, numCols, 0));
			for (int iRow = 1; iRow <= numRows; ++iRow)
			{
				IdxVec varIdx(2, (*idxVec1)[iRow]);
				IdxVec resIdx(2, iRow);
				for (int iCol = 1; iCol <= numCols; ++iCol)
				{
					varIdx[1] = (*idxVec2)[iCol];
					resIdx[1] = iCol;
					(*res)[resIdx] = (*var)[varIdx];
				}
			}
		}
	}
	catch (out_of_range&)
	{
		throw SYNTAX_UNDEFINED(lineSegments[firstVarIdx_]);
	}
	varMap_[tmpVarName] = res;
	ReplaceCommandByTmpVar(tmpVarName, lineSegments, firstVarIdx_, numVars_);
}



void Commands::SubscriptAssignment(vector<string>& lineSegments)
{
	VarPtr res;
	int lineSegmentsSize = lineSegments.size();
	if (numVars_ < 2 || numVars_ > 3)
		throw BAD_VAR_NUM;
	if (firstVarIdx_ > 0 || numVars_ < lineSegmentsSize)
		throw SYNTAX_INCOMPLETE;

	try
	{
		VarPtr lhs = varMap_.at(lineSegments[firstVarIdx_]);
		VarPtr rhs = varMap_.at(varToAssign_);
		VarPtr lhsCopy = lhs->Copy();
		VarPtr idxVec1 = varMap_.at(lineSegments[firstVarIdx_ + 1]);

		if (numVars_ == 2)
		{
			if ((*(rhs->NumElems()))[1] == 1)
				for (int iIdx = 1; iIdx <= (*(idxVec1->NumElems()))[1]; ++iIdx)
					(*lhsCopy)[(*idxVec1)[iIdx]] = (*rhs)[1];
			else
			{
				if ((*(idxVec1->NumElems()))[1] != (*(rhs->NumElems()))[1])
					throw SUBSCRIPT_MISMATCH;
				for (int iIdx = 1; iIdx <= (*(idxVec1->NumElems()))[1]; ++iIdx)
					(*lhsCopy)[(*idxVec1)[iIdx]] = (*rhs)[iIdx];
			}
		}
		else // numVars == 3
		{
			VarPtr idxVec2 = varMap_.at(lineSegments[firstVarIdx_ + 2]);
			int numRows = (*(idxVec1->NumElems()))[1];
			int numCols = (*(idxVec2->NumElems()))[1];
			if ((*(rhs->NumElems()))[1] == 1)
				for (int iRow = 1; iRow <= numRows; ++iRow)
				{
					IdxVec lhsIdx(2, (*idxVec1)[iRow]);
					for (int iCol = 1; iCol <= numCols; ++iCol)
					{
						lhsIdx[1] = (*idxVec2)[iCol];
						(*lhsCopy)[lhsIdx] = (*rhs)[1];
					}
				}
			else
			{
				VarPtr rhsSizeVec = rhs->Size();
				if ((*rhsSizeVec)[1] != numRows || (*rhsSizeVec)[2] != numCols)
					throw SUBSCRIPT_MISMATCH;
				for (int iRow = 1; iRow <= numRows; ++iRow)
				{
					IdxVec lhsIdx(2, (*idxVec1)[iRow]);
					IdxVec rhsIdx(2, iRow);
					for (int iCol = 1; iCol <= numCols; ++iCol)
					{
						lhsIdx[1] = (*idxVec2)[iCol];
						rhsIdx[1] = iCol;
						(*lhsCopy)[lhsIdx] = (*rhs)[rhsIdx];
					}
				}
			}
		}
		varMap_.at(lineSegments[firstVarIdx_]) = lhsCopy;
	}
	catch (out_of_range&)
	{
		throw SYNTAX_UNDEFINED(lineSegments[firstVarIdx_]);
	}
	ReplaceCommandByTmpVar(lineSegments[firstVarIdx_], lineSegments, firstVarIdx_, numVars_);
}


void Commands::Mult(vector<string>& lineSegments)
{
	string tmpVarName = varMap_.GetTmpVariable();
	if (numVars_ != 2)
		throw BAD_VAR_NUM;

	varMap_[tmpVarName] = (*varMap_.at(lineSegments[firstVarIdx_])) * (*varMap_.at(lineSegments[firstVarIdx_ + 1]));
	ReplaceCommandByTmpVar(tmpVarName, lineSegments, firstVarIdx_, numVars_);
}



void Commands::Add(vector<string>& lineSegments)
{
	string tmpVarName = varMap_.GetTmpVariable();
	if (numVars_ != 2)
		throw BAD_VAR_NUM;

	varMap_[tmpVarName] = (*varMap_.at(lineSegments[firstVarIdx_])) + (*varMap_.at(lineSegments[firstVarIdx_ + 1]));
	ReplaceCommandByTmpVar(tmpVarName, lineSegments, firstVarIdx_, numVars_);
}



void Commands::LinVec(vector<string>& lineSegments)
{
	int startVal, endVal;
	string tmpVarName = varMap_.GetTmpVariable();

	if (numVars_ != 2)
		throw BAD_VAR_NUM;
	if ((*(varMap_.at(lineSegments[firstVarIdx_])->NumElems()))[1] != 1 || (*(varMap_.at(lineSegments[firstVarIdx_ + 1])->NumElems()))[1] != 1)
		throw BAD_INPUT;

	startVal = (*varMap_.at(lineSegments[firstVarIdx_]))[1];
	endVal = (*varMap_.at(lineSegments[firstVarIdx_ + 1]))[1];
	varMap_[tmpVarName] = VarPtr(new Matrix(startVal, endVal));
	ReplaceCommandByTmpVar(tmpVarName, lineSegments, firstVarIdx_, numVars_);
}



void Commands::LessThan(vector<string>& lineSegments)
{
	string tmpVarName = varMap_.GetTmpVariable();
	if (numVars_ != 2)
		throw BAD_VAR_NUM;

	varMap_[tmpVarName] = (*varMap_.at(lineSegments[firstVarIdx_])) < (*varMap_.at(lineSegments[firstVarIdx_ + 1]));
	ReplaceCommandByTmpVar(tmpVarName, lineSegments, firstVarIdx_, numVars_);
}



void Commands::Equal(vector<string>& lineSegments)
{
	string tmpVarName = varMap_.GetTmpVariable();
	if (numVars_ != 2)
		throw BAD_VAR_NUM;

	varMap_[tmpVarName] = (*varMap_.at(lineSegments[firstVarIdx_])) == (*varMap_.at(lineSegments[firstVarIdx_ + 1]));
	ReplaceCommandByTmpVar(tmpVarName, lineSegments, firstVarIdx_, numVars_);
}



void Commands::And(vector<string>& lineSegments)
{
	string tmpVarName = varMap_.GetTmpVariable();
	if (numVars_ != 2)
		throw BAD_VAR_NUM;

	varMap_[tmpVarName] = (*varMap_.at(lineSegments[firstVarIdx_])) && (*varMap_.at(lineSegments[firstVarIdx_ + 1]));
	ReplaceCommandByTmpVar(tmpVarName, lineSegments, firstVarIdx_, numVars_);
}



void Commands::Or(vector<string>& lineSegments)
{
	string tmpVarName = varMap_.GetTmpVariable();
	if (numVars_ != 2)
		throw BAD_VAR_NUM;

	varMap_[tmpVarName] = (*varMap_.at(lineSegments[firstVarIdx_])) || (*varMap_.at(lineSegments[firstVarIdx_ + 1]));
	ReplaceCommandByTmpVar(tmpVarName, lineSegments, firstVarIdx_, numVars_);
}







void ReplaceCommandByTmpVar(string& tmpVarName, vector<string>& lineSegments, int firstVarIdx, int numVars)
{
	vector<string> tmpVec;
	for (int ii = 0; ii < firstVarIdx; ++ii)
		tmpVec.push_back(lineSegments[ii]);
	tmpVec.push_back(tmpVarName);
	for (unsigned int ii = firstVarIdx + numVars; ii < lineSegments.size(); ++ii)
		tmpVec.push_back(lineSegments[ii]);
	lineSegments = tmpVec;
}