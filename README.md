sard
====

lammps extension

Based on LAMMPS, I extended the stochastic rotation dynamics (SRD) code with velocity boundaries. 
Collisions between solvent and immersed particles are considered in the SRD rotation process, 
that is to treat solid particles similar as solvent but taking mass into account in average velocity 
calculation in each grids. This is different from the original SRD code. 

One paper reivewed this two coupling methods in details, interested readers refer to 
Simulation of Claylike Colloids, DOI:	10.1103/PhysRevE.72.011408
