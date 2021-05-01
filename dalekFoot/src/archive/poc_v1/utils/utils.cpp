#include "utils.h"
#include <stdint.h>
#include <dirent.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <vector>

using namespace std;


#ifndef NULL
#define NULL 0
#endif

uint64_t useconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_usec + (uint64_t)(tv.tv_sec * 1000000ULL);
}

bool isStartsWith(const char *const str, const char * const prefix) {
	const char * sptr = str;
	const char * pptr = prefix;	
	while (*pptr != '\0') {
		if (*sptr != *pptr) return false;
		sptr++;
		pptr++;
	}
	return true;
}

const char * getEnv(char *env[], const char *prefix, const char *def) {
	size_t len = strlen(prefix);
	while (*env) {
		if (isStartsWith(*env, prefix)) return ((*env)+len);
		env++;
	}
	return def;
}

bool isDir(const string &path) {
    struct stat path_stat;
    stat(path.c_str(), &path_stat);
    return !S_ISREG(path_stat.st_mode);
}

bool isFile(const string &path) {
    struct stat path_stat;
    stat(path.c_str(), &path_stat);
    return S_ISREG(path_stat.st_mode);
}

vector<string> listFilenames(const string &folder) {
	vector<string> ret;
	if (!isDir(folder)) return ret;
	DIR* dirp = opendir(folder.c_str());
	if (nullptr == dirp) return ret;
	struct dirent * dp;
	while ((dp = readdir(dirp)) != NULL) {
		if ((strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0)) {
			ret.push_back(dp->d_name);
		}
	}
	closedir(dirp);
	return ret;
}