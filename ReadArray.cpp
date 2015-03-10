#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>

using namespace std;
int Error(string message);
#define DEBUG_readarray

int main(int argc, char** argv )
{
  ifstream myfile(argv[1] );
  if(!myfile) 
  {
    Error("No valid file exist!");
  }
 
  int max_line=1100;
  string line[ max_line+1 ], subline; //maximum line read in


  /* Read file line by line */
  int line_itr(0);
  while( getline(myfile, line[line_itr]) && line_itr < max_line )
  {
    if (line[line_itr].size() <  80) // fill line to fit line width 80
    { line[line_itr].resize(80, ' '); } 
#ifdef DEBUG_readarray
    cout << "Line" << setw(3) << line_itr << ":" << line[line_itr] << endl;
#endif
    line_itr++;
  }
  cout << "Lines input:" << line_itr << endl;
  if (line_itr < 25*22*2-1 )
  { Error("Incomplete input file for a whole core");}

  /* Separate lines into digits, and convert to float 
  // Each table contains 25 lines: k=25, i=11, j=1
  // if j++ --> linenumber+25
  */
  line_itr=0;
  int halfcore(0), i(0), j(0), k(0); // core iterators, halfcore=0, left; =1, right
  float tmp_flt(0); // 
  float coredata0[12100]={0}; // initiate vectors for a core
  //int brn_case(31), brn_step(3); // total 31 cases, 3 step for each case.
  int coredata_itr(0);
  for (halfcore=0; halfcore < 2; halfcore++)
  {
    if (halfcore ==0 )
    { cout << "Extract left core data: \n";}
    else if (halfcore == 1)
    { cout << "Extract right core data: \n";}
    else 
    { Error("Wrong part of core");}

    for (j=0; j < 22; j++)
    {
      cout << "(ROW " << j+1 << "/" << 44-2*j << ")" << endl;
      line_itr = 25*j + 550*halfcore; // relocate to new table
      for (k=25; k > 0; k--)
      {
#ifdef DEBUG_readarray
        cout << "Line number:" << line_itr << endl;  // debug
        cout << setw(3) << k << " line:" << "\n";
        cout << line[line_itr] << "\n    ";
#endif
        for (i=0; i < 11; i++ )
        {
          subline = line[line_itr].substr(5+7*i,5);
          // Line format: every number has 5 digit and 2 spacing, started from 5th
          tmp_flt = atof( subline.c_str() );
          coredata_itr = 25*k + 5*j + i + 11*halfcore;
          coredata0[coredata_itr] = tmp_flt ;
#ifdef DEBUG_readarray
          //cout << setw(6) << subline << ",";
          //cout << setw(6) << tmp_flt << ";";
          //cout << coredata_itr << " ";
          cout << setw(6) <<coredata0[coredata_itr] << ",";
#endif
        }
        line_itr++;
#ifdef DEBUG_readarray
        cout << endl;
#endif
      }
    }
  }
  cout << "End input array"<< endl;




  return 0;
}











int Error(string message)
{
  cout << "Error: " << message << endl;
//system("pause");
  exit(-1);
};
