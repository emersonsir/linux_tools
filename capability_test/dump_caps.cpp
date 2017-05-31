#include <sys/capability.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <sstream>
#include <cstring>
#ifdef __ANDROID__
#define LOG_TAG "XX"
#include <utils/Log.h>
#else
#define ALOGE printf
#define ALOGI printf
#endif

void dump_caps(void) {
    pid_t pid;
    cap_t cap;
    cap_value_t cap_list[CAP_LAST_CAP+1];
    cap_flag_t cap_flags;
    cap_flag_value_t cap_flags_value;
    //
    // generated list with command line below:
    // sed -n 's/^#define \(CAP_.*\) .*/\1/p' /usr/include/linux/capability.h | tr A-Z a-z
    // don't take cap_last_cap which is the same as the last cap_syslog capability
    //
    const char *cap_name[CAP_LAST_CAP+1] = {
#include "caps.source"
    };

    pid = getpid();
    cap = cap_get_pid(pid);
    if (cap == NULL) {
        ALOGE("cap_get_pid: code=%d, str=%s\n", errno, strerror(errno));
        return;
    }

    /* effetive cap */
    cap_list[0] = CAP_CHOWN;
    if (cap_set_flag(cap, CAP_EFFECTIVE, 1, cap_list, CAP_SET) == -1) {
        ALOGE("cap_set_flag cap_chown: code=%d, str=%s\n", errno, strerror(errno));
        cap_free(cap);
        return;
    }
    
    /* permitted cap */
    cap_list[0] = CAP_MAC_ADMIN;
    if (cap_set_flag(cap, CAP_PERMITTED, 1, cap_list, CAP_SET) == -1) {
        ALOGE("cap_set_flag cap_syslog: code=%d, str=%s\n", errno, strerror(errno));
        cap_free(cap);
        return;
    }

    /* inherit cap */
    cap_list[0] = CAP_SETFCAP;
    if (cap_set_flag(cap, CAP_INHERITABLE, 1, cap_list, CAP_SET) == -1) {
        ALOGE("cap_set_flag cap_setfcap: code=%d, str=%s\n", errno, strerror(errno));
        cap_free(cap);
        return;
    }

    for (unsigned i=0; i < CAP_LAST_CAP + 1; i++) {
        char line[64] = { 0 };
        std::ostringstream ss;

        cap_from_name(cap_name[i], &cap_list[i]);
        sprintf(line, "%-20s %6d\t", cap_name[i], cap_list[i]);
        ss << line;
        memset(line, 0, sizeof(line));

        ss << ("flags: \t");

        cap_get_flag(cap, cap_list[i], CAP_EFFECTIVE, &cap_flags_value);
        sprintf(line, " EFFECTIVE %-4s ", (cap_flags_value == CAP_SET) ? "OK" : "-");
        ss << line;
        memset(line, 0, sizeof(line));

        cap_get_flag(cap, cap_list[i], CAP_PERMITTED, &cap_flags_value);
        sprintf(line, " PERMITTED %-4s ", (cap_flags_value == CAP_SET) ? "OK" : "-");
        ss << line;
        memset(line, 0, sizeof(line));

        cap_get_flag(cap, cap_list[i], CAP_INHERITABLE, &cap_flags_value);
        sprintf(line, " INHERITABLE %-4s ", (cap_flags_value == CAP_SET) ? "OK" : "-");
        ss << line;
        memset(line, 0, sizeof(line));

        ALOGI("%s\n", ss.str().c_str());
    }
    cap_free(cap);
}

int main(void) {
    dump_caps();
    return 0;
}
