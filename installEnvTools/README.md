# OUTDATED

## Allow script execution
`Set-ExecutionPolicy RemoteSigned`

## Clone the project
`cd C:\; mkdir code; cd code; git clone https://github.com/mthang1201/Game.git`

## ~~Install MSYS2~~
`pacman -S --needed base-devel git mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make`

## Install CMake
~~`Move-Item -Path "C:\code\Game\installEnvTools\cmake-3.29.0-rc2-windows-x86_64" -Destination "C:\Program Files\CMake"`~~

## Move SDL folder
`Move-Item -Path "C:\code\Game\installEnvTools\SDL_mingw" -Destination "C:\code\SDL_mingw"`

## Install extensions for vscode
`code --install-extension "C:\code\Game\installEnvTools\ms-vscode.cpptools-extension-pack-1.3.0.vsix"`

## Install vcpkg (Optional)
```
cd "C:\msys64\ucrt64\bin"
git clone https://github.com/Microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
vcpkg install sdl2 sdl2_image sdl2_ttf sdl2_mixer
setx VCPKG_DEFAULT_BINARY_CACHE "C:\msys64\ucrt64\bin\vcpkg\archives"
setx VCPKG_DEFAULT_TRIPLET "x64-windows"
```

## Set environment variables
```
setx Path "%Path%;C:\msys64\ucrt64\bin;C:\msys64\usr\bin;C:\Users\Minh Thang Bui\AppData\Local\Programs\Microsoft VS Code\bin;C:\Program Files\CMake\bin"
```
add /M for system environment variables

## Directory tree
```
C:/
│
├── msys2/
│   ├── ucrt64/
│   │   ├── bin/
│   │       ├── vcpkg/
│   └── ...
├── code/
    ├── SDL_mingw/
    ├── Game/
```

## Important Notice
ATTENTION: These instructions are tailored specifically for my school machine. Do not attempt to follow them. The proper instructions are provided in the README.md file located in the root folder of this project.
