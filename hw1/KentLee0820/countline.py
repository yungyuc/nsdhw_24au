##!/bin/bash
"exec" "$PYTHON_BIN" "$0" "$@"

import sys
import os.path


# print(os.environ['PYTHON_BIN'])

if os.environ['PYTHON_BIN'] != 'python2' and os.environ['PYTHON_BIN'] != 'python3':
    sys.stdout.write('exec: {}: not found'.format(os.environ['PYTHON_BIN']))
    sys.exit(1)

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
