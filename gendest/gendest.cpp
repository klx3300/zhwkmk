#include "gendest.h"
#include "../stroper/stroper.h"
#include <cstdio>
using namespace std;

char tab[5];

void init_gendest(){
    sprintf(tab,"\t");
}

string gendest_ref(string name){
    return "$("+name+")";
}

void gendest_assign(vector<string> &output,vector<FuncParams> call){
    output.push_back(call[1].str+" := "+call[2].str);
}

void gendest_eval(vector<string> &output,vector<FuncParams> call){
    output.push_back(call[1].str+=" := `"+call[2].str+"`");
}

void gendest_obj(vector<string> &output,vector<FuncParams> call,string dir){
    // parse paras
    string comp,src,flag,name;
    comp = call[1].str;
    src=dir+call[2].str;
    flag=call[3].str;
    if(call.size() == 4){
        // shortv
        name = dir+src+".o";
    }else{
        name = dir+call[4].str+".o";
    }
    // generate
    output.push_back(name+": "+src);
    string ass;
    ass += tab;
    ass += "@echo \"   "+comp+"   "+name+"\"";
    output.push_back(ass);
    ass = "";
    ass+=tab;
    ass += "@"+comp+" -c " + flag + " -o " + name + " " + src;
    output.push_back(ass);
}

void gendest_exe(vector<string> &output,vector<FuncParams> call,string dir){
    // parse paras
    string comp,src,flag,name;
    comp=call[1].str;
    src = dir+call[4].str+".o";
    flag = call[3].str;
    name = dir+call[2].str;
    string ass;
    ass += name+": "+dir+src+" ";
    for(int i=5;i<call.size();i++){
        ass += call[i].str + ".o ";
    }
    output.push_back(ass);
    ass = "";
    ass += tab;
    ass += "@echo \"   LD   "+name+"\"";
    output.push_back(ass);
    ass = "";
    ass+=tab;
    ass += "@"+comp+" "+flag+" -o "+name+" "+src+" ";
    for(int i=5;i<call.size();i++){
        ass += call[i].str+".o ";
    }
    output.push_back(ass);
}

void gendest_clean(vector<string> &output,vector<string> targets){
    output.push_back("clean:");
    string ass;
    ass+=tab;
    ass+="@echo \"  CLEAN   all files.\"";
    output.push_back(ass);
    ass = "";
    ass+=tab;
    ass+="-@rm ";
    for(auto x:targets){
        ass+=x+" ";
    }
    ass+=" || true";
    output.push_back(ass);
}

void gendest_default(vector<string> &output,string default_name){
    vector<string> copy = output;
    output.clear();
    output.push_back("__fake_main__: "+default_name);
    output.push_back("");
    for(auto x: copy){
        output.push_back(x);
    }
}