#!/usr/bin/env python

import sys
if len(sys.argv) < 2 :
    print(__file__,": Usage Error python3  ", __file__, "path/to/file")

else:
    File = sys.argv[1]
    with open(File, 'r') as file:
        lines = file.readlines()
    with open(File, 'w') as file:
        for line in lines:
            # rstrip remove all trailing white spaces and the endline '\n'
            # so we concatenate '\n' with the line
            file.write(line.rstrip() + '\n')