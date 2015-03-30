# g++ for ReadArray to read.exe
# The compilers provided by the mingw-gcc, mingw64-i686-gcc, and mingw64-x86_64-gcc packages link against standard Microsoft DLLs instead of Cygwin.
CFLAG=--debug -Wall -static-libstdc++ -static-libgcc
all:AVG_3D_perSTEP.cpp function_splitCASE.cpp
	g++ $(CFLAG) AVG_3D_perSTEP.cpp function_splitCASE.cpp -o read.exe 
	i686-pc-mingw32-g++ $(CFLAG) AVG_3D_perSTEP.cpp function_splitCASE.cpp -o win32_read.exe 
#	x86_64-w64-mingw32-g++ --debug -Wall ReadArray.cpp -o read.exe
clean:
	rm read.exe
