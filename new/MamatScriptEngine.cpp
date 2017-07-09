#include<string.h>
#include<iostream>
#include"MamatScriptEngine.h"
#include"ScriptExceptions.h"


#define BLANK_LINE 0
#define FOR_LOOP 1
#define IF_CLAUSE 2
#define ASSIGNMENT 3
#define DISP 4
#define END_BLOCK 5
#define ERROR 6

using namespace std;


int ParseCommandType(string line);
void GetBlock(istream& is_, stringstream& curBlock);




void MamatScriptEngine::Execute()
{
	VarPtr loopVec;
	string line, forVarName;
	int type, numLoopIters;
	while (!is_.eof())
	{
		getline(is_, line);
		type = ParseCommandType(line);
		if (type == BLANK_LINE)
		{
			continue;
		}
		else if (type == FOR_LOOP)
		{
			stringstream forBlock;
			GetBlock(is_, forBlock);
			loopVec = parser_.ReadLoopParameters(line, forVarName);
			numLoopIters = (*(loopVec->NumElems()))[1];
			for (int iIter = 1; iIter <= numLoopIters; ++iIter)
			{
				stringstream curBlock(forBlock.str());
				(*varMap_[forVarName])[1] = (*loopVec)[iIter];
				MamatScriptEngine RunForBlock(curBlock, varMap_);
				RunForBlock.Execute();
			}
		}
		else if (type == IF_CLAUSE)
		{
			stringstream curBlock;
			GetBlock(is_, curBlock);
			if (parser_.TestIfClause(line) == true)
			{
				MamatScriptEngine RunIfBlock(curBlock, varMap_);
				RunIfBlock.Execute();
			}
		}
		else if (type == ASSIGNMENT)
		{
			parser_.ParseAssignment(line);
		}
		else if (type == DISP)
		{
			parser_.ParseDisplay(line);
		}
		else
		{
			throw SYNTAX_INCOMPLETE;
		}
	}
}






int ParseCommandType(string line)
{
	int idx, firstCharIdx = line.find_first_not_of(BLANK_SPACES);
	if (firstCharIdx == (int)string::npos)
	{
		return BLANK_LINE;
	}

	if (line.find("for ") == (size_t)firstCharIdx) // execute for loop
	{
		idx = line.find_first_not_of(BLANK_SPACES, firstCharIdx + strlen("for"));
		if (idx != (int)string::npos && line[idx] != '=')
			return FOR_LOOP;
	}

	if (line.find("if") == (size_t)firstCharIdx) // excecute if clause
	{
		idx = line.find_first_not_of(BLANK_SPACES, firstCharIdx + strlen("if"));
		if (idx != (int)string::npos && line[idx] != '=' && (idx - firstCharIdx > (int)strlen("if") || line[idx] == '('))
			return IF_CLAUSE;
	}

	if (line.find("end") == (size_t)firstCharIdx) // end block
	{
		if (line.find_first_not_of(BLANK_SPACES, firstCharIdx + strlen("end")) == string::npos)
			return END_BLOCK;
	}

	if (line.find("=") != string::npos) // assignment
	{
		return ASSIGNMENT;
	}

	if (line.find("disp ") == (size_t)firstCharIdx) // display variable
	{
		idx = line.find_first_not_of(BLANK_SPACES, firstCharIdx + strlen("disp"));
		if (idx != (int)string::npos && line[idx] != '=')
			return DISP;
	}
	// error
	return ERROR;
}






void GetBlock(istream& is_, stringstream& curBlock)
{
	string line;
	int type,blockNum = 1;
	while (!is_.eof())
	{
		getline(is_, line);
		type = ParseCommandType(line);
		if (type == FOR_LOOP || type == IF_CLAUSE)
		{
			++blockNum;
		}
		else if (type == END_BLOCK)
		{
			--blockNum;
		}
		else if (type == ERROR)
		{
			throw SYNTAX_INCOMPLETE;
		}
		if (blockNum > 0)
			curBlock << line << endl;
		else
			return;
	}
	throw MISSING_BLOCK_END;
}