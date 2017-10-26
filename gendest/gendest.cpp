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
    comp = call[0].str;
    src=dir+call[1].str;
    flag=call[2].str;
    if(call.size() == 3){
        // shortv
        name = dir+src+".o";
    }else{
        name = dir+call[3].str;
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
    comp=call[0].str;
    src = dir+call[3].str+".o";
    flag = call[2].str;
    name = dir+call[1].str;
    string ass;
    ass += name+": "+dir+src+" ";
    for(int i=4;i<call.size();i++){
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
    for(int i=4;i<call.size();i++){
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