#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>

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
  float      tmp_flt=0, sum_quadra=0;
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
    line="output_3DRPF.txt";
    cout << "Comment: default output is set to "<< line << endl;
  }
  else if ( argc > 2 )
  {
    line=argv[2];
  }
  out_file.open( line.c_str(), std::ofstream::trunc );
  cout << "Output file is " << line << endl;

  // separate CASE from intact file
  extractCASE( argv[1] );


  //--------------------------------------
  // load operation data for every CASE: dates and power_fraction
  //--------------------------------------
  if(!operationfile) 
  { Error("Error: No valid file exist!"); }
  while (getline(operationfile, line) && !operationfile.eof() && inCycle < 50 )
  {
    if (line.at(0) == 'c' || line.empty() )
    { continue; }
    linestream.str(""); linestream.clear(); // clear stringstream
    linestream.str( line );
    linestream >> time[inCycle] >> power[inCycle];
#ifdef DEBUG_readarray
    cout << setw(7) << time[inCycle] << setw(7) << power[inCycle] << endl;
#endif

    if (power[inCycle] > 2)
    { power[inCycle]=power[inCycle]/100; } // put percentage into ratio
    CycleDay = CycleDay + time[inCycle];
    inCycle++;
  }
  cout << "Total " << setw(3) << inCycle << " STEPS between " << CycleDay << " days" << endl;
  operationfile.close();

  //--------------------------------------
  // load all element for every CASE
  //--------------------------------------
  stringstream readname;
  for ( t=0 ; t < inCycle; t++)
  {
    //read the CASE file at STEP 1
    readname.str(""); readname.clear(); // clear stringstream
    readname << "CASE" << setfill('0') << setw(2) << t+1 << "01.txt";
    //--------------------------------------
    // load 3-D data for CASE t using Class "core"
    //--------------------------------------
    core.readtable( readname.str() ); 

    // AVG the POWER
    cout << "  Averaging the core3ddata in CASE" << setw(3) << t+1 
         << " STEP  1" << endl;
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
  out_file << endl << endl << endl;
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
        out_file << " " << fixed << setw(6) << setprecision(3) << tmp_flt;
      }// for i loop
      out_file << endl;
    }// for k loop
  }// for j loop


  // export 3D source for MAVRIC
  out_file << endl << endl << endl;
  float strength = 1.389E20;
  out_file << "Print Source Card for MAVRIC, with AVG Strength=" 
           << uppercase << scientific << strength << endl;
  cout     << "Print Source Card for MAVRIC, with AVG strength=" 
           << uppercase << scientific << strength << endl;

  t=0;
  out_file << "Print Distribution sets in Definition Block" << endl;
  for (j=0; j< 11; j++)
  {
    for (i=11; i<22; i++)
    {
      // if the column is very small -> neglect this column!
      k=25;
      coredata_itr = 484*(k-1) + 22*j + i;
      tmp_flt = tmp_data[coredata_itr]; // locate source element 
      if ( abs( tmp_flt ) < 1E-2 )
      { continue; }

      out_file << "  distribution " << setw(4) << t+2 << endl;
      out_file << "    title=\"source (i=" << setw(2) << i+1 
               << ",j=" << setw(2) << j+1 
               << ") src=" << setw(4) << t+1 << "\"" << endl;
      out_file << "    abscissa 635.9525 620.7125 605.4725 590.2325 574.9925" << endl;
      out_file << "             559.7525 544.5125 529.2725 514.0325 498.7925" << endl;
      out_file << "             483.5525 468.3125 453.0725 437.8325 422.5925" << endl;
      out_file << "             407.3525 392.1125 376.8725 361.6325 346.3925" << endl;
      out_file << "             331.1525 315.9125 300.6725 285.4325 270.1925" << endl;
      out_file << "             254.9525      end" << endl;
      out_file << "    truePDF" ;
      for (k=25; k > 0; k--)
      {
        coredata_itr = 484*(k-1) + 22*j + i;
        tmp_flt = tmp_data[coredata_itr]; // locate source element 
        out_file << "  " << setw(7) << fixed << setprecision(3) << tmp_flt;
        if ( (k-1)%5 == 0 )
        { out_file << endl << "           "; }
      }
      out_file << "end" << endl;
      out_file << "  end distribution" << endl;
      t++;
    }
  }
  out_file << "There are " << t << " sources" << endl << endl;;

  for (coredata_itr=0; coredata_itr < 12100 ; coredata_itr++)
  {
     sum_quadra= tmp_data[coredata_itr] + sum_quadra;
  };

  t=0;
  float check_sum=0;
  out_file << "Print SRC sets in Source Block" << endl;
  for (j=0; j< 11; j++)
  {
    for (i=11; i<22; i++)
    {
      // if the column is very small -> neglect this column!
      k=25;
      coredata_itr = 484*(k-1) + 22*j + i;
      tmp_flt = tmp_data[coredata_itr]; // locate source element 
      if ( abs( tmp_flt ) < 1E-2 )
      { continue; }
      tmp_flt=0;
      for (k=25; k>0; k--)
      { tmp_flt = tmp_data[coredata_itr] + tmp_flt; }

      check_sum=tmp_flt/sum_quadra*strength;
      out_file << "  src " << setw(4) << t+1 << endl;
      out_file << "    title=\"source (i=" << setw(2) << i+1 
               << ",j=" << setw(2) << j+1 
               << ") \" " << endl; 
      out_file << "    neutrons" << endl;
      out_file << "    strength=" << uppercase << scientific << check_sum << endl;
      out_file << "    cuboid 167.64 -167.64 167.64 -167.64  635.9525 254.9525" << endl;
      out_file << "    unit=" << t+1 << endl;
      out_file << "    eDistributionID=" << t+1 << endl ;
      out_file << "    zdistribution=" << t+2 << " zscaledist" << endl ;
      out_file << "  end src" << endl ;
      t++;
    }
  }
  if ( abs(check_sum/strength-1) > 1E3 )
  {cout << "Column Weighted Source is not conserved with Total Source!!\n"; }
  else
  {cout << "Column Weighted Source is conserved with Total Source\n"; }

  out_file.close();
  
  return 0;
}







int Error(string message)
{
  cout << "Error: " << message << endl;
//system("pause");
  exit(-1);
};

