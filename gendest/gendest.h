#ifndef Q_ZHWKMK_GENDEST_H
#define Q_ZHWKMK_GENDEST_H

#include <string>
#include <vector>
#include "../stdafx.h"
#include "../parse_str/strparse.h"

void init_gendest();

std::string gendest_ref(std::string name);
void gendest_assign(std::vector<std::string> &output,std::vector<FuncParams> call);
void gendest_eval(std::vector<std::string> &output,std::vector<FuncParams> call);
void gendest_obj(std::vector<std::string> &output,std::vector<FuncParams> call,std::string relative);
void gendest_exe(std::vector<std::string> &output,std::vector<FuncParams> call,std::string relative);
void gendest_clean(std::vector<std::string> &output,std::vector<std::string> targets);

#endif