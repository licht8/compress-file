# Checks for the necessary directories and executable
# to run the Huffman compression program. If everything is in place,
# it executes the program. If not, it provides appropriate error messages.

if (-not (Test-Path -Path "build")) {
    Write-Host "The build directory does not exist. Please run BUILD.ps1 to create it."
    exit 1
}

if (-not (Test-Path -Path "build/bin")) {
    Write-Error "The bin directory is missing. Please run BUILD.ps1 to create it."
    exit 1
}

if (Test-Path -Path "build/bin/Compress-File.exe") {
    Write-Host "Running Compress-File.exe..."
    & "build/bin/Compress-File.exe"
} else {
    Write-Error "The executable Compress-File.exe is missing. Please run BUILD.ps1 to create it."
    exit 1
}