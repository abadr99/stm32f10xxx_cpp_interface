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

# Install gtest using vcpkg
Write-Host "Installing Google Test (gtest)..."
.\vcpkg install gtest

# Optionally, integrate vcpkg with MSBuild to simplify project setup
Write-Host "Integrating vcpkg with MSBuild..."
.\vcpkg integrate install

Write-Host "Google Test (gtest) installation complete."
