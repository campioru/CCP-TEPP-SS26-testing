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

TEST(HistogramConstruction, IncorrectRangeThrows)
{
  EXPECT_THROW(Histogram(10, 10.0f, 0.0f), std::invalid_argument);
}

TEST(HistogramConstruction, BinCountsHasCorrectSize)
{
  EXPECT_EQ(Histogram(10, 0.0f, 10.0f).bin_counts().size(), 10);
  EXPECT_EQ(Histogram(1, 0.0f, 10.0f).bin_counts().size(), 1);
}

TEST(HistogramConstruction, AllBinsInitiallyZero)
{
  Histogram hist(10, 0.0f, 1.0f);
  std::vector<float> expected(10, 0.0f);

  // EXPECT_EQ(hist.bin_counts(), expected);
  EXPECT_THAT(hist.bin_counts(), ::testing::ContainerEq(expected));
}
