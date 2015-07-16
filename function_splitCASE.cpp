#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>

//#define DEBUG_readarray

using namespace std;
int Error(string message);

int extractCASE (char *filename)
{
  ifstream myfile  (filename );
  ofstream outfile;
  if(!myfile) 
  {
    Error(" extractCASE: No valid file exist!");
  }
 
  string line, tmp_string; //maximum line read in
  stringstream stepname;
  int cases, steps;
  int tmp_int;

  /* Read file line by line */
  int line_itr=0;
  while( getline(myfile, line) )
  {
    if ( line.find("CASE") == 1 && line_itr < 5000 )
    {
      stringstream linestream(line);
      linestream >> tmp_string; //eat "CASE"
      linestream >> cases >> tmp_string  >> steps; // read CASE ## and STEP ##
#ifdef DEBUG_readarray
      cout << "Line" << setw(5) << line_itr << ": CASE" << setw(2) << cases << " STEP" << setw(2) << steps << endl;
#endif
      tmp_int = cases*100 + steps; // set extract file name
      outfile.close (); // close old output
      stepname.str(""); stepname.clear(); // clear stringstream
      stepname << "CASE" << setfill('0') << setw(4) << tmp_int << ".txt";
      outfile.open (stepname.str().c_str() , std::ofstream::app);
      line_itr++;
    }
    else if ( isdigit( line[2] ) )
    {
#ifdef DEBUG_readarray
      cout << stepname.str() << outfile.is_open() << endl;
#endif
      outfile << line << endl;
    }
  }
#ifdef DEBUG_readarray
  cout << " extractCASE: Lines input:" << line_itr << endl;
#endif

  return 0;
}





int extract_rm(int cases, int steps)
{
  //cout << "in rm function" << endl;
  stringstream stepname;
  for (int i=cases; i > 0; i--)
  {
    for (int j=steps; j >= 0; j--)
    {
      int tmp_int = i*100 + j; // set extract file name
      stepname.str(""); stepname.clear(); // clear stringstream
      stepname << "CASE" << setfill('0') << setw(4) << tmp_int << ".txt";
      //cout << "try to delete " << stepname.str().c_str() << endl;
      remove( stepname.str().c_str() ) ;
    }
  }
  
  return 0;
}; 


