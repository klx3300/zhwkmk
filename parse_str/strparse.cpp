#include "strparse.h"
#include <iostream>

using namespace std;

vector<string> strsplit(string src,char sep){
    int tmpos = 0;
    vector<string> tmpv;
    while((tmpos=src.find(sep))!=string::npos){
        // found
        tmpv.push_back(src.substr(0,tmpos));
        src=src.substr(tmpos+1,string::npos);
    }
    tmpv.push_back(src);
    return tmpv;
}

vector<FuncParams> parsefunc(string src,int lineno){
    int tmpos = 0;
    vector<FuncParams> tmpvec;
    string tmpstr;
    int FLAG=0;
    bool escape_char = false;
    for(auto ch:src){
        tmpos++;
        if(ch == '\\'){
            if(escape_char != true){
                escape_char = true;
                continue;
            }
            escape_char = false;
        }
        if(FLAG == 0){ // 0: parsing function name
            if(ch != '('){
                tmpstr += ch;
            }else{
                tmpvec.push_back(FuncParams(tmpstr,false));
                tmpstr = "";// re-init
                FLAG++;
            }
        }else if(FLAG == 1){ // 1: pre-parsing phase
            if(ch == '"'){
                // parameter is string literal
                if(escape_char == false){
                    FLAG = 3;
                }else{
                    escape_char = false;
                    tmpstr += ch;
                    FLAG = 2;
                }
            }else{
                tmpstr += ch;
                FLAG++;
            }
        }else if(FLAG == 2){ // 2: parsing parameter
            if( ch == '"'){
                if(escape_char){
                    escape_char = false;
                    tmpstr += ch;
                    continue;
                }
                cerr << "[FAIL] Unsupported operation between normal paramter and " << endl;
                cerr << "       string literal at " << lineno << ':' << tmpos << endl;
                return vector<FuncParams>();
            }else if(ch == ','){
                if(escape_char){
                    escape_char = false;
                    tmpstr += ch;
                    continue;
                }
                tmpvec.push_back(FuncParams(tmpstr,false));
                tmpstr = "";
                FLAG = 1;
            }else if(ch == ')'){
                // parsing completed.
                if(escape_char){
                    escape_char = false;
                    tmpstr += ch;
                    continue;
                }
                tmpvec.push_back(FuncParams(tmpstr,false));
                tmpstr = "";
                break;
            }else{
                tmpstr += ch;
            }
        }else if(FLAG == 3){ // 3: parsing string literal
            if(ch == '"'){
                if(escape_char){
                    escape_char = false;
                    tmpstr += ch;
                    continue;
                }
                tmpvec.push_back(FuncParams(tmpstr,true));
                tmpstr = "";
                FLAG = 4;
            }else{
                tmpstr += ch;
            }
        }else if(FLAG == 4){ // 4: post-parsing string literal
            if(ch == ','){
                FLAG = 1;
            }else if(ch == ')'){
                break;
            }else{
                cerr << "[FAIL] Unsupported operation between normal parameter and " << endl;
                cerr << "       string literal at " << lineno << ":" << tmpos << endl;
                return vector<FuncParams>();
            }
        }else{
            // parsing complete.
            break;
        }
        if(escape_char){
            escape_char = false;
        }
    }
    if(tmpstr != ""){
        // abnormal termination
        cerr << "[FAIL] Unclosed function call at " << lineno << ":" << tmpos << endl;
        return vector<FuncParams>();
    }
    return tmpvec;
}