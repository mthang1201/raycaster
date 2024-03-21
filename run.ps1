if ($exeFiles.Count -gt 0) {
    rm bin/Game.exe
}

cd build
cmake -G "MinGW Makefiles" ..
# cmake -G "CodeBlocks - MinGW Makefiles" ..
cmake --build .

if ($LASTEXITCODE -eq 0) {
    ./../bin/Game
}