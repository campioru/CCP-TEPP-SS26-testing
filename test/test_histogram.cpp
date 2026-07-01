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

TEST(HistogramConstruction, BinEdgesHasCorrectSize)
{
  EXPECT_EQ(Histogram(10, 0.0f, 10.0f).bin_edges().size(), 10+1);
  EXPECT_EQ(Histogram(1, 0.0f, 10.0f).bin_edges().size(), 1+1);
}

TEST(HistogramConstruction, BinEdgesHasCorrectEndpoints)
{
  Histogram hist(10, 0.0f, 1.0f);
  EXPECT_FLOAT_EQ(hist.bin_edges().front(), 0.0f) << "front not equal" << std::endl;
  EXPECT_FLOAT_EQ(hist.bin_edges().back(), 1.0f) << "back not equal" << std::endl;
}

// -----------------------------------------------------------------------------


TEST(HistogramFill, SingleFillIncreasesCorrectBin)
{
  Histogram hist(10, 0.0f, 1.0f);
  hist.fill(0.33f);
  EXPECT_EQ(hist.bin_counts()[3], 1.0f);
  EXPECT_EQ(hist.n_entries(), 1);
}

TEST(HistogramFill, SingleFillLeavesOtherBinsAtZero)
{
  Histogram hist(10, 0.0f, 1.0f);
  hist.fill(0.44f);
  std::vector<float> expected(10, 0.0f);
  expected[4] = 1.0f;
  EXPECT_THAT(hist.bin_counts(), ::testing::ContainerEq(expected));
}

TEST(HistogramFill, SingleFillOutsideRangeGoesToUnderflow)
{
  Histogram hist(10, 0.0f, 1.0f);
  hist.fill(-1.0f);
  std::vector<float> expected_bin_counts(10, 0.0f);
  EXPECT_THAT(hist.bin_counts(), ::testing::ContainerEq(expected_bin_counts));
  EXPECT_EQ(hist.n_underflow(), 1);
  EXPECT_EQ(hist.n_entries(), 1);
}
