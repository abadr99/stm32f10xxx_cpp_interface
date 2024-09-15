#/!/bin/sh
pwd
chmod 777 ../../tests/unittests
lcov --capture --no-external --directory ../../tests/unittests/ --output-file ../../coverage.info
echo "Displaying coverage.info"
cat ../../coverage.info
# genhtml coverage.info --output-directory out