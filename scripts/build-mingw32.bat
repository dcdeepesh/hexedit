@ECHO OFF
cd ..
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make clean
mingw32-make
cd ..
cd scripts