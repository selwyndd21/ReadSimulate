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
  float coredata[12100];
  fill_n(&coredata[0], 12100, 0);

  return 0;
}











int Error(string message)
{
  cout << "Error: " << message << endl;
//system("pause");
  exit(-1);
};
