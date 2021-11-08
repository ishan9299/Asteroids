@echo off

if not exist build mkdir build

pushd build

setlocal

call "D:\Apps\Visual Studio\VC\Auxiliary\Build\vcvarsall" x64

set LinkerFlags=/I..\include

cl /MD ..\src\Asteroids.cpp ..\lib\raylib\raylib.lib user32.lib gdi32.lib shell32.lib winmm.lib %LinkerFlags%

endlocal

popd
