echo off
set MINGW32=C:\MinGW-W64\mingw32\bin
set MINGW64=C:\MinGW-W64\mingw64\bin
echo on

%MINGW64%\windres addIcon.rc -O coff -o addIcon-x64.res
%MINGW32%\windres addIcon.rc -O coff -F pe-i386 -o addIcon-x32.res
%MINGW64%\g++ -static -o Snake-x64 main.cpp functions.cpp addIcon-x64.res
%MINGW32%\g++ -static -m32 -o Snake-x32 main.cpp functions.cpp addIcon-x32.res