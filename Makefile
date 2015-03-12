# g++ for ReadArray to read.exe
# The compilers provided by the mingw-gcc, mingw64-i686-gcc, and mingw64-x86_64-gcc packages link against standard Microsoft DLLs instead of Cygwin.
all:ReadArray.cpp
	i686-pc-mingw32-g++ -static-libstdc++ -static-libgcc ReadArray.cpp -o read.exe 
#	i686-pc-mingw32-g++.exe ReadArray.cpp -o read.exe -static-libgcc -static-libstdc++
#	x86_64-w64-mingw32-g++ --debug -Wall ReadArray.cpp -o read.exe
clean:
	rm read.exe
