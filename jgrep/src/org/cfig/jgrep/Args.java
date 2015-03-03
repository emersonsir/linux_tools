package org.cfig.jgrep;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.File;

/**
 * Created by y on 2/15/15.
 */
public class Args {
    private Logger log = LoggerFactory.getLogger(this.getClass());
    private boolean showIndex;
    private boolean showGroup;
    private boolean ignoreCase = false;
    private String regex;
    private String file;//file or dir
    private boolean recurvice;//if "file" is a dir
    private boolean verbose;
    private boolean consoleMode;
    private boolean useStdin;
    private boolean showHelp;
    private boolean showVersion;
    private boolean forceColorOn;

    public void printUsage() {
        String ret = "Usage: jgrep [OPTION]... PATTERN [FILE]...\n";
        ret += "Search for PATTERN in each FILE or standard input.\n";
        ret += "PATTERN is java flavored regex\n";
        ret += "        Example: jgrep -i 'hello world' menu.c\n";
        ret += "    -h | --help         print help\n";
        ret += "       | --version      print version info\n";
        ret += "    -i | --ignore-case  be case insensitive\n";
        ret += "       | --color=on     force color on even no console detected\n";
        ret += "    -g | --group        show group info\n";
        log.info(ret);
    }

    @Override
    public String toString() {
        return "Args{" +
                "showIndex=" + showIndex +
                ", showGroup=" + showGroup +
                ", ignoreCase=" + ignoreCase +
                ", regex='" + regex + '\'' +
                ", file='" + file + '\'' +
                ", recurvice=" + recurvice +
                ", verbose=" + verbose +
                ", consoleMode=" + consoleMode +
                ", useStdin=" + useStdin +
                ", showHelp=" + showHelp +
                ", showVersion=" + showVersion +
                ", forceColorOn=" + forceColorOn +
                '}';
    }

    public boolean parse(String[] inArgs) {
        String s1 = "";
        String s2 = "";
        for (int i = 0; i < inArgs.length; i++)
            switch (inArgs[i]) {
                case "-g":
                case "--group":
                    showGroup = true;
                    break;
                case "-i":
                case "--ignore-case":
                    ignoreCase = true;
                    break;
                case "-v":
                    verbose = true;
                    showIndex = true;
                    break;
                case "-h":
                case "--help":
                    showHelp = true;
                    break;
                case "--version":
                    showVersion = true;
                    break;
                case "--color=auto":
                    //default
                    break;
                case "--color=on":
                    forceColorOn = true;
                    break;
                default:
                    if (s1.isEmpty()) {
                        s1 = inArgs[i];
                    } else if (s2.isEmpty()) {
                        s2 = inArgs[i];
                    } else {
                        log.error("Unknown arg: " + inArgs[i]);
                        return false;
                    }
            }

        //whether stdout is connected to a terminal
        if (null == System.console()) {
            this.consoleMode = false;
        } else {
            this.consoleMode = true;
        }

        //--help
        if (showHelp) {
            return true;
        }

        //--version
        if (showVersion) {
            return true;
        }

        //runner
        regex = s1;
        file = s2;
        if (regex.isEmpty()) {
            return false;
        }

        if (file == null || file.isEmpty()) {
            this.useStdin = true;
            recurvice = false;
        } else {
            //validate args
            File f = new File(s2);
            if (!f.exists()) {
                //no file
                log.error("file does not exist: " + s2);
                return false;
            }

            if (!f.canRead()) {
                //no permission
                log.error("file unreadable: " + s2);
                return false;
            }

            if (f.isDirectory()) {
                recurvice = true;
            }
        }

        return true;
    }

    public boolean isShowIndex() {
        return showIndex;
    }

    public boolean isShowGroup() {
        return showGroup;
    }

    public boolean isIgnoreCase() {
        return ignoreCase;
    }

    public String getRegex() {
        return regex;
    }

    public String getFile() {
        return file;
    }

    public boolean isRecurvice() {
        return recurvice;
    }

    public boolean isVerbose() {
        return verbose;
    }

    public boolean isUseStdin() {
        return useStdin;
    }

    public boolean isForceColorOn() {
        return forceColorOn;
    }

    public boolean isShowVersion() {
        return showVersion;
    }

    public boolean isShowHelp() {

        return showHelp;
    }

}
