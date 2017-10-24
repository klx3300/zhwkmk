#include "gendest.h"
#include "../stroper/stroper.h"

using namespace std;

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

}

void gendest_exe(vector<string> &output,vector<FuncParams> call,string dir){

}