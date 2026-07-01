//! \file test_histogram.cpp
#include "histogram.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(HistogramConstruction, ValidParametersDoNotThrow)
{
  EXPECT_NO_THROW(Histogram(10, 0.0f, 1.0f));
}

TEST(HistogramConstruction, ZeroBinsThrows)
{
  EXPECT_THROW(Histogram(0, 0.0f, 10.0f), std::invalid_argument);
}

TEST(HistogramConstruction, NegativeBinsThrows)
{
  EXPECT_THROW(Histogram(-1, 0.0f, 10.0f), std::invalid_argument);
}
