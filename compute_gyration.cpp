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

#include "math.h"
#include "compute_gyration.h"
#include "update.h"
#include "atom.h"
#include "group.h"
#include "domain.h"
#include "error.h"

using namespace LAMMPS_NS;

/* ---------------------------------------------------------------------- */

ComputeGyration::ComputeGyration(LAMMPS *lmp, int narg, char **arg) :
  Compute(lmp, narg, arg)
{
  if (narg != 3) error->all(FLERR,"Illegal compute gyration command");

  scalar_flag = vector_flag = 1;
  size_vector = 6;
  extscalar = 0;
  extvector = 0;

  vector = new double[6];
}

/* ---------------------------------------------------------------------- */

ComputeGyration::~ComputeGyration()
{
  delete [] vector;
}

/* ---------------------------------------------------------------------- */

void ComputeGyration::init()
{
  masstotal = group->mass(igroup);
}

/* ---------------------------------------------------------------------- */

double ComputeGyration::compute_scalar()
{
  invoked_scalar = update->ntimestep;

  double xcm[3];
  group->xcm(igroup,masstotal,xcm);
  scalar = group->gyration(igroup,masstotal,xcm);
  return scalar;
}

/* ----------------------------------------------------------------------
   compute the radius-of-gyration tensor of group of atoms
   around center-of-mass cm
   must unwrap atoms to compute Rg tensor correctly
------------------------------------------------------------------------- */

void ComputeGyration::compute_vector()
{
  invoked_vector = update->ntimestep;

  double xcm[3];
  group->xcm(igroup,masstotal,xcm);

  double **x = atom->x;
  int *mask = atom->mask;
  int *type = atom->type;
  tagint *image = atom->image;
  double *mass = atom->mass;
  double *rmass = atom->rmass;
  int nlocal = atom->nlocal;

  int xbox,ybox,zbox;
  double dx,dy,dz,massone;
  double xprd = domain->xprd;
  double yprd = domain->yprd;
  double zprd = domain->zprd;

  double rg[6];
  rg[0] = rg[1] = rg[2] = rg[3] = rg[4] = rg[5] = 0.0;

  for (int i = 0; i < nlocal; i++)
    if (mask[i] & groupbit) {
      xbox = (image[i] & IMGMASK) - IMGMAX;
      ybox = (image[i] >> IMGBITS & IMGMASK) - IMGMAX;
      zbox = (image[i] >> IMG2BITS) - IMGMAX;
      dx = (x[i][0] + xbox*xprd) - xcm[0];
      dy = (x[i][1] + ybox*yprd) - xcm[1];
      dz = (x[i][2] + zbox*zprd) - xcm[2];
      if (rmass) massone = rmass[i];
      else massone = mass[type[i]];
      rg[0] += dx*dx * massone;
      rg[1] += dy*dy * massone;
      rg[2] += dz*dz * massone;
      rg[3] += dx*dy * massone;
      rg[4] += dx*dz * massone;
      rg[5] += dy*dz * massone;
    }
  MPI_Allreduce(rg,vector,6,MPI_DOUBLE,MPI_SUM,world);

  if (masstotal == 0.0) return;
  for (int i = 0; i < 6; i++) vector[i] /= masstotal;
}
