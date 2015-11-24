# 初始化
#-------------------------------------------------------------------------------
#                                     init
#-------------------------------------------------------------------------------
# autoconf
AC_INIT([db], [0.1], [yuyezhong@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

# automake
AM_INIT_AUTOMAKE([foreign -Wall -Werror]) #foreign ignores some GNU Coding Standards

#-------------------------------------------------------------------------------
#                                 check std progs
#-------------------------------------------------------------------------------
# 检查sed
AC_PROG_SED
# check autoconf version
AC_PREREQ([2.65])

#-------------------------------------------------------------------------------
#                                 check misc progs
#-------------------------------------------------------------------------------
# ensure configure is not run from outer space
AC_CONFIG_SRCDIR([src/db])

#-------------------------------------------------------------------------------
#                                 check headers
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
#                                   outputs
#-------------------------------------------------------------------------------
# 配置config.h
AC_CONFIG_HEADERS([config.h])

# 要从xx.in生成xx的文件列表:automake从FILE.am-->FILE.in,autoconf从FILE.in-->FILE
AC_CONFIG_FILES([Makefile src/Makefile])

# 结束
AC_OUTPUT
