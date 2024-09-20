# Define download URL and destination
$downloadUrl = "https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2?rev=78196d3461ba4c9089a67b5f33edf82a&hash=5631ACEF1F8F237389F14B41566964EC"
$destinationFolder = "C:\opt"
$destinationFile = "${destinationFolder}\gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2"

# Create destination folder if it doesn't exist
if (-not (Test-Path $destinationFolder)) {
    Write-Host "Creating directory: ${destinationFolder}"
    New-Item -Path $destinationFolder -ItemType Directory
}

# Download the file with retries
$retryCount = 3
for ($i = 1; $i -le $retryCount; $i++) {
    try {
        Write-Host "Attempt ${i}: Downloading GCC ARM toolchain..."
        Invoke-WebRequest -Uri $downloadUrl -OutFile $destinationFile -UseBasicParsing -Verbose
        if (Test-Path $destinationFile) {
            Write-Host "Download successful!"
            break
        }
    } catch {
        Write-Host "Download failed on attempt ${i}. Retrying..."
        Start-Sleep -Seconds 10
    }
}

if (-not (Test-Path $destinationFile)) {
    Write-Host "Error: Failed to download the file after ${retryCount} attempts."
    exit 1
}

# Extract the tar.bz2 file using 7zip (which is available on GitHub runners)
Write-Host "Extracting the toolchain using 7zip..."
if (-not (Get-Command "7z" -ErrorAction SilentlyContinue)) {
    Write-Host "Error: '7z' is not available. Please ensure 7zip is installed."
    exit 1
}

# Use 7zip to extract the file
7z x $destinationFile -o$destinationFolder

# Optionally, update the PATH (adding the bin folder to the system PATH environment variable)
$binPath = "${destinationFolder}\gcc-arm-none-eabi-10.3-2021.10\bin"
[System.Environment]::SetEnvironmentVariable("Path", $env:$GITHUB_PATH + ";${binPath}", [System.EnvironmentVariableTarget]::Machine)

Write-Host "GCC ARM toolchain installation complete. The bin directory has been added to the PATH."

