#ifndef __UTILS_H__
#define __UTILS_H__

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

using namespace std;


uint64_t useconds();
const char * getEnv(char *env[], const char *prefix, const char *defaultValue);
vector<string> listFilenames(const string &folder);
bool isDir(const string &path);
bool isFile(const string &path);



#endif