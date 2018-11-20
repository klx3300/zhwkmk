#include <iostream>
#include <fstream>
#include "parse_str/strparse.h"
#include "macro_replace/macro_replace.h"
#include "stroper/stroper.h"
#include "gendest/gendest.h"
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdio>
#include <unordered_set>

#define println(str) cout << str << endl;
#define unixok(funcall) (!(funcall))
#define dbg(...) printf("[DBG] " __VA_ARGS__);printf("\n")

using namespace std;

unordered_map<string,string> macros;
vector<string> clear_targets;
vector<string> finale;
unordered_set<string> arbits;

void parsefile(string filename,string prestructure, string rpath);

int main(int argc,char** argv){
    init_gendest();
    string filename;
    string rpath;
    // parse args
    if(argc == 1){
        filename = "make.zhwkmk";
        rpath = "./";
        dbg("Makespec file not specified. fallback to default(make.zhwkmk).");
        dbg("Out-of-tree make disabled by default(./).");
    }
    if(argc > 1){
        if(string(argv[1]) == "--help" || string(argv[1]) == "-h"){
            cout << "Read readme plz!" << endl;
            return 0;
        }
        rpath = string(argv[1]);
        if(rpath[rpath.length() - 1] != '/') rpath += "/";
        dbg("Out-of-tree zhwkmk file path set to %s", rpath.c_str());
        filename = "make.zhwkmk";
    }
    if (argc > 2){
        filename = argv[2];
        dbg("Set makespec file to %s", filename.c_str());
    }
    parsefile(rpath + filename,"", rpath);
    gendest_clean(finale,clear_targets);
    // write out.
    fstream output("Makefile",ios_base::out);
    for(auto x:finale){
        output << x << endl;
    }
    dbg("Makefile generated at Makefile.");
    return 0;
}

void parsefile(string filename, string prestructure, string rpath){
    // check access
    if(!unixok(access(filename.c_str(),R_OK))){
        cout << "Makespec file is not exist or read permission denied." << endl;
        exit(1);
    }
    // create directory structure
    if(prestructure != "" && !unixok(access(prestructure.c_str(), F_OK))){
        dbg("Creating directory structure at %s", prestructure.c_str());
        if(!unixok(mkdir(prestructure.c_str(), 0755))){
            cout << "Failed creating directory structure. Aborting.." << endl;
            abort();
        }
    }
    // read lines
    fstream makespec(filename,ios_base::in);
    string linebuffer;
    int lineno = 0;
    vector<pair<int,string>> instructions;
    while(getline(makespec,linebuffer)){
        lineno++;
        // ignore comments
        dbg("[%d] %s", lineno, linebuffer.c_str());
        linebuffer = str_trim(linebuffer);
        if(str_startwith(linebuffer,"#")){
            continue;
        }
        instructions.push_back(pair<int,string>(lineno,linebuffer));
    }
    vector<vector<FuncParams>> pr;
    for(auto i:instructions){
        pr.push_back(parsefunc(i.second,i.first));
    }
    for(auto x:pr){
        if(x.size() < 1) continue; // ignore empty lines
        string origfirst = x[1].str;
        auto replaced = macro_replace(macros,x);
        if(replaced[0].str == "include"){
            parsefile(rpath + replaced[1].str, prestructure + replaced[2].str, rpath);// recursively
        }else if(replaced[0].str == "macro"){
            macros[origfirst] = replaced[2].str;
        }else if(replaced[0].str == "concat"){
            string tmpres;
            for(int i=2;i<replaced.size();i++){
                tmpres+=replaced[i].str;
            }
            macros[origfirst] = tmpres;
        }else if(replaced[0].str == "vari"){
            macros[origfirst] = gendest_ref(origfirst);
            replaced[1].str = origfirst;
            (gendest_assign(finale,replaced));
        }else if(replaced[0].str == "eval"){
            replaced[1].str = origfirst;
            macros[origfirst] = gendest_ref(origfirst);
            (gendest_eval(finale,replaced));
        }else if(replaced[0].str == "cc"){
            macros["cc"] = str_trim(replaced[1].str);
        }else if(replaced[0].str == "cxx"){
            macros["cxx"] = str_trim(replaced[1].str);
        }else if(replaced[0].str == "object"){
            if(replaced.size() > 4) replaced[4].str = prestructure + replaced[4].str;
            else replaced.push_back(FuncParams(prestructure + replaced[2].str, true));
            replaced[2].str = rpath + prestructure + replaced[2].str;
            for(int i = 5; i < replaced.size(); i++){
                // optional header dependencies
                replaced[i].str = rpath + prestructure + replaced[i].str;
            }
            // auto detect header dependency (simple)
            string srcname = replaced[2].str;
            int position = srcname.find_last_of('.');
            if(position != string::npos){
                srcname = srcname.substr(0, position);
            }
            if(unixok(access((srcname + ".h").c_str(), R_OK))){
                dbg("Auto generated header dependency %s.h", srcname.c_str());
                replaced.push_back(FuncParams(srcname + ".h", true));
            }else if(unixok(access((srcname + ".hpp").c_str(), R_OK))){
                dbg("Auto generated header dependency %s.h", srcname.c_str());
                replaced.push_back(FuncParams(srcname + ".hpp", true));
            }
            gendest_obj(finale,replaced);
            clear_targets.push_back(replaced[4].str + ".o");
        } else if(replaced[0].str == "arbit"){
            replaced[1].str = rpath + prestructure + replaced[1].str;
            macros[replaced[2].str] = replaced[1].str;
            arbits.insert(replaced[1].str);
            dbg("Arbitrary Object at %s", replaced[1].str.c_str());
        }else if(replaced[0].str == "executable"){
            replaced[2].str = prestructure + replaced[2].str;
            replaced[4].str = prestructure + replaced[4].str;
            for(int i = 5; i < replaced.size(); i++){
                replaced[i].str = prestructure + replaced[i].str;
            }
            gendest_exe(finale,replaced,arbits);
            clear_targets.push_back(replaced[2].str);
        }else if(replaced[0].str == "default"){
            gendest_default(finale,prestructure + replaced[1].str);
        }else{
            println("Unknown function. parsing terminated.");
            exit(-1);
        }
    }
}
