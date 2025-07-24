#include <gtest/gtest.h>

extern "C" {
#include "libasm_bonus.h"
#include <string.h>
}

struct StrspnTestCase {
  const char* str;
  const char* accept;
  const char* description;
};

std::ostream &operator<<(std::ostream &os, const StrspnTestCase &data) {
  os << data.description;
  return os;
}

class StrspnTestArgs : public ::testing::TestWithParam<StrspnTestCase> {};

TEST_P(StrspnTestArgs, ComparesWithStandardStrspn) {
  auto param = GetParam();
  EXPECT_EQ(strspn(param.str, param.accept), ft_strspn(param.str, param.accept)) 
    << param.description;
}

INSTANTIATE_TEST_SUITE_P(
    FtStrspnTests,
    StrspnTestArgs,
    ::testing::Values(
        StrspnTestCase{"", "", "Empty string and accept"},
        StrspnTestCase{"hello", "", "Non-empty string, empty accept"},
        StrspnTestCase{"", "abc", "Empty string, non-empty accept"},
        StrspnTestCase{"hello", "hel", "Matching prefix"},
        StrspnTestCase{"hello", "xyz", "No matching characters"},
        StrspnTestCase{"hello", "abcdefghijklmnopqrstuvwxyz", "All characters match"},
        StrspnTestCase{"123abc", "0123456789", "Digits only"},
        StrspnTestCase{"   \t\n", " \t\n", "Whitespace characters"},
        StrspnTestCase{"hello world", "helo w", "Partial match with space"},
        StrspnTestCase{"aaaaaa", "a", "Repeated character"},
        StrspnTestCase{"abcdef", "fed", "Different order"},
        StrspnTestCase{"test", "tset", "All chars present different order"}),
    [](const testing::TestParamInfo<StrspnTestArgs::ParamType> &info) {
      return std::to_string(info.index);
    });

