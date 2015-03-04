package org.cfig.jgrep;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by y on 3/4/15.
 */
public class BinaryChecker {
    private Logger log = LoggerFactory.getLogger(this.getClass());

    public boolean isTextFile(String file) throws IOException {
        StringBuilder sb = new StringBuilder();
        String ret = null;

        String command[] = new String[]{"file", "--brief", file};
        Process p = Runtime.getRuntime().exec(command);

        BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()), 1024);
        String line;
        if ((line = br.readLine()) != null) {
            log.debug(line);
            ret = line;
        }

        if (null != ret) {
            if (ret.indexOf("text") > 0) {
                return true;
            }
        }

        return false;
    }

    /*
        this function is buggy, needs to be refined
     */
    @Deprecated
    public boolean isTextLine(String line) {
        Pattern p2 = Pattern.compile("[\020-\040]");
        Matcher m2 = p2.matcher(line);
        if (m2.find()) {
            return false;
        }

        return true;
    }
}
