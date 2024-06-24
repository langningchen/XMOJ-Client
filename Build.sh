cmake -DCMAKE_BUILD_TYPE:STRING=Release -S . -B Build
cmake --build Build -j 8 --target XMOJ-Client
