#ifndef Q_ZHWKMK_FUNCTIONS_H
#define Q_ZHWKMK_FUNCTIONS_H

#include <unordered_map>
#include <string>
#include <vector>

class DestObject{
public:
    std::string name;
    std::string filepath;
    std::string flags; // cflags cxxflags
    std::string compiler;
};

class DestExecutable{
public:
    std::string name;
    std::string filepath;
    std::string flags; // ldflags
    std::string compiler;
    std::vector<std::string> dependencies;
};

void mkMacro(std::unordered_map<std::string,std::string>& replacement,
    std::vector<std::string>& func_params);

void mkConcat(std::unordered_map<std::string,std::string>& replacement,
    std::vector<std::string>& func_params);

void mkEval(std::unordered_map<std::string,std::string>& replacement,
    std::vector<std::string>& func_params);

void mkCC(std::string& destcc,std::vector<std::string>& func_params);
void mkCXX(std::string& destcxx,std::vector<std::string>& func_params);

void mkObject(std::vector<DestObject>& objlist,std::vector<std::string>& func_params);
void mkExecutable(std::vector<DestExecutable>& execlist,std::vector<std::string>& func_params);

#endif