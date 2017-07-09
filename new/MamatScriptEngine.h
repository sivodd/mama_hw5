#ifndef _MAMAT_SCRIPT_ENGINE_H_
#define _MAMAT_SCRIPT_ENGINE_H_

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>

#include<istream>
#include<sstream>
#include<string>
#include"VariablesMap.h"
#include"LineParser.h"
using namespace std;


class MamatScriptEngine
{
public:
	MamatScriptEngine(istream& is, VariablesMap& varMap) : is_(is), varMap_(varMap), parser_(varMap) {};
	void Execute();
private:
	istream& is_;
	VariablesMap& varMap_;
	LineParser parser_;
};


#endif // _MAMAT_SCRIPT_ENGINE_H_



