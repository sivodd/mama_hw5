#include<iostream>
#include"Variable.h"
#include"ScriptExceptions.h"

using namespace std;

Variable::Variable() {};
Variable::~Variable() {};

IdxVec operator+(const IdxVec& lhs, const IdxVec& rhs)
{
	if (lhs.size() != rhs.size())
		throw ScriptException("IdxVec operator+, vector sizes mismatch.");
	IdxVec res = lhs;
	int resSize = res.size();
	for (int ii = 0;ii < resSize;++ii)
		res[ii] += rhs[ii];
	return res;
}

ostream& operator<<(ostream& ro, const VarPtr& varPtr){
	varPtr.get()->print(ro);
	return ro;
}


