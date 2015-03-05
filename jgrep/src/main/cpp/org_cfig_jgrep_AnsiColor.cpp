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

/*
 * Class:     org_cfig_jgrep_AnsiColor
 * Method:    nativeTest
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_cfig_jgrep_AnsiColor_nativeTest(JNIEnv *env, jobject obj) {
    jclass jc; 
    jmethodID jmid;
    jc = env->FindClass("org/cfig/jgrep/AnsiColor");
    if (NULL == jc) {//fail to find class
        return NULL;
    }
    jmid = env->GetMethodID(jc,"nativeTest2", "()Ljava/lang/String;");
    if (NULL == jmid) {//fail to find method
        return NULL;
    }
    jstring result = (jstring)env->CallObjectMethod(obj, jmid, NULL);
    const char* str = env->GetStringUTFChars(result, 0); 
    printf("Got string from java: [%s], sending back ...\n", str);
    env->ReleaseStringUTFChars(result, 0); 
    jstring ret = env->NewStringUTF(str);
    return ret;
}
