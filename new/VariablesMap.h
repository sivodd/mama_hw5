#ifndef _VARIABLES_MAP_H_
#define _VARIABLES_MAP_H_

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <memory>
#include "Variable.h"
#include "Scalar.h"
#include "Matrix.h"

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

//these functions are for debugging with main_varmap.

//    string getsavedname(){
//        return savedName_;
//    };

//    void print_list(){
//        for (std::list<string>::iterator it = tmp_list.begin(); it != tmp_list.end(); ++it)
//            std::cout << ' ' << *it;
//
//        std::cout << '\n';
//    };
//
//    void print(){
//        for(map<string, VarPtr>::const_iterator it = VariablesMap_.begin();
//            it != VariablesMap_.end(); ++it)
//        {
//            std::cout << it->first << " " << "\n";
//        }
//    };

private:
    string savedName_;
    map<string, VarPtr>VariablesMap_;
    list<string>tmp_list;
};


#endif // _VARIABLES_MAP_H_
