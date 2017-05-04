@echo off

echo "Build project files ..."

rem First create the build folder
mkdir build

cd build
cmake "../" -G "Visual Studio 14 2015 Win64"
