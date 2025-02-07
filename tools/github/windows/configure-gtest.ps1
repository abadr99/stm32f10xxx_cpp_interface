# Clone the repository
git clone https://github.com/google/googletest.git --depth 1
 
Set-Location googletest

# Create a build directory
mkdir build
Set-Location build

# Configure the build using CMake
cmake -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc ..
mingw32-make
# Build the project
cmake --build . --config Release

# Install the built files
cmake --install . --config Release
ls ../../googletest/build/lib
# List the output directory
Get-ChildItem