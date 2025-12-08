#include "utils.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <random>
#include <functional>
using namespace std;
using namespace chrono;

string utils::timeNow() {
    auto now = system_clock::now();
    time_t t = system_clock::to_time_t(now);
    tm tm = *localtime(&t);
    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

string utils::makeSalt() {
    static mt19937_64 rng((unsigned)chrono::system_clock::now().time_since_epoch().count());
    static const char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    uniform_int_distribution<> dist(0, sizeof(chars)-2);
    string s;
    for (int i = 0; i < 12; ++i) s.push_back(chars[dist(rng)]);
    return s;
}

string utils::hashPassword(const string &password, const string &salt) {
    hash<string> h;
    auto combined = password + ":" + salt;
    size_t val = h(combined);
    ostringstream oss;
    oss << hex << val;
    return oss.str();
}
