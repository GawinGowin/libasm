#include <gtest/gtest.h>

extern "C" {
#include "libasm_bonus.h"
#include <string.h>
}

struct StrchrTestCase {
  const char* str;
  int needle;
  const char* description;
};

std::ostream &operator<<(std::ostream &os, const StrchrTestCase &data) {
  os << data.description;
  return os;
}

class StrchrTestArgs : public ::testing::TestWithParam<StrchrTestCase> {};

TEST_P(StrchrTestArgs, ComparesWithStandardStrchr) {
  auto param = GetParam();
  const char* ft_result = ft_strchr(param.str, param.needle);
  const char* std_result = strchr(param.str, param.needle);
  
  if (ft_result == nullptr && std_result == nullptr) {
    EXPECT_EQ(ft_result, std_result) << param.description;
  } else if (ft_result != nullptr && std_result != nullptr) {
    EXPECT_STREQ(ft_result, std_result) << param.description;
  } else {
    EXPECT_TRUE(false) << "One of the results is null: " << param.description;
  }
}
INSTANTIATE_TEST_SUITE_P(
    FtStrchrTests,
    StrchrTestArgs,
    ::testing::Values(
        StrchrTestCase{"hello world", 'o', "find_first_o"},
        StrchrTestCase{"hello world", 'z', "find_nonexistent_char"},
        StrchrTestCase{"", 'a', "empty_string"},
        StrchrTestCase{"test string", 't', "find_first_t"},
        StrchrTestCase{"test string", '\0', "find_null_terminator"},
        StrchrTestCase{"test string", 's', "find_s_in_string"}),
    [](const testing::TestParamInfo<StrchrTestArgs::ParamType> &info) {
      return info.param.description;
    });