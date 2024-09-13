#/!/bin/sh

lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory out