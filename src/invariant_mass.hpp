//! \file invariant_mass.hpp
#pragma once // header guard

#include <stdexcept>

// 1. return m = sqrt(E^2 - p^2)
// 2. If E < 0, throws std::domain_error
// 3. If E^2 < p^2, throws std::domain_error
double invariant_mass(double energy, double momentum);
