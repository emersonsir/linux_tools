package org.cfig.jgrep;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.*;

/**
 * Created by y on 2/15/15.
 */
public class AnsiColor {
    private static final String ANSI_RESET = "\u001B[0m";
    private static final String ANSI_BLACK = "\u001B[30m";
    private static final String ANSI_RED = "\u001B[31m";
    private static final String ANSI_GREEN = "\u001B[32m";
    private static final String ANSI_YELLOW = "\u001B[33m";
    private static final String ANSI_BLUE = "\u001B[34m";
    private static final String ANSI_PURPLE = "\u001B[35m";
    private static final String ANSI_CYAN = "\u001B[36m";
    private static final String ANSI_WHITE = "\u001B[37m";
    private static final Logger log = LoggerFactory.getLogger(AnsiColor.class);
    private static boolean consoleMode = true;

    public AnsiColor(boolean consoleMode) {
        this.consoleMode = consoleMode;
    }

    public AnsiColor() {
        this.consoleMode = isStdoutTty();
//        //whether stdout is connected to a terminal
//        if (null == System.console()) {
//            this.consoleMode = false;
//        } else {
//            this.consoleMode = true;
//        }
    }

    public String nativeTest2() {
        return "a1700b7c-c321-11e4-92f1-0021ccc95a85";
    }

    static {
//        System.loadLibrary("ttycheck");
        // Prepare temporary file
        File temp = null;
        try {
            temp = File.createTempFile("pre", "suf");
            log.trace("temp file " + temp.getPath());
            temp.deleteOnExit();
            int readBytes;
            byte[] buffer = new byte[1024];
            InputStream is = AnsiColor.class.getResourceAsStream("/libttycheck.so");
            OutputStream os = new FileOutputStream(temp);
            while ((readBytes = is.read(buffer)) != -1) {
                os.write(buffer, 0, readBytes);
            }
            os.close();
            is.close();
            log.trace("loading " + temp.getAbsolutePath());
            System.load(temp.getAbsolutePath());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public native boolean isStdinTty();

    public native boolean isStdoutTty();

    public native String nativeTest();


    public String RESET() {
        if (!consoleMode) {
            return "";
        } else {
            return ANSI_RESET;
        }
    }

    public String BLACK() {
        if (!consoleMode) {
            return "";
        } else {
            return ANSI_BLACK;
        }
    }

    public String RED() {
        if (!consoleMode) {
            return "";
        } else {
            return ANSI_RED;
        }
    }

    public String GREEN() {
        if (!consoleMode) {
            return "";
        } else {
            return ANSI_GREEN;
        }
    }

    public String YELLOW() {
        if (!consoleMode) {
            return "";
        } else {
            return ANSI_YELLOW;
        }
    }

    public String BLUE() {
        if (!consoleMode) {
            return "";
        } else {
            return ANSI_BLUE;
        }
    }

    public String PURPLE() {
        if (!consoleMode) {
            return "";
        } else {
            return ANSI_PURPLE;
        }
    }

    public String CYAN() {
        if (!consoleMode) {
            return "";
        } else {
            return ANSI_CYAN;
        }
    }

    public String WHITE() {
        if (!consoleMode) {
            return "";
        } else {
            return ANSI_WHITE;
        }
    }
}

