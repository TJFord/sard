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

PairStyle(line/lj,PairLineLJ)

#else

#ifndef LMP_PAIR_LINE_LJ_H
#define LMP_PAIR_LINE_LJ_H

#include "pair.h"

namespace LAMMPS_NS {

class PairLineLJ : public Pair {
 public:
  PairLineLJ(class LAMMPS *);
  virtual ~PairLineLJ();
  virtual void compute(int, int);
  void settings(int, char **);
  void coeff(int, char **);
  double init_one(int, int);

 protected:
  double cut_global;
  double **cut;
  double **epsilon,**sigma;
  double **lj1,**lj2,**lj3,**lj4;
  class AtomVecLine *avec;

  struct Discrete {
    double dx,dy;
    double sigma;
  };
  Discrete *discrete;           // list of all discretes for all lines
  int ndiscrete;                // number of discretes in list
  int dmax;                     // allocated size of discrete list
  int *dnum;                    // number of discretes per line, 0 if uninit
  int *dfirst;                  // index of first discrete per each line
  int nmax;                     // allocated size of dnum,dfirst vectors

  void allocate();
  void discretize(int, double);
};

}

#endif
#endif

/* ERROR/WARNING messages:

E: Pair line/lj requires atom style line

Self-explanatory.

E: Illegal ... command

Self-explanatory.  Check the input script syntax and compare to the
documentation for the command.  You can use -echo screen as a
command-line option when running LAMMPS to see the offending line.

E: Incorrect args for pair coefficients

Self-explanatory.  Check the input script or data file.

*/
