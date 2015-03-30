#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <string>

//#define DEBUG_readarray

using namespace std;

class core3ddata
{
public:
  // Constructor
  core3ddata();
  // parameters
  // function
  int readtable (string filename);
  float element (int ele_itr);//return element
private:
  string line[1101], subline; //maximum line read in
  float  coredata[12100];      // initiate for a core
  int    max_line;
  int    line_itr, coredata_itr;
  int    halfcore, i, j, k;      // core iterators, halfcore=0, left; =1, right
  float  tmp_flt;
  //int brn_case(31), brn_step(3); // total 31 cases, 3 step for each case.
};

core3ddata::core3ddata()// Constructor
{
  fill_n( &coredata[0], 12100, 0); // reset coredata to 0
  max_line=1100;
}

int core3ddata::readtable (string filename)
{
  ifstream myfile(filename.c_str() );
  cout << "in Class core3ddata: Read " << filename << endl;
  if(!myfile) 
  {
    cout << "Error: No valid file exist!" << endl;
    exit(-1);
  }

  // Read file line by line
  line_itr=0;
  while( getline(myfile, line[line_itr]) && line_itr < max_line )
  {
    if (line[line_itr].size() <  80) // fill line to fit line width 80
    { line[line_itr].resize(80, ' '); } 
#ifdef DEBUG_readarray
    cout << "Line" << setw(3) << line_itr << ":" << line[line_itr] << endl;
#endif
    line_itr++;
  }
  cout << "in Class core3ddata: Lines are read:" << line_itr << endl;
  if (line_itr < 25*22*2-1 )
  {
    cout << "Error: in Class core3ddata: Incomplete input file for a whole core" << endl;
    exit(-1);
  }
  
  // Separate lines into digits, and convert to float 
  // Each table contains 25 lines: k=25, i=11, j=1
  // if j++ --> linenumber+25
  //
  for (halfcore=0; halfcore < 2; halfcore++)
  {
#ifdef DEBUG_readarray // debug info
    if (halfcore == 0 )
    { cout << "in Class core3ddata: Extract left core data: \n";}
    else if (halfcore == 1)
    { cout << "in Class core3ddata: Extract right core data: \n";}
    else 
    {
      cout << "Error: in Class core3ddata: Wrong part of core" << endl;
      exit(-1);
    }
#endif

    for (j=0; j < 22; j++)
    {
#ifdef DEBUG_readarray // debug info
      cout << "(ROW " << j+1 << "/" << 44-2*j << ")" << endl;
#endif
      line_itr = 25*j + 550*halfcore; // relocate to new table
      for (k=25; k > 0; k--)
      {
        subline = line[line_itr].substr(1,2);
        int tmp_int = atof ( subline.c_str() );
        if (k != tmp_int)
        {
          cout << "k=" << k << ", line=" << tmp_int << endl;
          cout << "Error: in Class core3ddata: wrong read in for k" << endl;
          exit(-1);
        }
#ifdef DEBUG_readarray // debug info
        cout << "Line number:" << line_itr << endl;  
        cout << setw(3) << k << " line:" << "\n";
        cout << line[line_itr] << "\n    ";
#endif
        for (i=0; i < 11; i++ )
        {
          subline = line[line_itr].substr(4+7*i,6);
          // Line format: every number has 5 digit and 2 spacing, started from 5th
          tmp_flt = atof( subline.c_str() );
          coredata_itr = 484*(k-1) + 22*j + i + 11*halfcore;
          coredata[coredata_itr] = tmp_flt ;
#ifdef DEBUG_readarray
          //cout << setw(6) << subline << ",";
          //cout << setw(6) << tmp_flt << ";";
          //cout << coredata_itr << " ";
          cout << setw(6) <<coredata[coredata_itr] << ",";
#endif
        }
        line_itr++;
#ifdef DEBUG_readarray
        cout << endl;
#endif
      }// for k loop
    }// for j loop
  }
  // Print Summary
  tmp_flt = 0;
  for (coredata_itr=0; coredata_itr<12100; coredata_itr++)
  {
    tmp_flt = tmp_flt + coredata[coredata_itr];
  }
  cout << "in Class core3ddata: Read " << filename << " with Normalized Power " << tmp_flt << endl;
  myfile.close();
  return 0;
}

float core3ddata::element (int ele_itr)
{
  return coredata[ele_itr];
}

