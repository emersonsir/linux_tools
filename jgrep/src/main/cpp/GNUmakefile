HEADER_DIR = \
	-I$(JAVA_HOME)/include \
	-I$(JAVA_HOME)/include/linux

libttycheck.so: org_cfig_jgrep_AnsiColor.o
	$(CXX) -shared -o $@ $^
	strip --strip-all $@

org_cfig_jgrep_AnsiColor.o:org_cfig_jgrep_AnsiColor.cpp
	$(CXX) $(HEADER_DIR) -c -Wall -Werror -fpic $^

.PHONY: clean install
clean:
	rm -f *.so *.o ../resources/libttycheck.so

install: ../resources/libttycheck.so
../resources/libttycheck.so: libttycheck.so
	cp -p $< ../resources/$<
