# g++ for ReadArray to read.exe
all:ReadArray.cpp
	g++ --debug -Wall ReadArray.cpp -o read.exe
clean:
	rm read.exe
