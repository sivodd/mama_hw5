#ifndef _VARIABLES_MAP_H_
#define _VARIABLES_MAP_H_

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "Variable.h"
using namespace std;


#define VALID_VAR_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"
typedef auto_ptr<Variable> p1 (new Variable);
class VariablesMap {
public:
    VariablesMap();
    ~VariablesMap(){string.~string();};// i think string doesn't need to be deleted because it's destructor is automatically called
    void SetSavedName(const string& newSavedName);
    char* GetTmpVariable();
    void ClearTmpVars();
    variable& operator[](const string& x);
    variable& at(const string& x);
    void erase(const string& x);

private:
    string savedName_;
};


#endif // _VARIABLES_MAP_H_
