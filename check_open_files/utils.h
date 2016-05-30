#ifndef _MY_UTILS_H_
#define _MY_UTILS_H_

#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <set>
#include <vector>
#include <map>

#ifdef _ANDROID_
#define LOGD ALOGE
#define LOGD ALOGD
#define LOGW ALOGW
#define LOGV
#else
/*
 * using printf
 */
#define LOGE(...) fprintf(stdout, __VA_ARGS__)
#define LOGW(...) fprintf(stdout, __VA_ARGS__)
#define LOGI(...) fprintf(stdout, __VA_ARGS__)
#define LOGD(...) fprintf(stdout, __VA_ARGS__)
#define LOGV(...) do {} while (0)
#endif

void ranking(std::map<int, int> &weights, std::vector<int> &rank);

#endif
