@echo off

REM SDL 2 DLLs
echo SDL2 DLLs:
cd SDL2
call "DeployDLL.bat"
cd ..

REM SDL_image 2 DLLS
echo SDL2_image DLLs:
cd SDL2_image
call "DeployDLL.bat"
cd ..
