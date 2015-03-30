#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>

#include "Class_core3ddata.hpp"

using namespace std;
int Error(string message);
int extractCASE (char *filename);
int extract_rm(int cases, int steps);
//#define DEBUG_readarray

int main(int argc, char** argv )
{
  // initiate variable
  ofstream   out_file;
  ifstream   operationfile("operation.txt");
  float      time[50], power[50];
  int        CycleDay=0, inCycle=0;        // CASES in the cycle
  core3ddata core;
  float      tmp_flt=0;
  float      tmp_data[12100]={0};      // initiate vectors for a core
  int        i, j, k, t;
  int        coredata_itr=0;
  string     line;
  stringstream linestream;

  // define inputfile and outfile
  if ( argc == 1 )
  { Error("No Inputfile!"); }
  else if ( argc == 2 )
  {
    cout << "Comment: default output is set" << endl;
    line="output.txt";
  }
  else if ( argc > 2 )
  {
    line=argv[2];
  }
  out_file.open( line.c_str(), std::ofstream::trunc );
  cout << "Output file is " << line << endl;

  // separate CASE from intact file
  extractCASE( argv[1] );


  // load operation data for every CASE: dates and power_fraction
  while (getline(operationfile, line) && !operationfile.eof() && inCycle < 50 )
  {
    if (line.at(0) == 'c' || line.empty() )
    { continue; }
    linestream.str(""); linestream.clear(); // clear stringstream
    linestream.str( line );
    linestream >> time[inCycle] >> power[inCycle];
    cout << setw(7) << time[inCycle] << setw(7) << power[inCycle] << endl;

    if (power[inCycle] > 2)
    { power[inCycle]=power[inCycle]/100; }
    CycleDay = CycleDay + time[inCycle];
    inCycle++;
  }
  cout << "Total " << setw(3) << inCycle << " STEPS between " << CycleDay << " days" << endl;
  operationfile.close();

  // load all element for every CASE
  stringstream readname;
  for ( t=0 ; t < inCycle; t++)
  {
    //read the CASE file at STEP 1
    readname.str(""); readname.clear(); // clear stringstream
    readname << "CASE" << setfill('0') << setw(2) << t+1 << "01.txt";
    core.readtable( readname.str() ); // load 3-D data for CASE t
    cout << " CASE" << setw(3) << t+1 << " STEP  1" << endl;

    // AVG the POWER
    for (coredata_itr=0; coredata_itr < 12100 ; coredata_itr++)
    {
       tmp_flt = core.element( coredata_itr ) * time[t]/CycleDay * power[t];
       tmp_data[coredata_itr] = tmp_data[coredata_itr] + tmp_flt;
    }
   
#ifdef DEBUG_readarray
    // Debug tracing information
    ifstream trace_point;
    trace_point.open ("points.txt");
    ofstream trace_file;
    trace_file.open ("debug_trace", std::ofstream::app);

    int tmp_int=0;
    while (getline(trace_point, line) && tmp_int < 50)
    {
      if (line.at(0) == 'c' || line.empty() )
      { continue; }
      linestream.str(""); linestream.clear(); // clear stringstream
      linestream.str( line );
      linestream >> i >> j >> k;

      coredata_itr = 484*(k-1) + 22*j + i;
      trace_file << " Case" << setw(3) << t+1 ;
      trace_file << " (i="  << setw(2) << i+1 << ",j="  << setw(2) << j+1 << ",k="  << setw(2) << k << "):" << fixed ;
      trace_file.precision(3) ;
      trace_file << setw(3) << core.element(coredata_itr);
      trace_file <<                     "; AVG of (i=" << setw(2) << j+1 << ",k="  << setw(2) << k << "):" << fixed ;
      trace_file.precision(3) ;
      trace_file << setw(3) << tmp_data[coredata_itr] << endl;
      tmp_int++;
    }
    trace_point.close();
    trace_file.close();

    // output Debug file
    stringstream DebugName;
    ofstream debug_file;
    tmp_int = 100*(t+1) + 1; // set extract file name
    DebugName.str(""); DebugName.clear(); // clear stringstream
    DebugName << "debug_CASE" << setfill('0') << setw(4) << tmp_int << ".txt";
    debug_file.open (DebugName.str().c_str() , std::ofstream::trunc);
    // print x-z layer
    for (tmp_int=0; tmp_int < 2; tmp_int++ )
    {
      debug_file << "halfcore " << tmp_int << endl;
      for ( j=0; j < 22; j++)
      {
        debug_file << " (ROW " << setw(2) << j+1 << "/" << setfill('0') << setw(2) << 44-2*j << ")" << endl;
        for ( k=25; k > 0; k--)
        {
          debug_file << setfill(' ') << setw(3) << k ;
         for ( i=0; i < 11; i++ )
          {
            coredata_itr = 484*(k-1) + 22*j + i + 11*tmp_int ;
            tmp_flt = core.element( coredata_itr );
            //fprintf(debug_file," %6.3f", tmp_flt);
            debug_file << " " << std::fixed;
            debug_file.precision(3); 
            debug_file << tmp_flt;
          }
          debug_file << endl;
        }// for j loop
      }// for k loop
    } // halfcore
    debug_file.close();
#endif
  }// end while getline

#ifndef DEBUG_readarray
  // Remove CASE files
  extract_rm(inCycle, 2);
#endif

  // print x-y power fraction
  out_file << "Print X-Y fraction for every Z layer" << endl;
  for ( k=25; k > 0; k--)
  {
  out_file << "        1      2      3      4      5      6      7      8      9      10"
           << "     11     12     13     14     15     16     17     18     19     20"
           << "     21     22"<< endl;
    for ( j=0; j < 22; j++)
    {
      out_file << setfill(' ') << setw(3) << k << setw(3) << (j+1);
      for ( i=0; i < 22; i++ )
      {
        coredata_itr = 484*(k-1) + 22*j + i;
        tmp_flt = tmp_data[coredata_itr];
        //tmp_flt = core.element( coredata_itr );
        out_file << " "  << fixed << setw(6) << setprecision(3) << tmp_flt;
        //printf(" %6.3f", tmp_flt);
      }// for i loop
      out_file << endl;
    }// for j loop
  }// for k loop

  // print x-z power fraction
  out_file << "Print X-Z fraction for every Y layer" << endl;
  for ( j=0; j < 22; j++)
  {
    out_file << "(ROW " << setw(2) << j+1 << "/" << setw(2) << 44-2*j << ")" << endl;
    out_file << "      1      2      3      4      5      6      7      8      9      10"
             << "     11     12     13     14     15     16     17     18     19     20"
             << "     21     22"<< endl;
    for ( k=25; k > 0; k--)
    {
      out_file << setw(3) << k;
      for ( i=0; i < 22; i++ )
      {
        coredata_itr = 484*(k-1) + 22*j + i;
        tmp_flt = tmp_data[coredata_itr];
        out_file << " "  << fixed << setw(6) << setprecision(3) << tmp_flt;
      }// for i loop
      out_file << endl;
    }// for k loop
  }// for j loop

  out_file.close();

  return 0;
}







int Error(string message)
{
  cout << "Error: " << message << endl;
//system("pause");
  exit(-1);
};

