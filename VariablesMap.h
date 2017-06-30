#ifndef _VARIABLES_MAP_H_
#define _VARIABLES_MAP_H_

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <memory>
#include "Variable.h"
using namespace std;


#define VALID_VAR_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

class VariablesMap {
public:
    VariablesMap();
    ~VariablesMap(){};//string.~string();};// i think string doesn't need to be deleted because it's destructor is automatically called
    void SetSavedName(const string& newSavedName);
    string GetTmpVariable();
    void ClearTmpVars();
    VarPtr& operator[](const string& x);
    VarPtr& at(const string& x);
    void erase(const string& x);

private:
    string savedName_;
    map<string, VarPtr>VariablesMap_;
    list<string>tmp_list;
};


#endif // _VARIABLES_MAP_H_
