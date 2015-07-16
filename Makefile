# g++ for ReadArray to read.exe
# The compilers provided by the mingw-gcc, mingw64-i686-gcc, and mingw64-x86_64-gcc packages link against standard Microsoft DLLs instead of Cygwin.
CFLAG=--debug -Wall -static-libstdc++ -static-libgcc
all:AVG_3DRPF_perSTEP.cpp AVG_3DVOI_perSTEP.cpp
	g++ $(CFLAG) AVG_3DRPF_perSTEP.cpp function_splitCASE.cpp -o 3DRPF_read.exe 
	g++ $(CFLAG) AVG_3DVOI_perSTEP.cpp function_splitCASE.cpp -o 3DVOI_read.exe 
rpf:AVG_3DRPF_perSTEP.cpp function_splitCASE.cpp
	g++ $(CFLAG) AVG_3DRPF_perSTEP.cpp function_splitCASE.cpp -o 3DRPF_read.exe 
voi:AVG_3DVOI_perSTEP.cpp function_splitCASE.cpp
	g++ $(CFLAG) AVG_3DVOI_perSTEP.cpp function_splitCASE.cpp -o 3DVOI_read.exe 
clean:
	rm read.exe
