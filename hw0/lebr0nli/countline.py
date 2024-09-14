#!/usr/bin/env python3

import os.path
import sys

if len(sys.argv) < 2:
    print("missing file name")
elif len(sys.argv) > 2:
    print("only one argument is allowed")
else:
    fname = sys.argv[1]
    if os.path.exists(fname):
        with open(fname) as fobj:
            lines = fobj.readlines()
        print(f"{len(lines)} lines in {fname}")
    else:
        print(f"{fname} not found")
