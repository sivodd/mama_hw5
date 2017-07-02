#include"VariablesMap.h"
#include"ScriptExceptions.h"
#include <ctime>

using namespace std;

VariablesMap::VariablesMap() {
    VariablesMap_.clear();
    string saved_name("");
    savedName_=saved_name;
}


void VariablesMap::SetSavedName(const string& newSavedName){
    if (!newSavedName.empty())//(newSavedName!=NULL)
        savedName_=newSavedName;
}

string VariablesMap::GetTmpVariable(){
    srand((unsigned)time(0)); // use current time as seed for random generator
    string s= VALID_VAR_CHARS;
    int floor = 0, ceiling = int(s.length()), range = (ceiling - floor);
    string tmp("a");
//  while tmp is already in the map or the saved name continue looking for a key.
    while ((VariablesMap_.find(tmp) != VariablesMap_.end()) || (tmp==savedName_))
	{
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
			VariablesMap_[x] = NULL;
            return (VariablesMap_[x]);
        }
    }
    throw (INVALID_VAR_NAME(x));
}

VarPtr& VariablesMap::at(const string& x){
    return VariablesMap_.at(x);
}

void VariablesMap::erase(const string& x){
    VariablesMap_.erase(x);
    if (find(tmp_list.begin(), tmp_list.end(), x) != tmp_list.end())//לפי האינטרנט זה לא בודק את האיבר האחרון (שלend)
        tmp_list.remove(x);//need to erase tmp from list if it exists.
}






