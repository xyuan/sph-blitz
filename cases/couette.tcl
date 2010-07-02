set SIMULATION_MODE 1

# possible values are 
# QuinticSpline, BetaSpline, CubicSpline
set KERNEL_TYPE QuinticSpline

set INITIAL_CONDITION	0

# number of cell
set ncell 8
set CELLS(0) $ncell
set CELLS(1) $ncell

# sizer of the domain
set L 1e-3
set SUPPORT_LENGTH [expr {$L / $ncell}]
set CELL_SIZE $SUPPORT_LENGTH

# the number of particles in one support length
set CELL_RATIO  3

# initial velocity
set U0(0) 0.0
set U0(1) 0.0

set rho0 1e3
set p0 1.0
set T0 1.0

set G_FORCE(0) 0.0
#set G_FORCE(0) 0.0
set G_FORCE(1) 0.0

set NUMBER_OF_MATERIALS 2
set Start_time 0.0
set End_time 1.0
# time between output
set D_time 1e-1

# boundary conditions
set wall 0 
set periodic 1
set freeslip 2
set symmetry 3

# type and velocity
set xBl $periodic
set UxBl(0) 0.0
set UxBl(1) 0.0

set xBr $periodic
set UxBr(0) 0.0
set UxBr(1) 0.0

set yBd $wall
set UyBd(0) 0.0
set UyBd(1) 0.0

set yBu $wall
set UyBu(0) 1.25e-5
set UyBu(1) 0.0

set NUMBER_OF_MATERIALS 2
set material_name(0) Air
set material_type(0) 1
set material_cv(0) 1.0e3
set material_eta(0) 1.0e-3
set material_gamma(0) 7.0
set material_b0(0) 1.0e2
set material_rho0(0) 1.0e3
set material_a0(0) 1.0e2

set material_name(1) $material_name(0)
set material_type(1) $material_type(0)
set material_cv(1) $material_cv(0)
set material_eta(1) $material_eta(0)
set material_gamma(1) $material_gamma(0)
set material_b0(1) $material_b0(0)
set material_rho0(1) $material_rho0(0)
set material_a0(1) $material_a0(0)