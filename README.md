# utils
Some convenient tools for daily work

## jgrep (obsolete, Now I use "ag" instead)
jgrep is a 'grep' like program with java regex flavor, targeted for advanced daily regex use

### quick start

Suggest to add the following alias into ~/.bashrc (suppose the jar file is put at ~/.bin/)

    alias jgrep='java -jar ~/.bin/jgrep.jar'

Then you can call it via a convenient command:

```
Usage: jgrep [OPTION]... PATTERN [FILE]...
Search for PATTERN in each FILE or standard input.
PATTERN is java flavored regex
        Example: jgrep -i 'hello world' menu.c
    -h | --help         print help
       | --version      print version info
    -i | --ignore-case  be case insensitive
       | --color=on     force color on even no console detected
    -g | --group        show group info
```
