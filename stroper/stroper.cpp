#include "stroper.h"

#include <vector>

using namespace std;

bool str_startwith(string src,string chk){
    return !src.find_first_of(chk);
}

bool str_endwith(string src,string chk){
    return src.find_last_of(chk) == (src.size()-chk.size());
}

string str_base_trim(string src,string trimer){
    string tmpstr;
    for(auto ch:src){
        bool FLAG=true;
        for(auto chk:src){
            if(ch == chk){
                FLAG=false;
                break;
            }
        }
        if(FLAG) tmpstr += ch;
    }
    return tmpstr;
}

string str_trim(string src){
    return str_base_trim(src," ");
}