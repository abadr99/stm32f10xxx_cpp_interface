#!/usr/bin/env python
import sys
import argparse
import re
from pathlib import Path

# Global variables
errors_ctr = 0
error_msgs = []

def Parse():
    parser = argparse.ArgumentParser(description="")
    parser.add_argument('-d', '--dir', type=str, help="path to main directory", required=True)
    return parser

def GetFiles(parser):
    main_dir = Path(parser.parse_args().dir)
    # Find all .cpp, .h, and .hpp files
    files = list(main_dir.rglob('*.cpp')) + list(main_dir.rglob('*.h')) + list(main_dir.rglob('*.hpp'))
    return [str(file) for file in files]

# Rule to check if commit id is present or not
# This should be like: // commit-id: 1234aabbccd
def CheckCommitID(file):
    global errors_ctr  # Declare global to modify
    global error_msgs  # Declare global to modify

    commit_id_pattern = re.compile(r'//\s*commit-id:\s*([a-fA-F0-9]{40})')

    with open(file, 'r') as f:
        content = f.read()
        
        # Search for the commit-id pattern in the file content
        match = commit_id_pattern.search(content)
        
        if not match:
            # If no match, increment error count and store message
            print(f"{file}: Should have comment with commit-id e.g. // commit-id: valid-hash-commit")
            error_msgs.append(f"{file}: Should have comment with commit-id e.g. // commit-id: valid-hash-commit")
            errors_ctr += 1
        else:
            print(f"Done processing {file}")

def Epilogue():
    # Print total errors and detailed messages
    global errors_ctr
    global error_msgs
    
    print(f"Total errors found: {errors_ctr}")
    for msg in error_msgs:
        print(msg)

def main():
    parser = Parse()
    files = GetFiles(parser)
    
    # --- MAIN LOOP
    for file in files:
        CheckCommitID(file)  
    
    Epilogue()
    
    global errors_ctr
    if errors_ctr > 0:
        sys.exit(1)
    else:
        sys.exit(0)
    
if __name__ == '__main__':
    main()
