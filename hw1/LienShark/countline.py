#!/usr/bin/env python3
import sys
import os.path
import subprocess
import shutil
python_bin = os.environ.get('PYTHON_BIN')
rerun_flag = os.environ.get('RERUN_FLAG')
if python_bin and not rerun_flag:
    if shutil.which(python_bin) is None:
        sys.stdout.write("exec: {}: not found.\n".format(python_bin))
        sys.exit(1)
    os.environ['RERUN_FLAG'] = '1'
    try:
        subprocess.check_call([python_bin] + sys.argv, env=os.environ)
    except subprocess.CalledProcessError:
        sys.stderr.write("Error: Failed to execute {}".format(python_bin))
        sys.exit(1)
    sys.exit(0)
if len(sys.argv) < 2:
    sys.stdout.write('missing file name\n')
elif len(sys.argv) > 2:
    sys.stdout.write('only one argument is allowed\n')
else:
    fname = sys.argv[1]
    if os.path.exists(fname):
        with open(fname) as fobj:
            lines = fobj.readlines()
        sys.stdout.write('{} lines in {}\n'.format(len(lines), fname))
    else:
        sys.stdout.write('{} not found\n'.format(fname))
