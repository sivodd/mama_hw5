#include"VariablesMap.h"
#include"ScriptExceptions.h"
#include <string>
#include <string.h>

using namespace std;
map<string, Variable>VarMap;

VariablesMap::VariablesMap(): {
//    map<string, VarPtr>VarMap; //not sure this should be varptr maybe just variable*
    VarMap.clear();
    string saved_name("");
    savedName_=saved_name;


};


void VariablesMap::SetSavedName(const string& newSavedName){
    if (newSavedName!=NULL)
    savedName_=newSavedName;
}

char* VariablesMap::GetTmpVariable(){}

void VariablesMap::ClearTmpVars(){

}
Variable& VariablesMap::operator[](const string& x){
    bool flag= true;
    string s=VALID_VAR_CHARS;
    auto_ptr < Variable > p_var(new Variable);
    if (isalpha(x[0])){
        for (int i=1; i<x.length(); i++){
            if (s.find(x[i])==string::npos) {
                flag=false;
                break;
            }
        }
        if (flag){
            p_var=NULL;
            return VarMap[string(x)]=p_var;
        }
    }
    throw (INVALID_VAR_NAME(x));
}
Variable& VariablesMap::at(const string& x){
    return VarMap.at(x);
}

void VariablesMap::erase(const string& x);






