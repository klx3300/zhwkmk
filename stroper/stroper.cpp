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
    int state = 0;
    for(auto ch:src){
        int laststate = state;
        for(auto chk:trimer){
            if(ch == chk){
                state += 1;
                break;
            }
        }
        if(laststate == state){
            tmpstr += ch;
            state = 0;
        }
    }
    return tmpstr;
}

string str_trim(string src){
    return str_base_trim(src," ");
}
