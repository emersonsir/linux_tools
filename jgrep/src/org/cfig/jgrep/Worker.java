package org.cfig.jgrep;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by y on 2/12/15.
 */
public class Worker {
    Logger log = LoggerFactory.getLogger(this.getClass());
    private boolean bShowIndex = false;
    private boolean bShowGroup = false;
    private String regex;
    private String file;
    private boolean recurvice;//if "file" is a dir
    private boolean ignoreCase;
    private boolean useStdin;
    private AnsiColor theColor;

    public Worker(Args inArgs) {
        this.bShowIndex = inArgs.isShowIndex();
        this.bShowGroup = inArgs.isShowGroup();
        this.recurvice = inArgs.isRecurvice();
        this.regex = inArgs.getRegex();
        this.file = inArgs.getFile();
        this.ignoreCase = inArgs.isIgnoreCase();
        this.useStdin = inArgs.isUseStdin();
        if (inArgs.isForceColorOn()) {
            this.theColor = new AnsiColor(true);
        } else {
            this.theColor = new AnsiColor();
        }
    }

    public void run() {
        log.trace("in/out=" + theColor.isStdinTty() + "/" + theColor.isStdoutTty());
        Pattern p;
        if (this.ignoreCase) {
            p = Pattern.compile(regex, Pattern.CASE_INSENSITIVE);
        } else {
            p = Pattern.compile(regex);
        }
        walk(new File(file), p);
    }

    public void walk(File src, Pattern p) {
        log.trace("Walking " + src.getPath());
        if (src.isDirectory()) {
            File[] fList;
            fList = src.listFiles();
            if (fList == null) {
                //usually user can ignore this error
                log.debug(theColor.RED() + "directory wrongly empty: " + theColor.PURPLE() + src.getPath() + theColor.RESET());
                return;
            }
            for (File f : fList) {
                walk(f, p);
            }
        } else {
            log.trace("Reading " + src.getPath());
            BufferedReader br;
            try {
                if (useStdin) {
                    br = new BufferedReader(new InputStreamReader(System.in));
                    log.info("Waiting for stdin data ...");
                    match_buffer(p, br, null);
                } else {
                    br = new BufferedReader(new FileReader(src.getPath()));
                    match_buffer(p, br, src.getPath());
                }
            } catch (FileNotFoundException e) {
                //usually user can ignore this error
                log.debug(theColor.RED() + "FileNotFoundException: " + theColor.PURPLE() + src.getPath() + theColor.RESET());
            }
        }
    }

    public void match_buffer(Pattern p, BufferedReader br, String bufferName) {
        try {
            String line = null;
            int lineNo = 0;
            while ((line = br.readLine()) != null) {
                lineNo++;
                Matcher m = p.matcher(line);
                String txt_head = (recurvice ? theColor.PURPLE() + bufferName + theColor.RESET() + " +" : "") + theColor.GREEN() + lineNo + theColor.RESET();
                String txt = "";
                int s1 = 0;
                while (m.find()) {//generate a user friendly output text
                    {//code block for binary files
                        Pattern p2 = Pattern.compile("[\01\02\02\04\05\06\07\010]");
                        Matcher m2 = p2.matcher(line);
                        if (m2.find()) {
                            String txt_head2 = (recurvice ? theColor.PURPLE() + bufferName + theColor.RESET() : "");
                            log.info("Binary file " + txt_head2 + " matches");
                            return;
                        }
                    }//code block for binary files

                    if (bShowIndex) {
                        txt_head += "[" + m.start() + "," + m.end() + ")";
                    }
                    txt += line.substring(s1, m.start());
                    txt += theColor.CYAN();
                    txt += line.substring(m.start(), m.end());
                    txt += theColor.RESET();
                    s1 = m.end();

                    if (bShowGroup) {
                        for (int i = 0; i < m.groupCount(); i++) {
                            log.info("    [" + i + "]" + theColor.CYAN() + m.group(i + 1) + theColor.RESET());
                        }
                    }
                }

                //output
                if (!txt.isEmpty()) {
                    txt += line.substring(s1);
                    log.info(txt_head + ":" + txt);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
