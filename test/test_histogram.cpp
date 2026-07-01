//! \file test_histogram.cpp
#include "histogram.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// -----------------------------------------------------------------------------

class HistogramFillTest : public ::testing::Test
{
  protected:
    Histogram hist = Histogram(10, 0.0f, 1.0f);
    std::vector<float> expected = std::vector<float>(10, 0.0f);
};

class FilledHistogramTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
      for (int bin = 0; bin < 10; ++bin)
      {
        for (int i = 0; i < bin + 1; ++i)
        {
          hist.fill(bin + 0.5f);
        }
      }
      hist.fill(-1.0f);
    }
    void TearDown() override
    {
      std::cout << "teardown" << std::endl;
    }

    Histogram hist = Histogram(10, 0.0f, 1.0f);
};

// -----------------------------------------------------------------------------

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

TEST_F(HistogramFillTest, SingleFillIncreasesCorrectBin)
{
  hist.fill(0.33f);
  EXPECT_EQ(hist.bin_counts()[3], 1.0f);
  EXPECT_EQ(hist.n_entries(), 1);
}

TEST_F(HistogramFillTest, SingleFillLeavesOtherBinsAtZero)
{
  hist.fill(0.44f);
  expected[4] = 1.0f;
  EXPECT_THAT(hist.bin_counts(), ::testing::ContainerEq(expected));
}

TEST_F(HistogramFillTest, SingleFillOutsideRangeGoesToUnderflow)
{
  hist.fill(-1.0f);
  EXPECT_THAT(hist.bin_counts(), ::testing::ContainerEq(expected));
  EXPECT_EQ(hist.n_underflow(), 1);
  EXPECT_EQ(hist.n_entries(), 1);
}

TEST_F(HistogramFillTest, WeightedFillProducesCorrectCounts)
{
  hist.fill(0.1f, 0.5f);
  hist.fill(0.6f, 1.5f);
  expected[1] = 0.5f;
  expected[6] = 1.5f;
  EXPECT_THAT(hist.bin_counts(), ::testing::ContainerEq(expected));
}

// -----------------------------------------------------------------------------

TEST_F(FilledHistogramTest, TotalEntryCount)
{
  EXPECT_EQ(hist.n_entries(), 56);
}
