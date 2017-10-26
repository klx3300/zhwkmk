#include <iostream>
#include <fstream>
#include "parse_str/strparse.h"
#include "macro_replace/macro_replace.h"
#include "stroper/stroper.h"
#include "gendest/gendest.h"
#include <string>
#include "unistd.h"
#include <cstdio>

#define println(str) cout << str << endl;
#define unixok(funcall) (!(funcall))
#define dbg(...) printf("DBG" __VA_ARGS__);printf("\n")

using namespace std;

unordered_map<string,string> macros;
vector<string> clear_targets;
vector<string> finale;

void parsefile(string filename,string prestructure);

int main(int argc,char** argv){
    init_gendest();
    string filename;
    // parse args
    if(argc == 1){
        filename = "make.zhwkmk";
        println("makespec file not specified. fallback to default(make.zhwkmk).")
    }else{
        string tmpargv = argv[1];
        if(tmpargv == "--help"){
            println("read the readme?");
            return 0;
        }else{
            filename = tmpargv;
            cout << "Set makespec file to "<<filename<<endl;
        }
    }
    parsefile(filename,"");
    gendest_clean(finale,clear_targets);
    // write out.
    fstream output("Makefile",ios_base::out);
    for(auto x:finale){
        output << x << endl;
    }
    return 0;
}

void parsefile(string filename,string prestructure){
    // check access
    if(!unixok(access(filename.c_str(),R_OK))){
        cout << "Makespec file is not exist or read permission denied." << endl;
        exit(1);
    }
    // read lines
    fstream makespec(filename,ios_base::in);
    string linebuffer;
    int lineno = 0;
    vector<pair<int,string>> instructions;
    while(getline(makespec,linebuffer)){
        lineno++;
        // ignore comments
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
        string origfirst = x[1].str;
        auto replaced = macro_replace(macros,x);
        if(replaced[0].str == "include"){
            dbg("include %s",replaced[1].str.c_str());
            parsefile(replaced[1].str,replaced[2].str);// recursively
        }else if(replaced[0].str == "macro"){
            dbg("macro");
            macros[origfirst] = replaced[2].str;
        }else if(replaced[0].str == "concat"){
            dbg("concat");
            string tmpres;
            for(int i=2;i<replaced.size();i++){
                tmpres+=replaced[i].str;
            }
            macros[origfirst] = tmpres;
        }else if(replaced[0].str == "vari"){
            dbg("vari");
            macros[origfirst] = gendest_ref(origfirst);
            replaced[1].str = origfirst;
            (gendest_assign(finale,replaced));
        }else if(replaced[0].str == "eval"){
            dbg("eval");
            replaced[1].str = origfirst;
            macros[origfirst] = gendest_ref(origfirst);
            (gendest_eval(finale,replaced));
        }else if(replaced[0].str == "cc"){
            dbg("cc");
            macros["cc"] = str_trim(replaced[1].str);
        }else if(replaced[0].str == "cxx"){
            dbg("cxx");
            macros["cxx"] = str_trim(replaced[1].str);
        }else if(replaced[0].str == "object"){
            dbg("obj");
            (gendest_obj(finale,replaced,prestructure));
            clear_targets.push_back(prestructure+(replaced.size()==3?replaced[1].str:replaced[3].str)+".o");
        }else if(replaced[0].str == "executable"){
            dbg("exe");
            (gendest_exe(finale,replaced,prestructure));
            clear_targets.push_back(prestructure+replaced[1].str);
        }else{
            println("Unknown function. parsing terminated.");
            exit(-1);
        }
    }
}