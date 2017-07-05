#include<iostream>
#include"MamatScriptEngine.h"
#include "ScriptExceptions.h"

using namespace std;



int main() {
    try {
        throw SYNTAX_UNBALANCED;
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
    return 0;
};

