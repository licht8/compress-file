if (-not (Get-Command make -ErrorAction SilentlyContinue)) {
    Write-Error "Make is not installed. Please install make."
    exit 1
}

if (-not (Test-Path -Path "Makefile")) {
    Write-Error "Makefile not found in the current directory."
    exit 1
}

if (Test-Path -Path "logs") {
    Write-Host "Logs directory found. Deleting it..."
    Remove-Item -Recurse -Force "logs"
}

New-Item -ItemType Directory -Path "logs"

if (Test-Path -Path "build") {
    Write-Host "Build directory found. Running make clean..."
    make clean
}

Write-Host "Starting project build..."
$start_time = Get-Date

try {
    make 2>&1 | Tee-Object -FilePath "logs/build.log"
    $end_time = Get-Date
    $duration = $end_time - $start_time
    Write-Host ("Build completed successfully in {0}" -f $duration)

    if (-not (Test-Path -Path "build/logs")) {
        New-Item -ItemType Directory -Path "build/logs"
    }
    Move-Item -Path "logs/*" -Destination "build/logs/"

    Remove-Item -Force "logs"
} catch {
    Write-Error "Error during project build."
    exit 1
}
