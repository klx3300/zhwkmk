#ifndef Q_ZHWKMK_GENDEST_H
#define Q_ZHWKMK_GENDEST_H

#include <string>
#include <vector>
#include "../stdafx.h"

std::string generate_destfile(std::vector<DestObject> &objlist,std::vector<DestExecutable>& execlist,
std::string cc,std::string cxx);

#endif