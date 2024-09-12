#!/usr/bin/env python3

import sys
import os
import subprocess

# Get the Python binary from environment variable or default to 'python'
python_bin = os.environ.get('PYTHON_BIN', 'python')

if len(sys.argv) < 2:
    sys.stdout.write('missing file name\n')
elif len(sys.argv) > 2:
    sys.stdout.write('only one argument is allowed\n')
else:
    fname = sys.argv[1]
    if os.path.exists(fname):
        try:
            # Switch the Python binary for execution
            result = subprocess.run([python_bin, '--version'], capture_output=True, text=True)
            if result.returncode != 0:
                raise FileNotFoundError
            with open(fname) as fobj:
                lines = fobj.readlines()
            sys.stdout.write('{} lines in {}\n'.format(len(lines), fname))
        except FileNotFoundError:
            sys.stderr.write(f'exec: {python_bin}: not found\n')
    else:
        sys.stdout.write(f'{fname} not found\n')
