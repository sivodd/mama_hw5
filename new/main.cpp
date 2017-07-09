#define _CRTDBG_MAP_ALLOC
#include<iostream>
#include <crtdbg.h>
#ifdef _DEBUG
	#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define new DEBUG_NEW
#endif

#include<iostream>
#include"MamatScriptEngine.h"

using namespace std;


int main() {
    VariablesMap varMap;
    MamatScriptEngine mmtEng(cin, varMap);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    while (!cin.eof())
    {
        try
        {
            mmtEng.Execute();
        }
        catch (const exception& e)
        {
            cout << e.what() << endl;
        }
        catch (...)
        {
            cout << "Unexpected Error" << endl;
            return 1;
        }
    }
	_CrtDumpMemoryLeaks();
    return 0;
};