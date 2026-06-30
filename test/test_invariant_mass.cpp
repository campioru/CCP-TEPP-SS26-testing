//! \file test_invariant_mass.cpp
#include <cmath>
#include <stdexcept>
#include <iostream>
#include "invariant_mass.hpp"

// Case 1. Physical domain
void test_physical_domain()
{
  std::cout << "photon mass should be zero: " << invariant_mass(100, 100) << std::endl;
}

// Case 2. Error conditions
void test_error_conditions()
{
  try
  {
    std::cout << "negative energy should throw exception: ";
    invariant_mass(-1, 0);
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
