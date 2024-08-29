"""
This script is used to parse input file that used to selective compilation
i.e. (file that contains files that will be compiled).

This parser takes file that contains file-names and print file-names
The scripts supports the following:
    1) removing double slash comments '//'

How to run script?
python3 -f path/to/input/file
"""

import argparse
import re

comment_pattern = re.compile(r'^\s*//')
parent_dir_pattern = re.compile(r'(\w+)\s*\{',)

def ParseOptions():
    parser = argparse.ArgumentParser(description="A script to demonstrate command-line argument parsing.")
    parser.add_argument('-f', '--file', type=str, help="path to input file", required=True)
    return parser

def ParseInputFile(file_path):
    files_to_be_compiled = []
    with open(file_path, 'r') as file:
        lines = file.readlines()
    
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        
        # -- Check if the line is a comment line or empty
        if comment_pattern.match(line) or not line:
            i += 1
            continue
        
        # -- If we are at the beginning of a block
        match = parent_dir_pattern.match(line)
        if match:
            parent_dir = match.group(1)
            i += 1
            while i < len(lines):
                line = lines[i].strip()
                if line == '}':  # End of the block
                    i += 1
                    break
                if line and not comment_pattern.match(line):
                    file_full_path = f"{parent_dir}/{line}\n"
                    files_to_be_compiled.append(file_full_path)
                i += 1
        else:
            i += 1

    return files_to_be_compiled


def main():
    input_file = ParseOptions().parse_args().file
    files_to_be_compiled = ParseInputFile(input_file)
    
    for file in files_to_be_compiled:
        print(file, end='')


if __name__ == "__main__":
    main()