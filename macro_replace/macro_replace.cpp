#include "macro_replace.h"
using namespace std;

vector<FuncParams> macro_replace(unordered_map<std::string,std::string> replacement,vector<FuncParams> orig){
    vector<FuncParams> tmpret;
    for(auto x:orig){
        if(x.is_literal == false && replacement.find(x.str) != replacement.end()){
            x.str = replacement.find(x.str)->second;
        }
        tmpret.push_back(x);
    }
    return tmpret;
}