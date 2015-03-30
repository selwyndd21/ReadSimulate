#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>


using namespace std;

int main(int argc, char** argv )
{
  ifstream   operationfile("operation.txt");
  string     line;
  float      time[50], power[50];
  int        i=0;

  // load power ratio for every CASE
  while (getline(operationfile, line) && !operationfile.eof() && i < 50 )
  {
    if (line.at(0) == 'c')
    { continue; }
    stringstream linestream(line);
    linestream >> time[i] >> power[i];
    cout << setw(7) << time[i] << setw(7) << power[i] << endl;
    i++;
  }
  cout << "total i=" << i << endl;
  operationfile.close();
  return 0;
}



