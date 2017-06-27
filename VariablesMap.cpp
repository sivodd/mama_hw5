#include"VariablesMap.h"
#include"ScriptExceptions.h"

using namespace std;

VariablesMap::VariablesMap(): {
    VariablesMap_.clear();
    string saved_name("");
    savedName_=saved_name;
};


void VariablesMap::SetSavedName(const string& newSavedName){
    if (newSavedName!=NULL)
        savedName_=newSavedName;
}

string VariablesMap::GetTmpVariable(){
    srand((unsigned)time(0)); // use current time as seed for random generator
    string s= VALID_VAR_CHARS;
    int floor = 0, ceiling = int(s.length()), range = (ceiling - floor);
    string tmp("a");
    while (VariablesMap_.find(tmp) == VariablesMap_.end()){
        int rnd = floor + int((range * rand()) / (RAND_MAX + 1.0));
        tmp= s[rnd] + tmp;
    }
    VariablesMap_[tmp]=NULL;// WE ADD THE TMP THAT WE FOUND TO THE MAP
    tmp_list.push_back(tmp);
    return tmp;
}

void VariablesMap::ClearTmpVars(){
    while (!tmp_list.empty())
    {
        string tmp;
        tmp = tmp_list.front();
        VariablesMap_.erase(tmp);
        tmp_list.pop_front();
    }
}
VarPtr& VariablesMap::operator[](const string& x){
    bool flag= true;
    string s=VALID_VAR_CHARS;
    if (isalpha(x[0])){
        for (int i=1; i<x.length(); i++){
            if (s.find(x[i])==string::npos) {
                flag=false;
                break;
            }
        }
        if (flag){
            return VariablesMap_[x]= NULL;//NOT SURE
        }
    }
    throw (INVALID_VAR_NAME(x));
}
VarPtr& VariablesMap::at(const string& x){
    return VariablesMap_.at(x);
}

void VariablesMap::erase(const string& x){
    VariablesMap_.erase(x);
    tmp_list.erase(tmp);//need to erase tmp from list if it exists.
}






