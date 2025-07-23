#include <gtest/gtest.h>
#include <vector>

extern "C" {
#include "libasm.h"
#include "libasm_bonus.h"
}

struct TestData {
  std::string input_string;
  std::string base_string;
  int expected_value;
};

std::ostream &operator<<(std::ostream &os, const TestData &data) {
  os << "Input: " << data.input_string << ", Base: " << data.base_string << ", Expected: " << data.expected_value;
  return os;
}

class PositiveArgsTest : public ::testing::TestWithParam<TestData> {};

TEST_P(PositiveArgsTest, Positive) {
  auto param = GetParam();
  int result = ft_atoi_base(param.input_string.c_str(), param.base_string.c_str());
  EXPECT_EQ(result, param.expected_value) << "Failed for " << param;
}

const TestData PositiveTestData[] = {
    {"42", "0123456789", 42},
    {"1", "1023456789", 0},
    {"-42", "0123456789", -42},
    {"  +42", "0123456789", 42},
    {"\t\n\v\f\r  +42", "0123456789", 42},
    {"-1", "01", -1},
    {"-1", "0123456789abcdef", -1},
    {"1000", "0123456789abcdef", 4096},
    {"-1000", "0123456789abcdef", -4096},
    {"1000", "01", 8},
    {"-1000", "01", -8},
    {"1000", "01234567", 512},
    {"-1000", "01234567", -512},
};

INSTANTIATE_TEST_SUITE_P(
    FtAtoiBaseTest,
    PositiveArgsTest,
    ::testing::ValuesIn(PositiveTestData),
    [](const testing::TestParamInfo<PositiveArgsTest::ParamType> &info) {
      return std::to_string(info.index);
    });