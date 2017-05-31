#!/usr/bin/env python3
import subprocess
import os.path
import platform

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    def disable(self):
        self.HEADER = ''
        self.OKBLUE = ''
        self.OKGREEN = ''
        self.WARNING = ''
        self.FAIL = ''
        self.ENDC = ''

Xcolors = bcolors();
if "Linux" == platform.system():
    pass
elif "Windows" == platform.system():
    Xcolors.disable()
elif "Darwin" == platform.system():
    pass
else:
    print("Unsupported platform: %s " % platform.system())
    raise

LOG_OK=Xcolors.OKGREEN+ "  [ ok ]" + Xcolors.ENDC
LOG_WARN=Xcolors.WARNING+ "  [warn]" + Xcolors.ENDC
LOG_ERROR=Xcolors.FAIL + "  [error]" + Xcolors.ENDC
LOG_INFO=Xcolors.OKBLUE+ "  [info]" + Xcolors.ENDC

def print_error(theCmd):
    print("%s %s" % (LOG_ERROR, theCmd))
    exit(1)

def print_warn(theCmd):
    print("%s %s" % (LOG_WARN, theCmd))

def print_ok(theCmd):
    print("%s %s" % (LOG_OK, theCmd))

def print_info(theCmd):
    print("%s %s" % (LOG_INFO, theCmd))

def shell_call(theCmd, check=True):
    try:
        subprocess.check_call(theCmd, shell=True)
        print("%s %s" % (LOG_OK, theCmd))
    except subprocess.CalledProcessError:
        if check:
            print("%s %s" % (LOG_ERROR, theCmd))
            raise
        else:
            print("%s %s" % (LOG_WARN, theCmd))

def shell_say_call(theCmd):
    shell_call(theCmd, check=False)

def prepare_dir(theDir):
    if os.path.exists(theDir) and not os.path.isdir(theDir):
        os.rm(theDir)
    if not os.path.isdir(theDir):
        os.mkdir(theDir)
    print_ok(theDir + " is ready")
