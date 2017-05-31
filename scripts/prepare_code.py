#!/usr/bin/env python3
import os.path
import os
from tools import *

def find_app_root(dirname):
    if not dirname:
	    raise Exception("Illegal argument : None")
    current_dir = os.path.abspath(".")
    parent_dir = current_dir
    while True:
        target = os.path.join(parent_dir, dirname)
        if os.path.isdir(target):
            return target
        parent_dir = os.path.dirname(current_dir)
        if parent_dir == current_dir:
            return None
        current_dir = parent_dir

def get_repo_projects(repodir):
    """
     @args: repodir: xxx/.repo/
    """

print(find_app_root(".repo"))
shell_call('repo forall -c "git reset --hard"')
shell_call('repo forall -c "git clean -xdf"')
#shell_call('repo forall -c "git checkout build/berlin/1061"')
#shell_say_call('repo forall -c "git checkout yzyu/1061/ub1204_ics 2>/dev/null"')
#shell_say_call('repo forall -c "git diff build/berlin/1061 HEAD"')
