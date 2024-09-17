echo off
set MINGW32=C:\MinGW-W64\mingw32\bin
set MINGW64=C:\MinGW-W64\mingw64\bin
set Zip="C:\Program Files\7-Zip\7z.exe"
set exeName=Snake
echo on

%MINGW32%\windres addIcon.rc -O coff -F pe-i386 -o addIcon-x32.res
%MINGW64%\windres addIcon.rc -O coff -o addIcon-x64.res

%MINGW32%\g++ -static -m32 -o %exeName%-x32 main.cpp functions.cpp addIcon-x32.res
%MINGW64%\g++ -static -o %exeName%-x64 main.cpp functions.cpp addIcon-x64.res

%Zip% a -t7z -mx9 windows-x32.7z %exeName%-x32.exe
%Zip% a -t7z -mx9 windows-x64.7z %exeName%-x64.exe