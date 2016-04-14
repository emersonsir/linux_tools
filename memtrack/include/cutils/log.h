#ifdef __WITH_ANDROID__
#define LOGD ALOGD
#define LOGW ALOGW
#define LOGV
#else
/*
 * add missing
 */
#include <cstring>
/*
 * using printf
 */
#define ALOGW(...) printf("\n");fprintf(stdout, __VA_ARGS__)
#define ALOGI(...) printf("\n");fprintf(stdout, __VA_ARGS__)
#define ALOGD(...) printf("\n");fprintf(stdout, __VA_ARGS__)
#define ALOGV(...) do {} while (0)
#endif

