#/!/bin/sh

lcov --capture --no-external --directory ../../tests/unittests/ --output-file coverage.info
echo "Displayinh coverage.info"
cat coverage.info
# genhtml coverage.info --output-directory out