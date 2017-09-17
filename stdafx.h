#ifndef Q_ZHWKMK_STDAFX_H
#define Q_ZHWKMK_STDAFX_H

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

#endif