#include <cstring>
#include <gtest/gtest.h>

extern "C" {
#include "libasm.h"
}

class FtStrlenTest : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(FtStrlenTest, empty_string) {
  const char *str = "";
  EXPECT_EQ(ft_strlen(str), strlen(str));
}

TEST_F(FtStrlenTest, single_character) {
  const char *str = "a";
  EXPECT_EQ(ft_strlen(str), strlen(str));
}

TEST_F(FtStrlenTest, normal_string) {
  const char *str1 = "hello";
  const char *str2 = "world";
  EXPECT_EQ(ft_strlen(str1), strlen(str1));
  EXPECT_EQ(ft_strlen(str2), strlen(str2));
}

TEST_F(FtStrlenTest, long_string) {
  std::string long_str(1000, 'a');
  EXPECT_EQ(ft_strlen(long_str.c_str()), strlen(long_str.c_str()));
}

TEST_F(FtStrlenTest, string_with_spaces) {
  const char *str = "hello world";
  EXPECT_EQ(ft_strlen(str), strlen(str));
}

TEST_F(FtStrlenTest, string_with_special_chars) {
  const char *special_str = "hello\n\t!@#";
  EXPECT_EQ(ft_strlen(special_str), strlen(special_str));
}

TEST_F(FtStrlenTest, compare_with_stdlib) {
  const char *test_strings[] = {"", "a", "hello", "world",
                                "test123", "hello world", "123!@#"};
  for (const char *str : test_strings) {
    EXPECT_EQ(ft_strlen(str), strlen(str)) << "Failed for string: " << str;
  }
}


TEST_F(FtStrlenTest, very_long_string) {
  // Test with very long strings
  std::string long_str(20000, 'y');
  EXPECT_EQ(ft_strlen(long_str.c_str()), strlen(long_str.c_str()));
  EXPECT_EQ(ft_strlen(long_str.c_str()), 20000);
}

TEST_F(FtStrlenTest, boundary_characters) {
  // Test with boundary ASCII characters
  const char boundary_chars[] = "\x01\x02\x7F\xFF";
  EXPECT_EQ(ft_strlen(boundary_chars), strlen(boundary_chars));
  
  // Test string with null byte in middle (should stop at first null)
  const char null_in_middle[] = "hello\0world";
  EXPECT_EQ(ft_strlen(null_in_middle), strlen(null_in_middle));
  EXPECT_EQ(ft_strlen(null_in_middle), 5);
}

TEST_F(FtStrlenTest, errno_not_modified) {
  // Test that errno is not modified during normal operation
  const char *test_str = "hello world";
  
  // Set errno to a specific value
  errno = EINVAL;
  size_t ft_result = ft_strlen(test_str);
  int ft_errno = errno;
  
  errno = EINVAL;
  size_t std_result = strlen(test_str);
  int std_errno = errno;
  
  // Both should preserve errno
  EXPECT_EQ(ft_errno, std_errno);
  EXPECT_EQ(ft_errno, EINVAL);
  EXPECT_EQ(ft_result, std_result);
  
  // Test with empty string
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
  
  // Test with very long string
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