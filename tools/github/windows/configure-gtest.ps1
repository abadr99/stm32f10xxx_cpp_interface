# Clone the repository
Set-Location $env:GITHUB_WORKSPACE
git clone https://github.com/google/googletest.git --depth 1
Set-Location googletest

# Create a build directory
mkdir build
Set-Location build

# Configure the build using CMake
cmake .. -G "Ninja" -A x64

# Build the project
cmake --build . --config Release

# Install the built files
cmake --install . --config Release

# List the output directory
Get-ChildItem