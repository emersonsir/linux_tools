# utils
Some convenient tools for daily work

## jgrep
jgrep is a 'grep' like program with java regex flavor, targeted for advanced daily regex use

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
