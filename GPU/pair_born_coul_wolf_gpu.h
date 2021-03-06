/* ----------------------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under 
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#ifdef PAIR_CLASS

PairStyle(born/coul/wolf/gpu,PairBornCoulWolfGPU)

#else

#ifndef LMP_PAIR_BORN_COUL_WOLF_GPU_H
#define LMP_PAIR_BORN_COUL_WOLF_GPU_H

#include "pair_born_coul_wolf.h"

namespace LAMMPS_NS {

class PairBornCoulWolfGPU : public PairBornCoulWolf {
 public:
  PairBornCoulWolfGPU(LAMMPS *lmp);
  ~PairBornCoulWolfGPU();
  void cpu_compute(int, int, int, int, int *, int *, int **);
  void compute(int, int);
  void init_style();
  double memory_usage();

 enum { GPU_FORCE, GPU_NEIGH, GPU_HYB_NEIGH };

 private:
  int gpu_mode;
  double cpu_time;
  int *gpulist;
};

}
#endif
#endif

/* ERROR/WARNING messages:

E: Out of memory on GPGPU

UNDOCUMENTED

E: Cannot use newton pair with born/coul/wolf/gpu pair style

UNDOCUMENTED

E: Pair style born/coul/wolf/gpu requires atom attribute q

The atom style defined does not have this attribute.

*/
