#ifndef OUTPUT_H
#define OUTPUT_H
/// \file output.h 
/// \brief Output the computational results

/// Output class 
class Output {
	
	///the project name
  std::string Project_name;

	int number_of_materials;
	///the inital particle distance
	double delta;
	///cells matrix for real particles
	int x_cells, y_cells;
	///the ratio between smoothing length and inital particle distance
	int hdelta; 
	int simu_mode;

public:

	///constructor
	Output(Initiation &ini);

	///output particle positions respected different materials
	void OutputParticle(Hydrodynamics &hydro, Boundary &boundary, 
						double Time, Initiation &ini);

	///Output real particle data for restart the computation
	void OutRestart(Hydrodynamics &hydro, double Time);
};

#endif //OUTPUT_H
