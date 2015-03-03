HEADER_DIR = \
	$(JAVA_HOME)/include \
	$(JAVA_HOME)/include/linux
libttycheck.so: org_cfig_jgrep_AnsiColor.o
	$(CXX) -shared -o $@ $^
	strip --strip-all $@

org_cfig_jgrep_AnsiColor.o:org_cfig_jgrep_AnsiColor.cpp
	$(CXX) -I$(HEADER_DIR) -c -Wall -Werror -fpic $^
