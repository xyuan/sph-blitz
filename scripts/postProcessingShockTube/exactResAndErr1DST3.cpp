

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

  double supportlength;// needed for norm/error calculation 
  string inputfile;// string for file name of the first input file
  int n_col=0;// number of columns in inputfile
  double x_dia;// diaphragm position of simulation shock tube
  vector<double> x_array;//array to store x values from inputfile
  /*
  //read in some data from user
  cout<<"Please enter the name of the input file containing the data for which the exact result should be calculated:\n ";
  cout<<"but this time including the (relative) path:\n";
  cout<<"for 1D particle distribution: ../../src/outdata/prtlxxxxxxxx.dat\n";
  cout<<"for 2D particle distribution: ../../results/ResultsInProgress/averagedxxxxxxxx.dat\n";
  cin>> inputfile;  
  cout<<"\n"<<"please enter the number of columns in the input file:  ";
  cin>>n_col;
  */
  n_col=8;//DELETE!!!


  string prefix("averaged");
  string suffix(".dat");
  string timestamp;
  // read file name from user
  cout<<"Please enter the time stamp (8 digits) ";
  cin>> timestamp;  
  // assemble file name
  inputfile=prefix +timestamp+suffix;
  //DELETE THE ABOVE PASSAGE!!!


  // cout<<"\n please enter support length of the simulation: ";
  // cin>>supportlength;
  // cout<<"\n";
  supportlength=0.025;
  // format of the inputfile name xxxx/x...x12345678.dat,
  // where 12345678 time in ms

  // extract time from filename:
  size_t length;
  char timeString[20];
  // cut the string containing the time off
  length=inputfile.copy(timeString,8,inputfile.size()-12);
  timeString[length]='\0';// add the end string sign
  cout << "time is (string) " << timeString << "\n";// test output
  // convert string into an integer using a stringstream
  stringstream ss(timeString); 
  int time;// time in ms
  double t;// time in s
  ss >> time;// 
  cout << "time is (int) in ms " << time << "\n";
  t=time/1e6;//convert time from ms to s
  cout << "time is (int) in s " << t << "\n";

  //reading the simulation result data which was specified by the user above
  ifstream fin(inputfile.c_str(), ios::in);
  if (!fin){
    cout<<"Initialtion: Cannot open "<< inputfile <<"! Restart program and try different file name \n";
    exit(1);
  }
  else cout<<"Starting the extraction of the positons of all particles from "<< inputfile <<" \n"; 

  // very "elegant" way of cutting off first to lines of file 
  // (as they do not contain data), but did not know any better
  string garbage;
  getline(fin,garbage);
  getline(fin,garbage);

  double buffer;// buffer to read inputfile data
  int counter=0;// counter for the current column

  while(!fin.eof()) {
    fin>>buffer;// read current value into buffer
    // if it is a value from the first column of the file (x-value)
    if(counter%n_col==0){
      x_array.push_back(buffer);// write it in the x array
    }
    counter++;// increment counter (next column)
  }  
  fin.close(); // close file when reading finished
  // remove last element (as last file entry is also written to x_array???)
  x_array.erase(x_array.end()-1);

  // visual control output for user
  cout<<"\n this is for visual control if the extraction of x values has been successful\n";
  cout<<"First value of the array (should correspond to left hand edge particle position)"<<x_array[0]<<"\n";
  cout<<"Last value of the array (should correspond to right hand edge particle position)"<<x_array[x_array.size()-1]<<"\n";

  // read x coordinate of diaphragm position (for simulation configuration)
  // from user (as exact values are always calculated for configuration 
  // around x=0) (therefore domain is translated by x_dia...)
  cout<<"\n please type x coordinate of diaphragm position of the simulation: ";
  //cin>>x_dia;
  x_dia=2;
  // define initial values for shock tube problem (needed for exact solution)
  // no need to automatically read them from 1DST.dat (where they are given
  // for simulation) as for changed conditions, p_2 has to be calculated
  // manually anyway (see below)
  const double gamma=1.4;
  // const double rho_1=0.125; 
   const double rho_1=0.1111111111111111;//for 2D const Mass particle distribution
  const double p_1=0.1;
  const double u_1=0.0;
  const double e_1=p_1/((gamma-1)*rho_1);
  const double a_1=sqrt(gamma*p_1/rho_1);
  const double rho_4=1.0;
  const double p_4=1.0;
  const double u_4=0.0;
  const double e_4=p_4/((gamma-1)*rho_4);
  const double a_4=sqrt(gamma*p_4/rho_4);
  // some little control output (to see if they are in the
  //  right order of magnitude)
  cout<<"\n a_1: "<<a_1; 
  cout<<"\n a_4: "<<a_4<<"\n";
  
  // values for exact shock solution: Anderson, Modern compressible flow
  // (third edition) sec: 7.8
  // in our case p_4=1 and p_1=0.1 the iterative solution of
  // equation (7.94) anderson for p2 is (obtained with my calculator,
  // did not manage to solve it with maxima):

  // for the 2D particle distribution with constant mass, we need a shock tube
  // case with density ratio 9 (rho_4=1, rho_1=0.11111111111) all the other values
  // remain unchanged
  
  // const double p_2=0.303130178;//for rho_4=1, rho_1=0.125
  const double p_2=0.293309753;//for rho_4=1, rho_1=0.111111111
  const double p_3=p_2; // pressure the same over contact discontinuity
  
  // rho_2 with shock relation from state 1
  const double rho_2=rho_1*(1+(gamma+1)/(gamma-1)*(p_2/p_1))/((gamma+1)/(gamma-1)+p_2/p_1);
  cout<<"\n rho_2: "<<rho_2;// little control output
  
  // rho 3 with isentropic relation from state 4 
  const double rho_3=pow((p_3/p_4),1/gamma)*rho_4;
  cout<<"\n rho_3: "<<rho_3;// little control output
  
  // sound speed in area 3
  const double a_3=sqrt(gamma*p_3/rho_3);
  cout<<"\n a_3: "<<a_3;// little control output
  
  // internal energy in 2 and 3 (ideal gas equation of state)
  const double e_2=p_2/(rho_2*(gamma-1));
  const double e_3=p_3/(rho_3*(gamma-1));
  cout<<"\n e_2: "<<e_2;// little control output
  cout<<"\n e_3: "<<e_3;// little control output
  
  // velocity behind the wave u_p (=u_2=u_3)
  // first wave velocity of the shock (7.14) Anderson
  const double W=a_1*sqrt((gamma+1)/(2*gamma)*(p_2/p_1-1)+1);
  cout<<"\n shock speed W: "<<W;// little control output
  
  //then induced velocity behind shock wave u_p with (7.15) Anderson
  const double u_p=W*(1-rho_1/rho_2);
  const double u_2=u_p;// vel. in area 2 and 3 correspond to u_p
  const double u_3=u_p;// vel. in area 2 and 3 correspond to u_p
  cout<<"\n induced velocity behind shock u_2=u_3= "<<u_3<<"\n";// control output
  
  // now iterate the position vector and calculate the exact values
  // for each og its components (=each position)
  
  
  // vectors for results
  vector<double> p_array(x_array.size(),0);
  vector<double> rho_array(x_array.size(),0);
  vector<double> u_array(x_array.size(),0);
  vector<double> e_array(x_array.size(),0);
  
  // here: shock tube is centered around x=0 (that is where diaphragm is)
  // if inputfiledata are calculated for a different diaphragm position,
  // values of x_array are translated for calculation and retranslated afertwards
  
  //translation of x values
  // could also have been done in one single for-loop togehther with the
  // actual calculation, but it seems clearer like this....
  for(int i=0;i<x_array.size();i++){
    //translate positions in a way the shock tube is centered around x=0;
    x_array[i]=x_array[i]-x_dia;
  };
  
  // actual calculation of exact schock tube values for each particle position
  // (for-loop over all particles)
  for(int i=0;i<x_array.size();i++){
    //if position is in area 4 (left hand side, before rarefaction)
    if(x_array[i]<=-1*a_4*t){
      p_array[i]=p_4;
      rho_array[i]=rho_4;
      u_array[i]=u_4;
      e_array[i]=e_4;
    }
    //if position inside rarefaction
    else if((x_array[i]>-1*a_4*t)&&(x_array[i]<=(-1*a_3+u_3)*t)){
      
      //local variables inside rarefaction
      double u,rho,p,e;
      double x=x_array[i];
      
      //velocity in rarefaction wave (7.89)
      u=2/(gamma+1)*(a_4+x/t);
      //rho in rarefaction wave (7.87)
      rho=rho_4*pow((1-(gamma-1)/2*(u/a_4)),(2/(gamma-1)));
      //p in rarefaction wave with isentropic relation
      p=p_4*pow((rho/rho_4),gamma);
      //energy with ideal gas and e=c_v*T
      e=p/(rho*(gamma-1));
      
      //writing results in vectors
      p_array[i]=p;
      rho_array[i]=rho;
      u_array[i]=u;
      e_array[i]=e;
    }
    
    //if position after rarefaction before contact discontinuity (area 3)
    else if((x_array[i]>(-1*a_3+u_3)*t)&&(x_array[i]<=u_3*t)){
     p_array[i]=p_3;
     rho_array[i]=rho_3;
     u_array[i]=u_3;
     e_array[i]=e_3;
    }
    
    //if position after contact discontinuity before shock (area 2)
    else if((x_array[i]>u_3*t)&&(x_array[i]<=W*t)){
      p_array[i]=p_2;
      rho_array[i]=rho_2;
      u_array[i]=u_2;
      e_array[i]=e_2;
    }
    
    //if position after shock (area 1)
    else if(x_array[i]>W*t){
      p_array[i]=p_1;
      rho_array[i]=rho_1;
      u_array[i]=u_1;
      e_array[i]=e_1;
    }
  }

  /*
  //assemble output file name for exact solution data
  stringstream number;//string for number
  number << setw(8) << setfill('0') <<t*1000000;
  const string outputfile = "../../results/ResultsInProgress/exact" + number.str() + ".dat";
  */
 const string outputfile="exact"+timestamp+".dat";//DELETE!!!
  // create and open outputfile
  ofstream out(outputfile.c_str());
  if (!out){
    cout<<"Initialtion: Cannot create "<<outputfile <<"! \n";
    exit(1);
  }
  else cout<<"\n writing the exact solution into "<< outputfile <<" \n"; 
  
  //write data into file (6 columns)
  for(int i=0;i<x_array.size();i++){
    out<<setprecision(9)
       << ::setw(17)<<x_array[i]+x_dia// translate  domain back to original position 
       << ::setw(17)<<0.0 //y coordinate (no relevance), just to maintain file structure
       << ::setw(17) <<rho_array[i]
       << ::setw(17)<<p_array[i]
       << ::setw(17)<<u_array[i]
       << ::setw(17)<<e_array[i]
       <<"\n";
  }
  out.close();// close outputfile
  cout<<"\n file successfully written \n";// user output
  
  // I just append the error calculation program here
  // (initially wanted to create a new file for it but almost
  // everything needed is already here, so:
  
  // again read simulation result data from file, but this time read everything
  
  vector <vector <double> > simulationData;
  
  ifstream fin3(inputfile.c_str(), ios::in);
  buffer=0;
  vector<double> row(n_col,0);// vector to save a whole row
  // throw away first to lines of input file
  getline(fin3,garbage);
  getline(fin3,garbage);
  //read rest of file
  while(!fin3.eof()){
    // read every row
    for (int i=0; i<n_col;i++){
      //problem: reads always one more than eof
      fin3>>buffer;
      row[i]=buffer; 
    }
    //append every row to 2D array (matrix) simulationData
    simulationData.push_back(row);
    
  }  
  // probably need to remove last row
  // (NO, no need here, as we consider only diaphragm +/-0.5)
  fin3.close();// close file
  
  // relative (NO, now ABSOLUTE) error (as relative nonsense for 0)
  // error vectors
  vector <double> error_rho;
  vector <double> error_p;
  vector <double> error_u;
  vector <double> error_e;
  
  for(int i=0;i<simulationData.size();i++){
   //error only for particles within +/- 0.5 of diaphragm (due to edge effect)
    if(x_array[i]>-0.5&&x_array[i]<0.5){
      error_rho.push_back(fabs((rho_array[i]-simulationData[i][2])/*/rho_array[i]*/));
      error_p.push_back(fabs((p_array[i]-simulationData[i][3])/*/p_array[i]*/));
      error_u.push_back(fabs((u_array[i]-simulationData[i][4])/*/u_array[i]*/));
      error_e.push_back(fabs((e_array[i]-simulationData[i][5])/*/e_array[i]*/));
    } 
  }
  
  // averaged relative (NO, now CUMMULATED ABSOLUTE) error ()
  double AverRelError_rho=0;
  double AverRelError_p=0;
  double AverRelError_u=0;
  double AverRelError_e=0;
  int count1=0;// counter for particles within +/- 0.5 diaphragm
  
  // calculate the cummulated absolute error
  for(int i=0;i<simulationData.size();i++){
    // only for +/- 0.5 diaphragm
    if(x_array[i]>-0.5&&x_array[i]<0.5){
      AverRelError_rho=AverRelError_rho+error_rho[count1];
      AverRelError_p=AverRelError_p+error_p[count1];
      AverRelError_u=AverRelError_u+error_u[count1];
      AverRelError_e=AverRelError_e+error_e[count1];
      count1++;
    }
  }
  
  // L norm calculation
  
  // norms for whole domain x=-0.5 to x=0.5 ("xxx ")
  // norms for domain 3 (after rarefaction before Contact Discontinuity(CD))("xxx3")
  // norms for the domain 2 (after CD before shock)("xxx2")
  double L_1NormRho=0;
  double L_1NormU=0;
  double L_1NormE=0;
  double L_2NormRho=0;
  double L_2NormU=0;
  double L_2NormE=0;
  double L_infNormRho=0;
  double L_infNormU=0;
  double L_infNormE=0;

  double L_1NormRho3=0;
  double L_1NormU3=0;
  double L_1NormE3=0;
  double L_2NormRho3=0;
  double L_2NormU3=0;
  double L_2NormE3=0;
  double L_infNormRho3=0;
  double L_infNormU3=0;
  double L_infNormE3=0;

  double L_1NormRho2=0;
  double L_1NormU2=0;
  double L_1NormE2=0;
  double L_2NormRho2=0;
  double L_2NormU2=0;
  double L_2NormE2=0;
  double L_infNormRho2=0;
  double L_infNormU2=0;
  double L_infNormE2=0;

  //variables for local error needed for norm calculation
  double deltaRho=0;
  double deltaU=0;
  double deltaE=0;
 
  
 
  int N_part=0;//number of particles in domain x=-0.5 to x=0.5
  int N_part3=0;// number of particles in domain between rarefaction and CD
  int N_part2=0;// number of particles in area between CD and shock

  //norm calculation in domain x=-0.5 to x=0.5

  // iterate all rows of simulation data matrix(=file)
  for(int i=0;i<simulationData.size();i++) {
    //  only for +/- 0.5 diaphragm (i.e test x value
    // (which is the same for simulation data and exact solution) 
    if(x_array[i]>-0.5&&x_array[i]<0.5) {
      // if x value within borders: calculate the point's contribution to the norm
      N_part++;// increment number of particles in the area
      deltaRho=fabs(rho_array[i]-simulationData[i][2]);
      deltaU=fabs(u_array[i]-simulationData[i][4]);
      deltaE=fabs(e_array[i]-simulationData[i][5]);
      // calculate L_1 norm contributions 
      L_1NormRho=L_1NormRho+deltaRho;
      L_1NormU=L_1NormU+deltaU;
      L_1NormE=L_1NormE+deltaE;
      // calculate L2 norm contributions
      L_2NormRho=L_2NormRho+pow(deltaRho,2);
      L_2NormU=L_2NormU+pow(deltaU,2);
      L_2NormE=L_2NormE+pow(deltaE,2);

      // calculate Linf norm (=maximum value)
      if(deltaRho>L_infNormRho)
	L_infNormRho=deltaRho;
      if(deltaU>L_infNormU)
	L_infNormU=deltaU;
      if(deltaE>L_infNormE)
	L_infNormE=deltaE;
    }
  }
  //divide final results (except for L_inf morms) by the number of particles in the corresponding domain
  L_1NormRho=L_1NormRho/N_part;
  L_1NormU=L_1NormU/N_part;
  L_1NormE=L_1NormE/N_part;
  L_2NormRho=L_2NormRho/N_part;
  L_2NormU=L_2NormU/N_part;
  L_2NormE=L_2NormE/N_part;

  //for L_2 norm: sqrt (according to definition)
  L_2NormRho=sqrt(L_2NormRho);
  L_2NormU=sqrt(L_2NormU);
  L_2NormE=sqrt(L_2NormE);

  // and finally normalize them with characteristic values which are 
  // (choice not unique): rho_4, e_4, u_2(=u_3)
  L_1NormRho=L_1NormRho/rho_4;
  L_1NormU=L_1NormU/u_2;
  L_1NormE=L_1NormE/e_4;
  L_2NormRho=L_2NormRho/rho_4;
  L_2NormU=L_2NormU/u_2;
  L_2NormE=L_2NormE/e_4;
  L_infNormRho= L_infNormRho/rho_4;
  L_infNormU= L_infNormU/u_2;
  L_infNormE= L_infNormE/e_4;
  
  // norm calculation in area 3 (after rarefaction before contact discontinuity)
  
  // more precisely, to get rid of the smoothing effect and to focus only
  // on the actual after shock value precision, a margin of the size
  // of the supportlength is given at both edges of area 3 
  // (see also README in <<..results/ShockTubeTestCase>>)
    
  // reset deltas to zero
  deltaRho=0;
  deltaU=0;
  deltaE=0;
  
  
  for(int i=0;i<simulationData.size();i++){
    // take into account only particles in area 3 including margin (see comment above)
    if((x_array[i]>(-1*a_3+u_3)*t+supportlength)&&(x_array[i]<=u_3*t-supportlength)){
      N_part3++;// count particle
      // calculate errors
      deltaRho=fabs(rho_array[i]-simulationData[i][2]);
      deltaU=fabs(u_array[i]-simulationData[i][4]);
      deltaE=fabs(e_array[i]-simulationData[i][5]);
      
      // calculate L_1 norm contributions 
      L_1NormRho3=L_1NormRho3+deltaRho;
      L_1NormU3=L_1NormU3+deltaU;
      L_1NormE3=L_1NormE3+deltaE;
      // calculate L2 norm contribution
      L_2NormRho3=L_2NormRho3+pow(deltaRho,2);
      L_2NormU3=L_2NormU3+pow(deltaU,2);
      L_2NormE3=L_2NormE3+pow(deltaE,2);

      // calculate Linf norm (maximum of deltas)
      if(deltaRho>L_infNormRho3)
	L_infNormRho3=deltaRho;
      if(deltaU>L_infNormU3)
	L_infNormU3=deltaU;
      if(deltaE>L_infNormE3)
	L_infNormE3=deltaE;
    }
  }
  // divide final results (except for L_inf morms) by the number
  // of particles in area 3
  L_1NormRho3=L_1NormRho3/N_part3;
  L_1NormU3=L_1NormU3/N_part3;
  L_1NormE3=L_1NormE3/N_part3;
  L_2NormRho3=L_2NormRho3/N_part3;
  L_2NormU3=L_2NormU3/N_part3;
  L_2NormE3=L_2NormE3/N_part3;

  //for L_2 norm: sqrt (according to definition)
  L_2NormRho3=sqrt(L_2NormRho3);
  L_2NormU3=sqrt(L_2NormU3);
  L_2NormE3=sqrt(L_2NormE3);
 
  // and finally normalize them with characteristic values which are 
  // (choice not unique): rho_4, e_4, u_2(=u_3)
  L_1NormRho3=L_1NormRho3/rho_4;
  L_1NormU3=L_1NormU3/u_2;
  L_1NormE3=L_1NormE3/e_4;
  L_2NormRho3=L_2NormRho3/rho_4;
  L_2NormU3=L_2NormU3/u_2;
  L_2NormE3=L_2NormE3/e_4;
  L_infNormRho3= L_infNormRho3/rho_4;
  L_infNormU3= L_infNormU3/u_2;
  L_infNormE3= L_infNormE3/e_4;


  
  // norm calculation in area2 (after contact discontinuity, before shock)
  // to get rid of the smoothing effect and to focus only on the actual
  // after shock value precision, a margin of the size of the supportlength
  // is given at both edges of area 2
  
  // reset deltas to zero
  deltaRho=0;
  deltaU=0;
  deltaE=0;
  
  for(int i=0;i<simulationData.size();i++){
    // take into account only particles in area 2 including margin (see comment above)
    if((x_array[i]>u_3*t+supportlength)&&(x_array[i]<=W*t-supportlength)){
      N_part2++;// count particle
      // calculate errors
      deltaRho=fabs(rho_array[i]-simulationData[i][2]);
      deltaU=fabs(u_array[i]-simulationData[i][4]);
      deltaE=fabs(e_array[i]-simulationData[i][5]);
      // calculate L_1 norm contributions 
      L_1NormRho2=L_1NormRho2+deltaRho;
      L_1NormU2=L_1NormU2+deltaU;
      L_1NormE2=L_1NormE2+deltaE;
      // calculate L2 norm contribution
      L_2NormRho2=L_2NormRho2+pow(deltaRho,2);
      L_2NormU2=L_2NormU2+pow(deltaU,2);
      L_2NormE2=L_2NormE2+pow(deltaE,2);

      // calculate Linf norm (maximum of deltas)
      if(deltaRho>L_infNormRho2)
	L_infNormRho2=deltaRho;
      if(deltaU>L_infNormU2)
	L_infNormU2=deltaU;
      if(deltaE>L_infNormE2)
	L_infNormE2=deltaE;
    }
  }
  // divide final results (except for L_inf morms) by the number
  // of particles in area 3
  L_1NormRho2=L_1NormRho2/N_part2;
  L_1NormU2=L_1NormU2/N_part2;
  L_1NormE2=L_1NormE2/N_part2;
  L_2NormRho2=L_2NormRho2/N_part2;
  L_2NormU2=L_2NormU2/N_part2;
  L_2NormE2=L_2NormE2/N_part2;

  //for L_2 norm: sqrt (according to definition)
  L_2NormRho2=sqrt(L_2NormRho2);
  L_2NormU2=sqrt(L_2NormU2);
  L_2NormE2=sqrt(L_2NormE2);

  // and finally normalize them with characteristic values which are 
  // (choice not unique): rho_4, e_4, u_2(=u_3)
  L_1NormRho2=L_1NormRho2/rho_4;
  L_1NormU2=L_1NormU2/u_2;
  L_1NormE2=L_1NormE2/e_4;
  L_2NormRho2=L_2NormRho2/rho_4;
  L_2NormU2=L_2NormU2/u_2;
  L_2NormE2=L_2NormE2/e_4;
  L_infNormRho2= L_infNormRho2/rho_4;
  L_infNormU2= L_infNormU2/u_2;
  L_infNormE2= L_infNormE2/e_4;
   
  // output the results in files
  
  // first output file: relative(NO, now absloute) error for
  // rho, p, u, e at each particle position
  
  // filename
  /*
  const string filename = "../../results/ResultsInProgress/relError" + number.str() + ".dat";
  */
  const string filename="relError"+timestamp+".dat";//DELETE!!!
  // create and open file
  ofstream out3(filename.c_str());
  if (!out3){
    cout<<"Initialtion: Cannot create "<<filename <<"! \n";
    exit(1);
  }
  else cout<<"\n writing relative (NO, ABSOLUTE) error of rho, p, u, e into "<< filename <<" \n"; 
  
  // write file header
  out3<<"relative (NO; ABSOLUTE) error file\n";
  out3<<" x | rho | error rho[-] | p | error p [-] | u | error u[-] | e | error e[-]\n";
  
  // counter to match the good error vector entries
  // for the corresponding x vector entries
  int count2=0;
  
  // write data (the file contains  actual data rho,p,u,r again,
  // as needed for gnuplot errorbars)
  for(int i=0;i<x_array.size();i++){
    if(x_array[i]>-0.5&&x_array[i]<0.5){
      out3<<setprecision(6)
	  << ::setw(17)<<x_array[i]+x_dia//to translate the domain back to its original position 
	  << ::setw(17)<<rho_array[i]
	  << ::setw(17)<<error_rho[count2]
	  << ::setw(17)<<p_array[i]
	  << ::setw(17)<<error_p[count2]
	  << ::setw(17)<<u_array[i]
	  << ::setw(17)<<error_u[count2]
	  << ::setw(17)<<e_array[i]
	  << ::setw(17)<<error_e[count2]
	  <<"\n";
      count2++;
    }
  }
  out3.close();// close file
  cout<<"\n error file successfully written \n";
  
  
 //second output file: global errors (norms)
 // filename
 
  /* const string filename2 = "../../results/ResultsInProgress/IntegralError" + number.str() + ".dat";
   */
 const string filename2="IntegralError"+timestamp+".dat";//DELETE!!!
  // create and open outputfile
  ofstream out4(filename2.c_str());
  if (!out4){
    cout<<"Initialtion: Cannot create "<<filename2 <<"! \n";
    exit(1);
 }
  else cout<<"\n writing norm error data into "<< filename2 <<" \n"; 
  
  // write file header
 out4<<"norm error file\n\n";
 out4<<"file structure:\n";
 out4<<"L1_rho|L1_u|L1e|L2_rho|L2_u|L2e|Linf_rho|Linf_u|Linf_e|L1_rho3|L1_u3|L1e3|L2_rho3|L2_u3|L2e3|Linf_rho3|Linf_u3|Linf_e3|L1_rho2|L1_u2|L1e2|L2_rho2|L2_u2|L2e2|Linf_rho2|Linf_u2|Linf_e2\n\n\n";


 

 out4<<setprecision(6)
     << L_1NormRho<<" "<< L_1NormU<<" "<< L_1NormE<<" "
     << L_2NormRho<<" "<< L_2NormU<<" "<< L_2NormE<<" "
     << L_infNormRho<<" "<< L_infNormU<<" "<< L_infNormE<<" "
     << L_1NormRho3<<" "<< L_1NormU3<<" "<< L_1NormE3<<" "
     << L_2NormRho3<<" "<< L_2NormU3<<" "<< L_2NormE3<<" "
     << L_infNormRho3<<" "<< L_infNormU3<<" "<< L_infNormE3<<" "
     << L_1NormRho2<<" "<< L_1NormU2<<" "<< L_1NormE2<<" "
     << L_2NormRho2<<" "<< L_2NormU2<<" "<< L_2NormE2<<" "
     << L_infNormRho2<<" "<< L_infNormU2<<" "<< L_infNormE2
     << "\n";
 
  // close output file
  out4.close();

  cout<<"\n integral error file successfully written \n";
  
  return 0;
}