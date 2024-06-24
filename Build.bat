@echo off
cmake.exe -DCMAKE_BUILD_TYPE:STRING=Release -S . -B Build
cmake.exe --build Build -j 8 --target XMOJ-Client
