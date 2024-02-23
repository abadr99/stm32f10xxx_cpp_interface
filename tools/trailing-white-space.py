#   To use this script:
#       1) type python3.
#       2) add the path of this script.
#       3) add the path of the file you want to remove trailing white space from it.
#
#  Example:
#       python3 /home/mohamed-refat/Desktop/G1_8bit_MCUs_Drivers/scripts/Trailing-remove.py  
#                   /home/mohamed-refat/Desktop/G1_8bit_MCUs_Drivers/C/mcal/GPIO/GPIO.c
#
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