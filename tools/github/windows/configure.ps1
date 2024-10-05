
echo "--- Install Chocolatey"
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

echo "--- Install ARM GCC Toolchain"
choco install -y gcc-arm-embedded

echo "--- Add ARM GCC to PATH"
$Env:Path += ';C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2021.10\bin'