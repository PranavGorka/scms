#pragma once
#include <string>
using namespace std;

namespace utils {
    string timeNow();          
    string makeSalt();            
    string hashPassword(const string &password, const string &salt);
}
