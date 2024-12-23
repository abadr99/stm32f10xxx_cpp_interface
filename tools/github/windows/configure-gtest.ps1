# Define the vcpkg installation path
$vcpkgPath = "$env:USERPROFILE\vcpkg"

# Check if vcpkg is installed, if not, clone the vcpkg repository and set it up
if (-not (Test-Path $vcpkgPath)) {
    Write-Host "vcpkg not found. Installing vcpkg..."
    git clone https://github.com/microsoft/vcpkg.git $vcpkgPath
    cd $vcpkgPath
    .\bootstrap-vcpkg.bat
} else {
    Write-Host "vcpkg already installed. Proceeding..."
    cd $vcpkgPath
}


Write-Host "Installing Google Test (gtest)..."
.\vcpkg install gtest:x64-mingw-dynamic

Write-Host "Checking if vcpkg package is installed successfully"
vcpkg list
ls C:\Users\runneradmin\vcpkg\installed\x64-mingw-dynamic\include\gtest

# Optionally, integrate vcpkg with MSBuild to simplify project setup
Write-Host "Integrating vcpkg with MSBuild..."
.\vcpkg integrate install

Write-Host "Google Test (gtest) installation complete."
