#ifndef Q_ZHWKMK_STROPER_H
#define Q_ZHWKMK_STROPER_H

#include <string>

bool str_startwith(std::string src,std::string chk);
bool str_endwith(std::string src,std::string chk);

std::string str_trim(std::string src);
// the trimer here acts like ... vector<char>
std::string str_base_trim(std::string src,std::string trimer);

#endif