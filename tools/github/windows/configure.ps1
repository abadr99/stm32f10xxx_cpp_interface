# Define download URL and destination
$downloadUrl = "https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2?rev=78196d3461ba4c9089a67b5f33edf82a&hash=5631ACEF1F8F237389F14B41566964EC"
$destinationFolder = "C:\opt"
$destinationFile = "$destinationFolder\gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2"

# Create destination folder if it doesn't exist
if (-not (Test-Path $destinationFolder)) {
    New-Item -Path $destinationFolder -ItemType Directory
}

# Download the file
Write-Host "Downloading GCC ARM toolchain..."
Invoke-WebRequest -Uri $downloadUrl -OutFile $destinationFile

# Wait for 30 seconds
Start-Sleep -Seconds 30

# Extract the tar.bz2 file
Write-Host "Extracting the toolchain..."
# Use tar command to extract (assumes you have tar installed, either via WSL or Git Bash)
tar -xvjf $destinationFile -C $destinationFolder

# Optionally, update the PATH (adding the bin folder to the system PATH environment variable)
$binPath = "$destinationFolder\gcc-arm-none-eabi-10.3-2021.10\bin"
[System.Environment]::SetEnvironmentVariable("Path", $env:Path + ";$binPath", [System.EnvironmentVariableTarget]::Machine)

Write-Host "GCC ARM toolchain installation complete. The bin directory has been added to the PATH."
