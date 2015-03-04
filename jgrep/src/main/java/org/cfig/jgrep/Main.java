package org.cfig.jgrep;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.security.CodeSource;
import java.security.ProtectionDomain;
import java.util.jar.Attributes;
import java.util.jar.JarInputStream;
import java.util.jar.Manifest;

public class Main {
    private static final String JGREP_VERSION = "JGREP_VERSION";
    private static final String BUILD_TIME = "BUILD_TIME";
    static Logger log = LoggerFactory.getLogger("main");

    private static void printVersion() {
        ProtectionDomain pd = Main.class.getProtectionDomain();
        CodeSource cs = pd.getCodeSource();
        URL u = cs.getLocation();

        try {
            InputStream is = u.openStream();
            JarInputStream jis = new JarInputStream(is);
            Manifest m = jis.getManifest();
            if (m != null) {
                Attributes as = m.getMainAttributes();
                log.info("jgrep version " + as.getValue(JGREP_VERSION));
                log.info("built time " + as.getValue(BUILD_TIME));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        for (int i = 0; i < args.length; i++) {
            log.trace(i + " " + args[i]);
        }

        try {
            NativeHelper.loadLibraryFromJar("/libttycheck.so");
        } catch (IOException e) {
            log.info("Internal error: can not load libttycheck.so");
            return;
        }

        Args aArgs = new Args();
        if (!aArgs.parse(args)) {
            aArgs.printUsage();
            return;
        }

        if (aArgs.isShowHelp()) {
            aArgs.printUsage();
            return;
        }

        if (aArgs.isShowVersion()) {
            printVersion();
            return;
        }

        Worker aW = new Worker(aArgs);
        log.trace(aArgs.toString());
        aW.run();
    }
}
