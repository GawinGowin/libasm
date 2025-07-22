#include <cstring>
#include <errno.h>
#include <gtest/gtest.h>
#include <vector>

extern "C" {
#include "libasm.h"
}

struct StringTestCase {
  const char* str;
  const char* description;
};

class FtStrlenTest : public ::testing::TestWithParam<StringTestCase> {
protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper to compare ft_strlen with standard strlen behavior
  void compareStrlenBehavior(const char* str) {
    size_t ft_result = ft_strlen(str);
    size_t std_result = strlen(str);
    EXPECT_EQ(ft_result, std_result);
  }
};

// Parameterized test data
const std::vector<StringTestCase> string_test_cases = {
  // Basic cases
  {"", "empty_string"},
  {"a", "single_character"},
  {"hello", "normal_string"},
  {"world", "another_normal_string"},
  {"test123", "alphanumeric_string"},
  
  // Special characters
  {"hello world", "string_with_spaces"},
  {"hello\n\t!@#", "string_with_special_chars"},
  {"123!@#", "numeric_with_special_chars"},
  {"\x01\x02\x7F\xFF", "boundary_ascii_characters"},
  
  // Edge cases
  {"hello\0world", "string_with_embedded_null"},
  {"x", "minimal_single_char"},
  {"ab", "two_characters"},
  {"abc", "three_characters"},
};

INSTANTIATE_TEST_SUITE_P(
    StringLength,
    FtStrlenTest,
    ::testing::ValuesIn(string_test_cases),
    [](const testing::TestParamInfo<StringTestCase>& info) {
      return info.param.description;
    }
);

TEST_P(FtStrlenTest, string_length) {
  const auto& test_case = GetParam();
  compareStrlenBehavior(test_case.str);
}

// Non-parameterized tests for special scenarios

TEST_F(FtStrlenTest, very_long_strings) {
  std::string long_str1(1000, 'a');
  std::string long_str2(20000, 'y');
  std::string long_str3(50000, 'z');
  
  compareStrlenBehavior(long_str1.c_str());
  compareStrlenBehavior(long_str2.c_str());
  compareStrlenBehavior(long_str3.c_str());
  
  // Verify specific lengths
  EXPECT_EQ(ft_strlen(long_str1.c_str()), 1000);
  EXPECT_EQ(ft_strlen(long_str2.c_str()), 20000);
  EXPECT_EQ(ft_strlen(long_str3.c_str()), 50000);
}

TEST_F(FtStrlenTest, errno_preservation) {
  const char* test_str = "hello world";
  
  // Test errno preservation with normal string
  errno = EINVAL;
  size_t ft_result = ft_strlen(test_str);
  int ft_errno = errno;
  
  errno = EINVAL;
  size_t std_result = strlen(test_str);
  int std_errno = errno;
  
  EXPECT_EQ(ft_errno, std_errno);
  EXPECT_EQ(ft_errno, EINVAL);
  EXPECT_EQ(ft_result, std_result);
  
  // Test errno preservation with empty string
  errno = EACCES;
  ft_result = ft_strlen("");
  ft_errno = errno;
  
  errno = EACCES;
  std_result = strlen("");
  std_errno = errno;
  
  EXPECT_EQ(ft_errno, std_errno);
  EXPECT_EQ(ft_errno, EACCES);
  EXPECT_EQ(ft_result, std_result);
  EXPECT_EQ(ft_result, 0);
  
  // Test errno preservation with very long string
  std::string long_str(1000, 'x');
  errno = ENOENT;
  ft_result = ft_strlen(long_str.c_str());
  ft_errno = errno;
  
  errno = ENOENT;
  std_result = strlen(long_str.c_str());
  std_errno = errno;
  
  EXPECT_EQ(ft_errno, std_errno);
  EXPECT_EQ(ft_errno, ENOENT);
  EXPECT_EQ(ft_result, std_result);
  EXPECT_EQ(ft_result, 1000);
}

TEST_F(FtStrlenTest, null_termination_behavior) {
  // Test string with null byte in middle (should stop at first null)
  const char null_in_middle[] = "hello\0world";
  compareStrlenBehavior(null_in_middle);
  EXPECT_EQ(ft_strlen(null_in_middle), 5);
  
  // Test strings with various null positions
  const char null_at_start[] = "\0hello";
  const char null_at_end[] = "hello\0";
  
  EXPECT_EQ(ft_strlen(null_at_start), 0);
  EXPECT_EQ(ft_strlen(null_at_end), 5);
}