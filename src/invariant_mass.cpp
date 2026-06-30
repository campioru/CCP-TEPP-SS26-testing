//! \file invariant_mass.cpp
#include "invariant_mass.hpp"

#include <cmath>

double invariant_mass(double energy, double momentum)
{
  if (energy < 0)
  {
    throw std::domain_error("unphysical negative energy");
  }
  double mass_squared = energy*energy - momentum*momentum;
  if (mass_squared < 0)
  {
    throw std::domain_error("unphysical mass^2");  
  }
  return std::sqrt(mass_squared);
}
