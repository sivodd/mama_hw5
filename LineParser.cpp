#include<string.h>
#include"LineParser.h"
#include"Scalar.h"
#include"Matrix.h"
#include"ScriptExceptions.h"



int ParseSingleCommand(const string& line, vector<string>& lineSegments, int& firstVarIdx, int& numVars);
bool ParseFunction(const char* commName, const string& line, vector<string>& lineSegments, int& firstVarIdx, int& numVars);
int ParseSubscriptOrParen(const string& line, vector<string>& lineSegments, int& firstVarIdx, int& numVars);
bool ParseBinaryOp(const char* commName, const string& line, vector<string>& lineSegments, int& firstVarIdx, int& numVars);
string& RemoveBlankSpaces(string& str);










LineParser::LineParser(VariablesMap& varMap) :  comms_(varMap), varMap_(varMap)
{
	// Do nothing
}



VarPtr LineParser::ReadLoopParameters(string line, string& forVarName)
{
	// Parse For variable name
	int firstCharIdx = line.find_first_not_of(BLANK_SPACES) + strlen("for");
	int eqSignIdx = line.find_first_of("=");
	if (eqSignIdx == (int)string::npos)
		throw SYNTAX_INCOMPLETE;
	forVarName = (line.substr(firstCharIdx, eqSignIdx - firstCharIdx));
	RemoveBlankSpaces(forVarName);
	
	// Parse For vector
	line = line.substr(eqSignIdx + 1);
	varMap_.SetSavedName(forVarName);
	ParseLine(line);

	// Clear tmp variables (first saving the for loop vector)
	VarPtr res = varMap_.at(line);
	varMap_.ClearTmpVars();

	// Create for variable
	varMap_[forVarName] = VarPtr(new Scalar(1));

	// Return For vector (as shared_pointer)
	return res;
}



bool LineParser::TestIfClause(string line)
{
	// Parse out if condition
	int firstCharIdx = line.find_first_not_of(BLANK_SPACES) + strlen("if");
	line = line.substr(firstCharIdx);
	ParseLine(line);

	// Clear tmp variables (first saving the if condition result)
	VarPtr res = varMap_.at(line);
	varMap_.ClearTmpVars();

	// Return if condition result
	if ((*(res->NumElems()))[1] == 0)
		return false;

	for (int ii = 0; ii < (*(res->NumElems()))[1]; ++ii)
		if ((*res)[ii + 1] == 0)
			return false;

	return true;
}



void LineParser::ParseAssignment(string line)
{
	// Parse left hand side of assignment
	int eqSignIdx = line.find_first_of("=");
	string varName = (line.substr(0, eqSignIdx));
	RemoveBlankSpaces(varName);
	
	// Parse right hand side of assignment
	line = line.substr(eqSignIdx + 1);
	varMap_.SetSavedName(varName);
	ParseLine(line);

	// Assign
	try
	{
		varMap_[varName] = varMap_.at(line);
	}
	catch (ScriptException&)
	{
		if (varName.find("(") == string::npos)
			throw;
		ParseLine(varName, line);
	}

	// Clear tmp variables
	varMap_.ClearTmpVars();

}



void LineParser::ParseDisplay(string line)
{
	int firstCharIdx = line.find_first_not_of(BLANK_SPACES) + strlen("disp");
	line = (line.substr(firstCharIdx));
	RemoveBlankSpaces(line);
	
	try
	{
		varMap_.at(line);
		cout << line << " =" << endl;
		cout << varMap_.at(line) << endl;
	}
	catch (out_of_range&)
	{
		throw SYNTAX_UNDEFINED(line);
	}
}







void LineParser::ParseLine(string& line, string varToAssign)
{
	int comType, firstVarIdx, numVars;
	size_t numCharsProcessed;
	vector<string> lineSegments;
	string tmpLine;

	RemoveBlankSpaces(line);
	while ((comType = ParseSingleCommand(line, lineSegments, firstVarIdx, numVars)) != NO_COMMAND)
	{
		// Parse Variables
		for (int iVar = 0; iVar < numVars; ++iVar)
			ParseLine(lineSegments[firstVarIdx+iVar]);

		// Execute command
		comms_.Execute(comType, lineSegments, firstVarIdx, numVars, varToAssign);

		// Update line after command parsing
		line.clear();
		for (int ii = 0; ii < (int)lineSegments.size(); ++ii)
		{
			line += lineSegments[ii];
			line += " ";
		}
		lineSegments.clear();
		RemoveBlankSpaces(line);
	}

	// Check if line is a variable name
	try
	{
		varMap_.at(line);
	}
	catch (out_of_range&) // If not then try to convert line to IntScalar variable
	{
		try
		{
			int num = stoi(line, &numCharsProcessed);
			if (numCharsProcessed == line.length())
			{
				string tmpVarName = varMap_.GetTmpVariable();
				varMap_[tmpVarName] = VarPtr(new Scalar(num));
				line = tmpVarName;
			}
			else
				throw SYNTAX_UNDEFINED(line);
		}
		catch (...)
		{
			throw SYNTAX_UNDEFINED(line);
		}
		
	}
}









