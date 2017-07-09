#include<iostream>
#include"MamatScriptEngine.h"

using namespace std;


int main() {
    VariablesMap varMap;
    MamatScriptEngine mmtEng(cin, varMap);
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
    return 0;
};