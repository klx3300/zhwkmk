#ifndef Q_ZHWKMK_GENDEST_H
#define Q_ZHWKMK_GENDEST_H

#include <string>
#include <vector>
#include "../stdafx.h"
#include "../parse_str/strparse.h"
#include <unordered_set>

void init_gendest();

std::string gendest_ref(std::string name);
void gendest_assign(std::vector<std::string> &output,std::vector<FuncParams> call);
void gendest_eval(std::vector<std::string> &output,std::vector<FuncParams> call);
void gendest_obj(std::vector<std::string> &output,std::vector<FuncParams> call);
void gendest_exe(std::vector<std::string> &output,std::vector<FuncParams> call, std::unordered_set<std::string>& arbits);
void gendest_clean(std::vector<std::string> &output,std::vector<std::string> targets);
void gendest_default(std::vector<std::string> &output,std::string default_name);


#endif
