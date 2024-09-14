#!/usr/bin/env python3

import sys
import os
import subprocess

# Get the Python binary from environment variable or default to 'python'
python_bin = os.environ.get('PYTHON_BIN', 'python')

# Check if the Python binary exists by trying to run it
try:
    result = subprocess.run([python_bin, '--version'], capture_output=True, text=True)
    if result.returncode != 0:
        raise FileNotFoundError
except FileNotFoundError:
    sys.stderr.write(f'exec: {python_bin}: not found\n')
    sys.exit(1)

# Argument validation
if len(sys.argv) < 2:
    sys.stdout.write('missing file name\n')
    sys.exit(1)
elif len(sys.argv) > 2:
    sys.stdout.write('only one argument is allowed\n')
    sys.exit(1)
else:
    fname = sys.argv[1]
    if os.path.exists(fname):
        with open(fname) as fobj:
            lines = fobj.readlines()
        sys.stdout.write('{} lines in {}\n'.format(len(lines), fname))
    else:
        sys.stdout.write('{} not found\n'.format(fname))
        sys.exit(1)
