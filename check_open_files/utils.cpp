#include "utils.h"
using namespace std;
/*
 * IN: map<a, b>, vector<a>
 * OUT: vector<a>', order by b, descending
 */
void ranking(map<int, int> &weights, vector<int> &rank) {
    map<int, int>::iterator it = weights.begin();
    for (; it != weights.end(); it++) {//遍历pid
        bool bInserted = false;
        vector<int>::iterator it2 = rank.begin();
        for (; it2 != rank.end(); it2++) {//寻找插入点
            if (it->second >= weights[*it2]) {
//                printf ( "insert (%d, %d) before (%d, %d)\n", it->first, it->second, *it2, weights[*it2]);
                rank.insert(it2, it->first);
                bInserted = true;
                break;
            }
        }
        if (!bInserted) {
//            printf ( "insert (%d, %d) after (?, ?)\n", it->first, it->second);
            rank.push_back(it->first);
        }
    }
}
