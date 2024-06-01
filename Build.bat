@echo off
cmake.exe -DCMAKE_BUILD_TYPE:STRING=Release -S Backend -B Build
cmake.exe --build Build -j 8
