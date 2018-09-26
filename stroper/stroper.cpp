#include "stroper.h"
#include <cstdlib>
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
    string bufferstr;
    int state = 0;
    for(auto ch:src){
        for(auto chk:trimer){
            if(ch == chk){
                if(state == 0) state = 1;
                else state = 3;
                break;
            }
        }
        switch(state){
            case 0:
                tmpstr += ch;
                state = 2;
                break;
            case 1:
                state = 0;
                break;
            case 2:
                tmpstr += bufferstr;
                tmpstr += ch;
                bufferstr = "";
                break;
            case 3:
                bufferstr += ch;
                state = 2;
                break;
            default:
                abort();
        }
    }
    return tmpstr;
}

string str_trim(string src){
    return str_base_trim(src," ");
}
