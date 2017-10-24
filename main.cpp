#include <iostream>
#include <fstream>
#include "parse_str/strparse.h"
#include "macro_replace/macro_replace.h"
#include "stroper/stroper.h"
#include <string>
#include "unistd.h"

#define println(str) cout << str << endl;
#define unixok(funcall) (!(funcall))

using namespace std;

unordered_map<string,string> macros;

void parsefile(string filename);

int main(int argc,char** argv){
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
    parsefile(filename);

}

void parsefile(string filename){
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
            auto replaced = macro_replace(macros,x);
            if(replaced[0].str == "include"){
                parsefile(replaced[1].str);// recursively
            }
        }
}