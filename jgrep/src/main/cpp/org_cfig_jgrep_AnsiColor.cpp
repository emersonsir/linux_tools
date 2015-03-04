/*
 * =====================================================================================
 *
 *       Filename:  org_cfig_jgrep_AnsiColor.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/16/2015 04:18:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <cstdio>
#include "org_cfig_jgrep_AnsiColor.h"

JNIEXPORT jboolean JNICALL Java_org_cfig_jgrep_AnsiColor_isStdinTty(JNIEnv *, jobject) {
    return isatty(fileno(stdin));
//EBADF //fd invalid
//EINVAL/ENOTTY //not tty
}

JNIEXPORT jboolean JNICALL Java_org_cfig_jgrep_AnsiColor_isStdoutTty(JNIEnv *, jobject) {
    return isatty(fileno(stdout));
}
