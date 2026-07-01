//! \file test_invariant_mass.cpp
#include "invariant_mass.hpp"
#include <gtest/gtest.h>

// Case 1. Physical domain
TEST(InvariantMass, PhysicalDomain)
{
  EXPECT_DOUBLE_EQ(invariant_mass(10., 0.), 10.) << "at rest, particle does not have correct mass" << std::endl;
  EXPECT_DOUBLE_EQ(invariant_mass(100., 100.), 0.) << "massless particle is not massless" << std::endl;

  EXPECT_DOUBLE_EQ(invariant_mass(5, 3), 4) << "off mass shell" << std::endl;
  EXPECT_DOUBLE_EQ(invariant_mass(5, 4), 3) << "off mass shell" << std::endl;

  EXPECT_DOUBLE_EQ(invariant_mass(.5, .3), .4) << "off mass shell" << std::endl;
  EXPECT_DOUBLE_EQ(invariant_mass(.5, .4), .3) << "off mass shell" << std::endl;

  EXPECT_DOUBLE_EQ(.1 + .2, .3);
  EXPECT_DOUBLE_EQ(.1 + .2, .2 + .1);
  EXPECT_DOUBLE_EQ((.1 + .3) + .2, .1 + (.3 + .2));

  EXPECT_NEAR(invariant_mass(54.9, 3.14), 54.8, .1);
}

// Case 2. Error conditions
// TEST(InvariantMass, UnphysicalEnergies)
// {
//   FAIL() << "not implemented yet" << std::endl;
// }
