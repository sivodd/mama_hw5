#ifndef _LINE_PARSER_H_
#define _LINE_PARSER_H_


#include<string>
#include"VariablesMap.h"
#include"Commands.h"

#define BLANK_SPACES " \t\n\r"

class LineParser
{
public:
	LineParser(VariablesMap& varMap);
	VarPtr ReadLoopParameters(string line, string& forVarName);
	bool TestIfClause(string line);
	void ParseAssignment(string line);
	void ParseDisplay(string line);
private:
	void ParseLine(string& line, string varToAssign="");

	Commands comms_;
	VariablesMap& varMap_;
};


#endif // _LINE_PARSER_H_
