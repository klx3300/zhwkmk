#ifndef Q_ZHWKMK_MACRO_H
#define Q_ZHWKMK_MACRO_H

#include "../parse_str/strparse.h"
#include <unordered_map>

std::vector<FuncParams> macro_replace(std::unordered_map<std::string,std::string> replacement,std::vector<FuncParams> orig);


#endif