/*
 * check total open fd number
 */
#include <dirent.h>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fstream>
#include <errno.h>
#include <set>

#define LOG_TAG "cof"
#define MAXLINE 256

#ifdef _ANDROID_
#include <cutils/log.h>
#endif

#include "utils.h"
using namespace std;

enum SKIPPED_PID {
    //    DEV_NULL_0 = 0,
    //    DEV_NULL_1 = 1,
    //    DEV_NULL_2 = 2,
    //    DEV_BINDER = 3,
    //    LOG_MAIN = 4,
    //    LOG_RADIO = 5,
    //    LOG_EVENTS = 6,

    SKIPPED_PID_MAX = 0,
};

set<int> all_open_fd;
map<int, int> pid_fd_map;
map<int, string> pid_cmd_map;
string read_line(string inFile);
vector<int> pid_list; //select * from pid_list, ordered by fd_num

void print_maps(int mOrder) {//default ordered by pid
    LOGD("  PID :   fd  :   cmdline\n");
    map<int, int>::iterator it;
    vector<int>::iterator it3;
    switch (mOrder) {
        case 1: //select (pid, fd, cmdline) from xx, order by pid, ascending
            for (it = pid_fd_map.begin(); it != pid_fd_map.end(); it++) {
                LOGD("%5d : %5d : %s\n", it->first, it->second, pid_cmd_map[it->first].c_str());
            }
            break;
        case 2: //select (pid, fd, cmdline) from xx, order by fd, descending
            for (it3 = pid_list.begin(); it3 != pid_list.end(); it3++) {
                LOGD("%5d : %5d : %s\n", *it3, pid_fd_map[*it3], pid_cmd_map[*it3].c_str());
            }
            break;
        default:
            LOGE( "internal error\n" );
            exit(4);
    }
}

int read_maps(const char *proc_dir, pid_t this_pid) {
    DIR *dp;
    struct dirent *dirp;
    // open /proc
    if ((dp = opendir(proc_dir)) == NULL) {
        LOGD("Can not open dir %s\n", proc_dir);
        return 1;
    }
    // iterate-1 /proc/<pid>
    while ((dirp = readdir(dp)) != NULL) {
        if (('1' <= *(dirp->d_name)) && (*(dirp->d_name)) <= '9') { // /proc/[1~9]+
            string fd_dir;
            string proc_pid_cmdline;
            stringstream ss;
            stringstream log_stream;
            ss << proc_dir << "/" << dirp->d_name << "/fd";
            fd_dir = ss.str();  //proc/123/fd
            int fd_num = 0;
            if (this_pid == atoi(dirp->d_name)) {
                log_stream << "PID(this): " << fd_dir << "\n";
            } else {
                log_stream << "PID: " << fd_dir << "\n";
            }
            DIR *dp2;
            struct dirent *dirp2;
            dp2 = opendir(fd_dir.c_str());
            if (NULL == dp2) {
                LOGW("error openning %s\n", fd_dir.c_str());
                continue;
            }
            // iterate-2 /proc/<pid>/fd/
            while ((dirp2 = readdir(dp2)) != NULL) {
                if ((0 != strcmp(".", dirp2->d_name))
                    && (0 != strcmp("..", dirp2->d_name))) {
                    log_stream << dirp2->d_name << " ";
                    if (atoi(dirp2->d_name) >= SKIPPED_PID_MAX) {
                        fd_num++;
                    }
                    all_open_fd.insert(atoi(dirp2->d_name));
                }
            }
            ss.str("");
            ss << proc_dir << "/" << dirp->d_name << "/cmdline";
            proc_pid_cmdline = read_line(ss.str());
            LOGV("%s, total=(%d)\n", log_stream.str().c_str(), fd_num);
            if (fd_num) {
                pid_fd_map[atoi(dirp->d_name)] = fd_num;
                pid_cmd_map[atoi(dirp->d_name)] = proc_pid_cmdline;
            }
            closedir(dp2);
        } else {
            //        LOGD ( "skip: %s\n", dirp->d_name);
        }
    }
    closedir(dp);
    return EXIT_SUCCESS;
}

void print_usage(void) {
    LOGD("Usage: prog [--loop | -l ] ([ -1 | --pid-order ] | [ -2 | --fd-order ])\n");
}

string read_line(string inFile) {
    //init
    vector < string > aLines;
    ifstream ifs;
    char aLine[MAXLINE];
    string ret = "";
    //open
    ifs.open(inFile.c_str(), ifstream::in);
    if (!ifs.is_open()) {
        goto this_ex1;
    }
    //read
    ifs.getline(aLine, MAXLINE);
    if (ifs.good() || ifs.eof()) {
        ret = string(aLine);
    }
  this_final:
    if (ifs.is_open()) {
        ifs.close();
    }
    return ret;
  this_ex1:
    LOGD("can not open %s, Why: %s\n", inFile.c_str(), strerror(errno));
    return ret;
}

int main(int argc, char *argv[]) {
    bool bLoop = false;
    int mOrder = 1;
    argc--;
    while (argc) {
        argv++;
        if (!strcmp("--loop", *argv) || !strcmp("-l", *argv)) {
            printf ( "looping...\n" );
            bLoop = true;
        } else if (!strcmp("-1", *argv)) {
            mOrder = 1;
        } else if (!strcmp("-2", *argv)) {
            mOrder = 2;
        } else {
            print_usage();
            exit(1);
        }
        argc--;
    }
    pid_t this_pid = getpid();
  runner:
    read_maps("/proc", this_pid);
    ranking(pid_fd_map, pid_list);
    print_maps(mOrder);
    if (bLoop) {
        sleep(30);              //polling every 30 seconds
        goto runner;
    }
    return EXIT_SUCCESS;
}