int ParseSingleCommand(const string& line, vector<string>& lineSegments, int& firstVarIdx, int& numVars)
{
	// NUMEL
	if (ParseFunction("numel(", line, lineSegments, firstVarIdx, numVars) == true)
		return NUMEL;

	// SIZE
	if (ParseFunction("size(", line, lineSegments, firstVarIdx, numVars) == true)
		return SIZE;

	// CONV
	if (ParseFunction("conv(", line, lineSegments, firstVarIdx, numVars) == true)
		return CONV;

	// ZEROS
	if (ParseFunction("zeros(", line, lineSegments, firstVarIdx, numVars) == true)
		return ZEROS;

	// TRANSPOSE
	if (ParseFunction("transpose(", line, lineSegments, firstVarIdx, numVars) == true)
		return TRANSPOSE;

	//PAREN or SUBSCRIPT
	int res = ParseSubscriptOrParen(line, lineSegments, firstVarIdx, numVars);
	if (res == PAREN || res == SUBSCRIPT)
		return res;
	

	
	// MULT
	if (ParseBinaryOp("*", line, lineSegments, firstVarIdx, numVars) == true)
		return MULT;

	// ADD
	if (ParseBinaryOp("+", line, lineSegments, firstVarIdx, numVars) == true)
		return ADD;

	// LIN_VEC
	if (ParseBinaryOp(":", line, lineSegments, firstVarIdx, numVars) == true)
		return LIN_VEC;

	// LESS_THAN
	if (ParseBinaryOp("<", line, lineSegments, firstVarIdx, numVars) == true)
		return LESS_THAN;

	// EQUAL
	if (ParseBinaryOp("==", line, lineSegments, firstVarIdx, numVars) == true)
		return EQUAL;

	// AND
	if (ParseBinaryOp("&&", line, lineSegments, firstVarIdx, numVars) == true)
		return AND;

	// OR
	if (ParseBinaryOp("||", line, lineSegments, firstVarIdx, numVars) == true)
		return OR;


	return NO_COMMAND;
}








bool ParseFunction(const char* commName, const string& line, vector<string>& lineSegments, int& firstVarIdx, int& numVars)
{
	int pos, prePos, varStart, varEnd;
	int parenCount = 1;

	pos = line.find(commName);
	if (pos != (int)string::npos) // command possibly found
	{
		prePos = line.find_last_not_of(VALID_VAR_CHARS, pos);
		if (pos == 0 || prePos == pos - 1) // command found
		{
			if (pos > 0) // save line up to command location
			{
				firstVarIdx = 1;
				lineSegments.push_back(line.substr(0, pos));
			}
			else // command at start of line
				firstVarIdx = 0;

			// Parse command variables
			numVars = 0;
			varStart = pos + strlen(commName);
			varEnd = varStart;
			while (parenCount > 0)
			{
				if (varEnd >= (int)line.length())
					throw SYNTAX_UNBALANCED;

				if (parenCount == 1 && (line[varEnd] == ',' || line[varEnd] == ')'))
				{
					numVars++;
					lineSegments.push_back(line.substr(varStart, varEnd - varStart));
					varStart = varEnd + 1;
				}
				if (line[varEnd] == '(')
					parenCount++;
				if (line[varEnd] == ')')
					parenCount--;

				varEnd++;
			}
			if(varEnd < (int)line.length()) // save line after command
				lineSegments.push_back(line.substr(varEnd));

			return true;
		}
	}
	return false;
}







