#include<iostream>
#include"Variable.h"
#include"ScriptExceptions.h"

using namespace std;


//from staff
IdxVec operator+(const IdxVec& lhs, const IdxVec& rhs)
{
	if (lhs.size() != rhs.size())
		throw ScriptException("IdxVec operator+, vector sizes mismatch.");
	IdxVec res = lhs;
	int resSize = int(res.size());//put int on res.size
	for (int ii = 0;ii < resSize;++ii)
		res[ii] += rhs[ii];
	return res;
}

// *************************************************************************************
//* Function name : Operator <<
//* Description   : Overloads operator <<.
//* Parameters    : Ostream& ro - reference to ostream.
//*             	VarPtr& VarP - reference to Variable to print
//* Return value  : ostream& - ostream reference to print Variable.
//*************************************************************************************
ostream& operator<<(ostream& ro, const VarPtr& var_ptr){
	var_ptr.get()->print(ro);
	return ro;
}