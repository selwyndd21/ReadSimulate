#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>

using namespace std;
int Error(string message);

int main(int argc, char** argv )
{
  ifstream myfile(argv[1] );
  if(!myfile) 
  {
//  cout << "No valid file exist!" << endl;
//  system("pause");
//  return -1;
    Error("No valid file exist!");
  }
  string line[1100], subline; //maximum line 1100
  float coredata0[12100]={0}; // initiate vectors for a core
  int i(0), j(0), k(0); // core iterators
  //int brn_case(31), brn_step(3); // total 31 cases, 3 step for each case.
  int line_itr(0), coredata_itr(0);

  /* Read file line by line */
  while(!myfile.eof())
  {
    if (line_itr > 1100) 
    { Error("Exceed array limit!! line number > 1100"); }
    getline(myfile,line[line_itr]);
    //cout << setw(3) << line_itr << " line:" << line[line_itr] << "\n";
    line_itr++;
  }
  /* Separate lines into digits, and convert to float 
  // Each table contains 25 lines: k=25, i=11, j=1
  // if j++ --> linenumber+25
  */
  cout << "Extract left core data: \n";
  line_itr=0;
  int halfcore=0; // =0, left; =1, right
  for (halfcore=0; halfcore < 2; halfcore++)
  {
    for (j=0; j < 1; j++)
    {
      cout << "(ROW " << j+1 << "/" << 44-2*j << ")" << endl;
      line_itr = 25*j + 275* halfcore; // relocate to new table
      for (k=25; k > 0; k--)
      {
        //cout << "Line number:" << line_itr << endl;
        //cout << setw(3) << k << " line:" << "\n";
        //cout << line[line_itr] << "\n   ";
        for (i=0; i < 11; i++ )
        {
          subline = line[line_itr].substr(5+7*i,5);
          // Line format: every number has 5 digit and 2 spacing, started from 5th
          float tmp_flt = atof( subline.c_str() );
          //cout << subline << ",";
          cout << setw(7) << tmp_flt << ";";
          coredata_itr = 25*k + 5*j + i + 11*halfcore;
          //cout << coredata_itr << " ";
          coredata0[coredata_itr] = tmp_flt ;
          cout << coredata0[coredata_itr] << ",";
        }
        line_itr++;
        cout << endl;
      }
    }
  }
  cout << "error"<< endl;




  return 0;
}











int Error(string message)
{
  cout << "Error: " << message << endl;
//system("pause");
  exit(-1);
};
