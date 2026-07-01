//! \file test_invariant_mass.cpp
#include "invariant_mass.hpp"
#include <gtest/gtest.h>

// Case 1. Physical domain
TEST(InvariantMass, PhysicalDomain)
{
  EXPECT_EQ(invariant_mass(10., 0.), 10.) << "at rest, particle does not have correct mass" << std::endl;
  EXPECT_EQ(invariant_mass(100., 100.), 0.) << "massless particle is not massless" << std::endl;

  EXPECT_EQ(invariant_mass(5, 3), 4) << "off mass shell" << std::endl;
  EXPECT_EQ(invariant_mass(5, 4), 3) << "off mass shell" << std::endl;
}

// Case 2. Error conditions
// TEST(InvariantMass, UnphysicalEnergies)
// {
//   FAIL() << "not implemented yet" << std::endl;
// }
