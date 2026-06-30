//! \file test_invariant_mass.cpp
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include "invariant_mass.hpp"

// Case 1. Physical domain
void test_physical_domain()
{
  assert((invariant_mass(100., 100.) == 0.) && "mass of photon not zero");
}

// Case 2. Error conditions
void test_error_conditions()
{
  try
  {
    double bad = invariant_mass(-1, 0);
    assert(false && "std::domain_error not thrown for negative error");
  }
  catch(const std::domain_error&)
  {
    std::cout << "pass" << std::endl;
  }
}

int main()
{
  test_physical_domain();
  test_error_conditions();
}
