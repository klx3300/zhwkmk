#ifndef X__BADMINTON_STRPARSE_H
#define X__BADMINTON_STRPARSE_H

#include <vector>
#include <string>

class FuncParams{
public:
    std::string str;
    bool is_literal=false;
    FuncParams(std::string istr,bool ilit):str(istr),is_literal(ilit){};
};

std::vector<std::string> strsplit(std::string src,char sep);

// this one supports string literal
std::vector<FuncParams> parsefunc(std::string src,int lineno);

#endif