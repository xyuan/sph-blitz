

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <math.h>


using namespace std;

int main (){
  
  const int n_col=8;// number of columns in simulation output file
  double buffer;
  double timeInterval;
  int counter=0;
  vector<double> row(n_col,0);
  vector <vector <double> > inputFileData; // stores data read from inputfile
  vector <vector <double> > MaxVelocAllInstants;// vector for max velocities of all instants and their corresponding time value
  // to store peak velocity and time values for each period  
  vector <vector <double> >PeakVelocEachPeriod;    
  vector <double>maxVelThisInstAndTime(2,0);
  int fileCounter=0;
  
  cout<<"please enter the output time interval in s (as precised in 1DWave.tcl file:"<<endl;
  cin>>timeInterval;
  // while loop over all output intervall values
  for(;;) {
    double maxVelocThisInstant=-10000;// max velocity of current instant(=output time)
    
    // assemble input file name
    stringstream number;//string for number (time stamp)
    stringstream number2;//string for second time stamp if first one not o.k.
    stringstream number3;//string for second time stamp if second one not o.k.
    // calculate number (time stamp) for file name
    // needs to be casted to int as otherwise numbers over1,000,000 
    // have the format 1e+6 which is not ok for the file name
    number << setw(8) << setfill('0') <<(int)(fileCounter*timeInterval*1000000);
    const string inputfile = "../../src/outdata/prtl" + number.str() + ".dat";
    cout<<endl<<inputfile<<endl;

    // create and open inputfile
    ifstream fin(inputfile.c_str(), ios::in);
    // test if inputfile opened, if not try different filename
    if (!fin) {
      // this is as sometimes filenames are...999 instead of ..0000
      // because time value is truncated for timestamp of file name...
      number2 << setw(8) << setfill('0') <<(int)(fileCounter*timeInterval*1000000-1);
      const string inputfile2 = "../../src/outdata/prtl" + number2.str() + ".dat";
      cout<<endl<<inputfile2<<endl;
      // assign a new filename to the streaming object
      fin.open(inputfile2.c_str(), ifstream::in);
      // test if inputfile opened, if not try different filename
      if (!fin) {
	// this is as sometimes, when entering e.g.0.8673, program 
	// stores 0.867299999... and therefore constructs the wrong filename:
	number3 << setw(8) << setfill('0') <<(int)(fileCounter*timeInterval*1000000+1);
	const string inputfile3 = "../../src/outdata/prtl" + number3.str() + ".dat";
	cout<<endl<<inputfile3<<endl;
	// assign a new filename to the streaming object
	fin.open(inputfile3.c_str(), ifstream::in);
	
	if(!fin) {
	  cout<<"no (more)file could be found: either all files have already been processed"<<endl;
	  cout<<"or there is a problem with the file name"<<endl;
	  cout<<"to chech if all files have already been treated, here the number of files that are read by the program: "<<fileCounter<<endl;
	  break;
	}
      }
    };
    
    // while reading directly sort out the boundary particles
    while(!fin.eof()) {
      
      // very "elegant" way of cutting off first to lines of file 
      // (as they do not contain data), but did not know any better
      string garbage;
      getline(fin,garbage);
      getline(fin,garbage);
      
      for (int i=0; i<n_col&&!fin.eof();i++) {
	// problem: reads always one more than eof
	fin>>buffer;
	row[i]=buffer; 
      }
      // to be sure the last row (which is already eof and does
      // not correspond to a physical row of the file any more)
      // is not added make ID=0;
      if(fin.eof()) {
	row[6]=0;
      }
      // determine max velocity for this instant if
      // -the row does not correspond to a boundary particle
      // (for which ID=0)
           
      if(row[n_col-2]!=0) {
	inputFileData.push_back(row);
      }
    } 
    
    fin.close();// close inputfile
    
    // for te case of a traveling wave, the simulation results data files
    // correspond exclusively to T and its multiples,
    // therefore: max velocities for two consecutive instants directly obtained!

    // find max velocity this instant
    for (int i=0;i<inputFileData.size();i++) {
      
      // if it is bigger than possible previous max at this instant:
      if (inputFileData[i][4]>maxVelocThisInstant)
	maxVelocThisInstant=inputFileData[i][4];
    }
    //clear inputfile data for next file
    inputFileData.clear();

    // pair maximum velocity of this instant with corresponding time:
    maxVelThisInstAndTime[0]=maxVelocThisInstant;
    maxVelThisInstAndTime[1]=fileCounter*timeInterval;
    //put max velocity this instant in an array/vector
    PeakVelocEachPeriod.push_back(maxVelThisInstAndTime);
    //increment file counter as loop will restart for next input file
    fileCounter++;  
  }
  // end while loop over all files
  
  //output of post-processing data into files

  //first file for velocity values etc...
  const string outputfile = "../../results/ResultsInProgress/peakVelocities.dat";
  // create and open outputfile
  ofstream out(outputfile.c_str());
  
  // test if file opened
  if (!out){
    cout<<"Cannot create file "<<outputfile<<"\n" ;
    exit(1);
  }
  else cout<<"\n writing in file\n"; 
  // write file header
  out<<"peak velocity for each period and corresponding time\n";
  out<<"period number | peak velocity | adimensional peak velocity| time |adimensional time \n";
  // write data into file
  for(int i=0;i<PeakVelocEachPeriod.size();i++) {
    out<<setprecision(9)
       << ::setw(17)<<i+1 // period number (starting at 1)
       << ::setw(17)<<PeakVelocEachPeriod[i][0] // peak velocity
       << ::setw(17)<<PeakVelocEachPeriod[i][0]/PeakVelocEachPeriod[0][0] // peak velocity (adimensional)
       << ::setw(17)<<PeakVelocEachPeriod[i][1] // corresponding time    
       << ::setw(17)<<PeakVelocEachPeriod[i][1]/PeakVelocEachPeriod[1][1] // corresponding time   
       <<"\n";
  }
  out.close();// close output file
  cout<<"\n 1D Wave port-processing date written to:\n";
  cout<<"   "<<outputfile<<"\n";
  
  // second file for damping factor etc...
  const string outputfile2 = "../../results/ResultsInProgress/DampingPeriod.dat";
  // create and open outputfile
  ofstream out2(outputfile2.c_str());
  
  // test if file opened
  if (!out2){
    cout<<"Cannot create file "<<outputfile2<<"\n" ;
    exit(1);
  }
  else cout<<"\n writing in file\n"; 
  // write file header
  out2<<"Damping and periodic time\n";
  out2<<"period number (1 means: damping between period 1 and 2,...) | damping | periodic time (normalized with T of first period\n";
  // write data into file
  for(int i=0;i<PeakVelocEachPeriod.size()-1;i++) {
    out2<<setprecision(9)
       << ::setw(17)<<i+1 // period number (starting at 1)
       << ::setw(17)<<(PeakVelocEachPeriod[i+1][0]-PeakVelocEachPeriod[i][0])/-PeakVelocEachPeriod[i][0]// damping
       << ::setw(17)<<(PeakVelocEachPeriod[i+1][1]-PeakVelocEachPeriod[i][1])/PeakVelocEachPeriod[1][1]// normalized periodic time
       <<"\n";
  }
  out2.close();// close output file

  cout<<"\n 1D Wave port-processing date written to:\n";
  cout<<"   "<<outputfile2<<"\n";

  cout<<"\n program ended\n";
  return 0;
}

   