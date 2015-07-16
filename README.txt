File Explanation
----------------------------------------
Compiled execution file:
  3DRPF_read.exe:  Main program compile for Linux
  win_static_3DRPF_read.exe:  Main program compile for Windows

Source codes:
  AVG_3DRPF_perSTEP.cpp
  Class_core3ddata.hpp
  function_splitCASE.cpp
  Makefile
  mingw_make.bat

Miscellaneous:
  bash.sh
  test inputs are put: example/
  Authority file: LICENSE
  Operation length and power ration is operation.txt
  The read me file: README.txt



Compile method
----------------------------------------
For windows with mingw compiler, double click the mingw_make.bat file.
Noting that the system the mingw version g++ should be installed and could be found in "cmd" environment.

For Linux system, use command "make" to compile.
Packages make, g++ are needed.

Compile the 3DRPF_read.exe under linux environment
--------------------
$ make rpf

Compile the 3DRPF_read.exe under Wiundows using mingw
--------------------
$ x86_64-w64-mingw32-g++.exe --debug -Wall -static-libstdc++ -static-libgcc AVG_3DRPF_perSTEP.cpp function_splitCASE.cpp -o win_static_3DRPF_read.exe



Execution
----------------------------------------

Under Linux environment
--------------------
./3DRPF_read.exe example/3DRPF_cs2cy26.txt

Use the program in Windows
--------------------
drag the "3DRPF_cs2cy26.txt" file into "win_static_3DRPF_read.exe"

The output file would be "output_3DRPF".



