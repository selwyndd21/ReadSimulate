#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>

using namespace std;
int Error(string message);

int main(int argc, char** argv )
{
  ifstream myfile  (argv[1] );
  ofstream outfile;
  if(!myfile) 
  {
    Error("No valid file exist!");
  }
 
  string line, tmp_string, subline; //maximum line read in
  stringstream stepname;
  int cases, steps;
  int tmp_int;
  int u=0, j=0;

  /* Read file line by line */
  int line_itr=0;
  float number=0;
  while( getline(myfile, line) )
  {
    if ( line.find("CASE") == 1 && line_itr < 5000 )
    {
      stringstream linestream(line);
      linestream >> tmp_string;
      linestream >> cases >> tmp_string  >> steps;
      cout << "Line" << setw(5) << line_itr << ": CASE" << setw(2) << cases << " STEP" << setw(2) << steps << endl;
      tmp_int = cases*100 + steps;
      stepname.str(""); stepname.clear(); // clear stringstream
      stepname << "Case" << tmp_int << ".txt";
      outfile.open (stepname.str().c_str() , std::ofstream::app);
      line_itr++;
    }
    else if ( isdigit( line[2] ) )
    {
      cout << stepname.str() << outfile.is_open() << endl;
      outfile << line << endl;
    }
  }
  cout << "Lines input:" << line_itr << endl;

  return 0;
}











int Error(string message)
{
  cout << "Error: " << message << endl;
//system("pause");
  exit(-1);
};
