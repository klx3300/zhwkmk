#include "functions.h"
#include <iostream>
#include "../stroper/stroper.h"

using namespace std;

void mkMacro(std::unordered_map<std::string,std::string>& replacement,
    std::vector<std::string>& func_params){
    if(func_params[0]!="macro"){
        cerr << "[INTR] Internal control flow error while trying execute " << func_params[0] << " as macro()." << endl;
        return;
    }
    if(func_params.size() !=3 ){
        cerr << "[FAIL] Passing " << func_params.size()-1 << " parameter(s) to macro(), which expects 2." << endl;
        return;
    }
    replacement[func_params[1]]=func_params[2];
}

void mkConcat(std::unordered_map<std::string,std::string>& replacement,
    std::vector<std::string>& func_params){
    if(func_params[0] != "concat"){
        cerr << "[INTR] Internal control flow error while trying execute " << func_params[0] << " as concat()" << endl;
        return;
    }
    if(func_params.size() < 3){
        cerr << "[FAIL] Passing " << func_params.size()-1 << " parameter(s) to concat(), which expects at least 2." << endl;
        return;
    }
    string tmpstr;
    for(int i=2;i<func_params.size();i++){
        tmpstr+=func_params[i];
    }
    replacement[func_params[1]] = tmpstr;
}

void mkEval(std::unordered_map<std::string,std::string>& replacement,
    std::vector<std::string>& func_params){
    if(func_params[0] != "eval"){
        cerr << "[INTR] Internal control flow error while trying execute " << func_params[0] << " as eval()." << endl;
        return;
    }
    if(func_params.size() != 3){
        cerr << "[FAIL] Passing " <<func_params.size()-1 << " parameter(s) to eval(), which expects 2." << endl;
        return;
    }
    // TODO: Implement the eval()
}

void mkCC(std::string& destcc,std::vector<std::string>& func_params){
    if(func_params[0] != "cc"){
        cerr << "[INTR] Internal control flow error while trying execute " << func_params[0] << " as cc()." << endl;
        return;
    }
    if(func_params.size() != 2){
        cerr << "[FAIL] Passing " << func_params.size() -1 << " parameter(s) to cc(), which expects 1." << endl;
        return;
    }
    destcc = func_params[1];
}
void mkCXX(std::string& destcxx,std::vector<std::string>& func_params){
    if(func_params[0] != "cxx"){
        cerr << "[INTR] Internal control flow error while trying execute " << func_params[0] << " as cxx()." << endl;
        return;
    }
    if(func_params.size() != 2){
        cerr << "[FAIL] Passing " << func_params.size() -1 << " parameter(s) to cxx(), which expects 1." << endl;
        return;
    }
    destcxx = func_params[1];
}

void mkObject(std::vector<DestObject>& objlist,std::vector<std::string>& func_params,std::pair<std::string,std::string> cc_cxx){
    if(func_params[0] != "object"){
        cerr << "[INTR] Internal control flow error while trying execute " << func_params[0] << " as object()." << endl;
        return;
    }
    if(func_params.size() != 3 || func_params.size() != 4){
        cerr << "[FAIL] Passing " << func_params.size() -1 << " parameter(s) to object(), which expects 2 or 3." << endl;
        return;
    }
    DestObject tmpdest;
    if(str_endwith(func_params[1],".cpp")){
        tmpdest.compiler = cc_cxx.second;
    }else if(str_endwith(func_params[1],".c")){
        tmpdest.compiler = cc_cxx.first;
    }else{
        cerr << "[FAIL] Attempt to build non-c/cxx object " << func_params[1] << endl;
        return;
    }
    tmpdest.filepath = func_params[1];
    tmpdest.flags = func_params[2];
    if(func_params.size() == 4){
        tmpdest.name = func_params[3];
    }else{
        tmpdest.name = func_params[1];
    }
    objlist.push_back(tmpdest);
}
void mkExecutable(std::vector<DestExecutable>& execlist,std::vector<std::string>& func_params,std::pair<std::string,std::string> cc_cxx){
    if(func_params[0] != "executable"){
        cerr << "[INTR] Internal control flow error while trying execute " << func_params[0] << " as executable()." << endl;
        return;
    }
    if(func_params.size() < 5){
        cerr << "[FAIL] Passing " << func_params.size() -1 << " parameter(s) to executable(), which expects at least 4." << endl;
        return;
    }
    DestExecutable tmpdest;
    tmpdest.compiler = func_params[1];
    tmpdest.name = func_params[2];
    tmpdest.flags = func_params[3];
    for(int i=4;i<func_params.size();i++){
        tmpdest.dependencies.push_back(func_params[i]);
    }
    execlist.push_back(tmpdest);
}
