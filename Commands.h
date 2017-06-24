#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include<string>
#include"VariablesMap.h"


#define NO_COMMAND -1

#define NUMEL 0
#define SIZE 1
#define CONV 2
#define ZEROS 3
#define TRANSPOSE 4

#define SUBSCRIPT 5
#define PAREN 6

#define MULT 7
#define ADD 8

#define LIN_VEC 9

#define LESS_THAN 10
#define EQUAL 11

#define AND 12
#define OR 13


class Commands
{
public:
	Commands(VariablesMap& varMap);
	void Execute(int comType, vector<string>& lineSegments, int firstVarIdx, int numVars, const string varToAssign);
private:
	void NumEl(vector<string>& lineSegments);
	void Size(vector<string>& lineSegments);
	void Conv(vector<string>& lineSegments);
	void Zeros(vector<string>& lineSegments);
	void Transpose(vector<string>& lineSegments);
	void Subscript(vector<string>& lineSegments);
	void SubscriptAssignment(vector<string>& lineSegments);
	void Mult(vector<string>& lineSegments);
	void Add(vector<string>& lineSegments);
	void LinVec(vector<string>& lineSegments);
	void LessThan(vector<string>& lineSegments);
	void Equal(vector<string>& lineSegments);
	void And(vector<string>& lineSegments);
	void Or(vector<string>& lineSegments);

	int firstVarIdx_;
	int numVars_;
	string varToAssign_;
	VariablesMap& varMap_;
};


#endif // _COMMANDS_H_