int ParseSubscriptOrParen(const string& line, vector<string>& lineSegments, int& firstVarIdx, int& numVars)
{
	int res = NO_COMMAND;
	int pos, prePos, varStart, varEnd;
	int parenCount = 1;
	
	pos = line.find("(");
	if (pos != (int)string::npos) // subscript or paren found
	{
		if (pos == 0 || line.substr(pos - 1, 1).find_first_of(VALID_VAR_CHARS) == string::npos) // if at start of line or next to variable character
			res = PAREN;
		else
			res = SUBSCRIPT;

		if (res == PAREN)
		{
			numVars = 0;
			if (pos == 0)
				firstVarIdx = 0;
			else
			{
				firstVarIdx = 1;
				lineSegments.push_back(line.substr(0, pos));
			}
		}
		else // SUBSCRIPT
		{
			numVars = 1;
			prePos = line.find_last_not_of(VALID_VAR_CHARS, pos-1);
			if (prePos != (int)string::npos)
			{
				firstVarIdx = 1;
				lineSegments.push_back(line.substr(0, prePos + 1));
				lineSegments.push_back(line.substr(prePos + 1, (pos - prePos) - 1));
			}
			else // command at start of line
			{
				firstVarIdx = 0;
				lineSegments.push_back(line.substr(0, pos));
			}
		}

		// Parse command variables
		varStart = pos + strlen("(");
		varEnd = varStart;
		while (parenCount > 0)
		{
			if (varEnd >= (int)line.length())
				throw SYNTAX_UNBALANCED;

			if (parenCount == 1 && (line[varEnd] == ',' || line[varEnd] == ')'))
			{
				numVars++;
				lineSegments.push_back(line.substr(varStart, varEnd - varStart));
				varStart = varEnd + 1;
			}
			if (line[varEnd] == '(')
				parenCount++;
			if (line[varEnd] == ')')
				parenCount--;

			varEnd++;
		}
		if (varEnd < (int)line.length()) // save line after command
			lineSegments.push_back(line.substr(varEnd));
	}
	return res;
}




bool ParseBinaryOp(const char* commName, const string& line, vector<string>& lineSegments, int& firstVarIdx, int& numVars)
{
	int opPos, bfrOpPos, aftrOpPos, pos1, pos2, pos3, pos4;
	
	opPos = line.find(commName);
	bfrOpPos = opPos - 1;
	aftrOpPos = opPos + strlen(commName);
	if (opPos != (int)string::npos) // operator found
	{
		numVars = 2;

		if (bfrOpPos < 0 || aftrOpPos >= (int)line.length()) //if missing variable
			throw MISSING_VAR;

		// Get left hand side variable
		pos2 = line.find_last_of(VALID_VAR_CHARS, bfrOpPos);
		if (pos2 == (int)string::npos || (bfrOpPos - pos2 > 0 && line.substr(pos2 + 1, bfrOpPos - pos2).find_first_not_of(BLANK_SPACES) != string::npos)) // if missing variable
			throw MISSING_VAR;
		pos1 = line.find_last_not_of(VALID_VAR_CHARS, pos2);
		if (pos1 == (int)string::npos || (pos1 == 0 && line[pos1] == '-') ) // if line starts with lhs var
		{
			firstVarIdx = 0;
			lineSegments.push_back(line.substr(0, pos2 + 1));
		}
		else
		{
			if (line[pos1] == '-')
				pos1--;
			firstVarIdx = 1;
			lineSegments.push_back(line.substr(0, pos1 + 1));
			lineSegments.push_back(line.substr(pos1+1, pos2 - pos1));
		}

		// Get right hand side variable
		pos3 = line.find_first_of(VALID_VAR_CHARS, aftrOpPos);
		if (pos3 == (int)string::npos) //if missing variable
			throw MISSING_VAR;
		pos4 = line.find_first_not_of(VALID_VAR_CHARS, pos3);
		if (line[pos3-1] == '-')
			pos3--;
		if (pos3 - aftrOpPos > 0 && line.substr(aftrOpPos, pos3 - aftrOpPos).find_first_not_of(BLANK_SPACES) != string::npos) // if missing variable
			throw MISSING_VAR;
		if (pos4 == (int)string::npos) // if line starts with lhs var
		{
			lineSegments.push_back(line.substr(pos3));
		}
		else
		{
			lineSegments.push_back(line.substr(pos3, pos4 - pos3));
			lineSegments.push_back(line.substr(pos4));
		}

		return true;
	}
	return false;
}





string& RemoveBlankSpaces(string& str)
{
	int startCharIdx = str.find_first_not_of(BLANK_SPACES);
	int endCharIdx = str.find_last_not_of(BLANK_SPACES);
	if (startCharIdx == (int)string::npos)
		str.clear();
	else
		str = str.substr(startCharIdx, endCharIdx - startCharIdx + 1);
	return str;
}