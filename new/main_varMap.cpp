#include<iostream>
#include"MamatScriptEngine.h"

using namespace std;



int main() {
    VariablesMap varMap;
    cout << varMap.getsavedname() << endl;
    varMap.SetSavedName("sivan");
    cout << varMap.getsavedname() <<endl;
    cout << varMap.GetTmpVariable()<<endl;
    cout << varMap.GetTmpVariable()<<endl;
    cout << varMap.GetTmpVariable()<<endl;
    varMap["aa"];
    try {
        varMap["1a"];
    }
    catch (const exception& e)
    {
        cout << e.what() << endl;
    }
    varMap.print_list();
    varMap.print();

    return 0;
};