# 1D shock configuration file
# 1: liquids
# 2: gas dynamics
set SIMULATION_MODE 2

# possible values are 
# QuinticSpline, BetaSpline, CubicSpline, CubicSpline1D
set KERNEL_TYPE CubicSpline1D

#possible integration schemes
#1: leap frog
#2: predictor corrector
set INTEGRATION_SCHEME 1

#possible density treatments
#1: summation density (density obtained by smoothing)
#2: continuity density (density is integrated)
set DENSITY_MODE 1

# initial conditions flag 
# 0: use initial 
# 1: use restart file
set INITIAL_CONDITION 0

# number of cells in X and Y directions
# 130 cells in x direction are good for supportlength =0.03 (for m=cte=0.001875)
# xx cells in x direction are good for supportlength =xx (for dx=cte=0.05)
set CELLS(0) 64
set CELLS(1) 1

# size of one cell
# ->make sure that cell size >= support length
set CELL_SIZE 0.03125

# support length of the kernel 
# -> make sure that support length > particle spacing
# (0.03 is not bad for m=cte=0.001875)
# (xx is not bad for dx=cte=0.005)
set SUPPORT_LENGTH 0.0252

# number of particles in one cell size
# not used in 1D shock 
set CELL_RATIO 1

# initial particles velocity (not used)
set U0(0) 0.0
set U0(1) 0.0

# initial propeties of the particles(not used)
set rho0 0.0
set p0 0.5
set T0 1.0

# gravity force
set G_FORCE(0) 0.0
set G_FORCE(1) 0.0



# artificial viscosity marker:
# 2. art. visc. globally turned on
# 1: incl. art. visc. for compression only (as needed for shock-tube case)
# 0: no artificial viscosity
set ARTIFICIAL_VISCOSITY_MARKER 2

# parameters for artificial viscosity
set alpha_artVis 1.0
set beta_artVis 2.0
set epsilon_artVis 0.1

# physical viscosity flag
# 1: physical viscosity included
# 0: no physical viscosity
set PHYSICAL_VISCOSITY_MARKER 0

# marker to choose output format
# 0: used for post-processing of shocktube cases and wave propagation
#    format: x, y, rho, p, Ux, e, ID, m
# 1: used for visualization with SPLASH-program and all "real" 2D simulations
#    format x, y, Ux, Uy, rho, e, p, h=supportlength/2, m, V, ID
set SPLASH_OPTIMIZED_OUTPUT 0

# boundary conditions

# disable boundary conditions:
# 1: boundary conditions disabled
# 0: boundary conditions enabled
set DISABLE_BOUNDARY 0
# type and velocity
set xBl 0
set UxBl(0) 0.0
set UxBl(1) 0.0

set xBr 0
set UxBr(0) 0.0
set UxBr(1) 0.0

set yBd 1
set UyBd(0) 0.0
set UyBd(1) 0.0

set yBu 1
set UyBu(0) 0.0
set UyBu(1) 0.0

# time control
set Start_time 0.0		
set End_time 3.38062
set D_time 0.0422411163

#marker for automatic time control
# 0: autom. time conrtol switched off: specified dt used (see below) 
# 1: autom time control activated!
set AUTOMATIC_DT_CONTROL_MARKER 1

#timestep taken into account if autom. time-step-control switched off
#ATTENTION: the timestep has to be thoroughly choosen (respecting the stability criteria)
#(RECOMMENDATION: run the desired configuration with autom.dt-control turned on first to get an idea of the max. admissible dt, then pick a dt (including a certain margin, to be safe)
set manually_choosen_dt 0.0008


set NUMBER_OF_MATERIALS 2
set material_name(0) Wall
set material_type(0) 1
set material_cv(0) 0.0
set material_eta(0) 0.0
set material_gamma(0) 0.0
set material_b0(0) 0.0
set material_rho0(0) 0.0
set material_a0(0) 0.0

set material_name(1) Air
set material_type(1) 1
set material_cv(1) 717.645
set material_eta(1) 0.0
set material_gamma(1) 1.4
set material_b0(1) 0.0
set material_rho0(1) 0.0
set material_a0(1) 0.0