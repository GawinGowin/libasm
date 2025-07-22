#include <cstring>
#include <errno.h>
#include <gtest/gtest.h>
#include <tuple>
#include <vector>

extern "C" {
#include "libasm.h"
}

struct StringCompareTestCase {
  const char* str1;
  const char* str2;
  const char* description;
};

class FtStrcmpTest : public ::testing::TestWithParam<StringCompareTestCase> {
protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper to compare ft_strcmp with standard strcmp behavior
  void compareStringBehavior(const char* str1, const char* str2) {
    int ft_result = ft_strcmp(str1, str2);
    int std_result = strcmp(str1, str2);
    
    // Check if signs match (same comparison result semantics)
    if (ft_result == 0) {
      EXPECT_EQ(std_result, 0);
    } else if (ft_result > 0) {
      EXPECT_GT(std_result, 0);
    } else {
      EXPECT_LT(std_result, 0);
    }
  }
};

// Parameterized test data
const std::vector<StringCompareTestCase> string_test_cases = {
  // Equal strings
  {"", "", "empty_strings"},
  {"a", "a", "single_equal_chars"},
  {"hello", "hello", "equal_strings"},
  {"test123", "test123", "equal_alphanumeric"},
  {"!@#$%", "!@#$%", "equal_special_chars"},
  {"test\n\t", "test\n\t", "equal_with_whitespace"},
  
  // Different strings - first less than second
  {"a", "b", "single_char_a_less_b"},
  {"abc", "abd", "string_difference_at_end"},
  {"hello", "world", "completely_different"},
  {"", "non-empty", "empty_vs_non_empty"},
  {"abc", "abcd", "prefix_relationship"},
  {"Hello", "hello", "case_difference"},
  {"test\n", "test\t", "whitespace_difference"},
  
  // Different strings - first greater than second
  {"b", "a", "single_char_b_greater_a"},
  {"abd", "abc", "string_difference_at_end_reverse"},
  {"world", "hello", "completely_different_reverse"},
  {"non-empty", "", "non_empty_vs_empty"},
  {"abcd", "abc", "longer_vs_shorter"},
  {"hello", "Hello", "case_difference_reverse"},
  
  // Special cases
  {"\x01\x02", "\x01\x02", "binary_equal"},
  {"\x01", "\x02", "binary_different"},
  {"\xFF\xFE", "\xFF\xFE", "high_ASCII_equal"},
  {"\xFF", "\xFE", "high_ASCII_different"},
};

INSTANTIATE_TEST_SUITE_P(
    StringComparison,
    FtStrcmpTest,
    ::testing::ValuesIn(string_test_cases),
    [](const testing::TestParamInfo<StringCompareTestCase>& info) {
      return info.param.description;
    }
);

TEST_P(FtStrcmpTest, string_comparison) {
  const auto& test_case = GetParam();
  compareStringBehavior(test_case.str1, test_case.str2);
}

// Non-parameterized tests for special scenarios

TEST_F(FtStrcmpTest, very_long_strings) {
  std::string long_str1(10000, 'a');
  std::string long_str2(10000, 'a');
  std::string long_str3(10000, 'b');
  
  compareStringBehavior(long_str1.c_str(), long_str2.c_str());
  compareStringBehavior(long_str1.c_str(), long_str3.c_str());
}

TEST_F(FtStrcmpTest, errno_preservation) {
  const char* str1 = "hello";
  const char* str2 = "world";
  
  // Test errno preservation with different strings
  errno = EINVAL;
  int ft_result = ft_strcmp(str1, str2);
  int ft_errno = errno;
  
  errno = EINVAL;
  int std_result = strcmp(str1, str2);
  int std_errno = errno;
  
  EXPECT_EQ(ft_errno, std_errno);
  EXPECT_EQ(ft_errno, EINVAL);
  compareStringBehavior(str1, str2);
  
  // Test errno preservation with equal strings
  errno = EACCES;
  ft_result = ft_strcmp(str1, str1);
  ft_errno = errno;
  
  errno = EACCES;
  std_result = strcmp(str1, str1);
  std_errno = errno;
  
  EXPECT_EQ(ft_errno, std_errno);
  EXPECT_EQ(ft_errno, EACCES);
  EXPECT_EQ(ft_result, 0);
  EXPECT_EQ(std_result, 0);
}