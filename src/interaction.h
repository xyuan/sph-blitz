#ifndef INTERACTION_H
#define INTERACTION_H
/// \file interaction.h 
/// \brief Defines interaction between particles

#include "glbtype.h"


/// Defines interaction between particles
class Interaction {


	//particle pair
	spParticle Org;	///<pointer to particle with larger ID (of particle pair)
	spParticle Dest;	///<pointer to particle with smaller ID (of particle pair)
	

	double mi;///<mass particle i
	double rmi;///<reciprocal value of mass particle i
	double etai;///<viscosity for particle i
	double mj;///<mass particle j
	double rmj;///<reciprocal value of mass particle j
	double etaj;///<viscosity for particle j

	double piij;///Monaghan artificial viscosity

	//distance between the two particles, weight and derivatives
	double rij;///<distance between 2 particles
        double rrij;///< reciprocal value of distance between 2 particles
        double Wij;///<<b>!!!question!!!<b>
        double Fij;///<<b>!!!question!!!<b>
        double Wij2;///<<b>!!!question!!!<b>
	Vec2d gradWij;///kernel gradient
	Vec2d eij; ///<pair direction from orginal particle to destination particle 
public:
	///total number of materials
	static int number_of_materials;
	static double supportlength;
        ///particle distance
	static double delta;
	///artificial viscosity
	static double art_vis;
	///simulation mode
       static int simu_mode;
       static double alpha_artVis;///<factor for Monaghan Artificial viscosity
       static double beta_artVis;///<factor for Monaghan Artificial viscosity
       static double epsilon_artVis;///<factor for Monaghan Artificial viscosity

	///constructor
	Interaction(const spParticle prtl_org, const spParticle prtl_dest, 
		    const Kernel &weight_function, const double dstc);
	
	///use old interaction object for new interaction
	void NewInteraction(const spParticle prtl_org, const spParticle prtl_dest, 
			    const Kernel &weight_function, const double dstc);

	///\brief renew pair parameters and changing pair values
	///
        ///Changes: Interaction object\n
        ///Depends on: Interaction Object, Org, Dest
	void RenewInteraction(const Kernel &weight_function);

	//pair interaction

	///\brief summation of the density
	///
        ///Changes: Org(rho:summation), Dest(rho:summation)\n
        ///Depends on: Interaction Object, Org(rho), Dest(rho)
        ///Remark: the idea is different from the original sph method
	void SummationDensity();

	///update forces
	void UpdateForces();

	spParticle  getOrigin();
	spParticle  getDest();
	double getWij() const;
	Vec2d getGradWij() const;

};

#endif //INTERACTION_H
