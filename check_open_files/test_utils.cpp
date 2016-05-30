#include "utils.h"

using namespace std;
map<int, int> pid_fd_map;
map<int, string> pid_cmd_map;
vector<int> pid_list; //select * from pid_list, ordered by fd_num

void print_maps(bool bNaturalOrder) {//default ordered by pid
    LOGD("  PID :   fd  :   cmdline\n");
    if (bNaturalOrder) { //select (pid, fd, cmdline) from xx, order by pid, ascending
        map<int, int>::iterator it;
        for (it = pid_fd_map.begin(); it != pid_fd_map.end(); it++) {
            LOGD("%5d : %5d : %s\n", it->first, it->second, pid_cmd_map[it->first].c_str());
        }
    } else {             //select (pid, fd, cmdline) from xx, order by fd, descending
        vector<int>::iterator it3;
        for (it3 = pid_list.begin(); it3 != pid_list.end(); it3++) {
            LOGD("%5d : %5d : %s\n", *it3, pid_fd_map[*it3], pid_cmd_map[*it3].c_str());
        }
    }
}

int main ( int argc, char *argv[] )
{
    pid_fd_map[1] = 3;
    pid_fd_map[2] = 2;
    pid_fd_map[3] = 5;
    pid_fd_map[4] = 8;
    pid_fd_map[5] = 8;
    pid_fd_map[6] = 2;
    pid_fd_map[7] = 11;
    ranking(pid_fd_map, pid_list);
    print_maps(false);
    print_maps(true);
    return 0;
}
