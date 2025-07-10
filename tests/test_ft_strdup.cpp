#include <cstdlib>
#include <cstring>
#include <gtest/gtest.h>

extern "C" {
#include "libasm.h"
}

class FtStrdupTest : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(FtStrdupTest, empty_string) {
  char *result = ft_strdup("");
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "");
  free(result);
}

TEST_F(FtStrdupTest, single_character) {
  char *result = ft_strdup("a");
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "a");
  free(result);
}

TEST_F(FtStrdupTest, normal_string) {
  char *result = ft_strdup("hello");
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "hello");
  free(result);
}

TEST_F(FtStrdupTest, long_string) {
  std::string src(500, 'z');
  char *result = ft_strdup(src.c_str());
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, src.c_str());
  free(result);
}

TEST_F(FtStrdupTest, string_with_spaces) {
  char *result = ft_strdup("hello world");
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "hello world");
  free(result);
}

TEST_F(FtStrdupTest, string_with_special_chars) {
  char *result = ft_strdup("test\n\t!@#");
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "test\n\t!@#");
  free(result);
}

TEST_F(FtStrdupTest, independence_of_copies) {
  const char *original = "test";
  char *copy = ft_strdup(original);
  ASSERT_NE(copy, nullptr);
  EXPECT_STREQ(copy, original);

  // Modify copy and ensure original is unchanged
  copy[0] = 'X';
  EXPECT_STREQ(original, "test");
  EXPECT_STREQ(copy, "Xest");

  free(copy);
}

TEST_F(FtStrdupTest, compare_with_stdlib) {
  const char *test_strings[] = {"",        "a",           "hello", "world",
                                "test123", "hello world", "123!@#"};
  for (const char *str : test_strings) {
    char *ft_result = ft_strdup(str);
    char *std_result = strdup(str);

    ASSERT_NE(ft_result, nullptr) << "ft_strdup failed for: " << str;
    ASSERT_NE(std_result, nullptr) << "strdup failed for: " << str;

    EXPECT_STREQ(ft_result, std_result) << "Results differ for: " << str;
    EXPECT_STREQ(ft_result, str) << "ft_strdup result incorrect for: " << str;

    free(ft_result);
    free(std_result);
  }
}


TEST_F(FtStrdupTest, very_long_string) {
  // Test with very long strings
  std::string long_str(8000, 'x');
  char *ft_result = ft_strdup(long_str.c_str());
  char *std_result = strdup(long_str.c_str());
  
  ASSERT_NE(ft_result, nullptr);
  ASSERT_NE(std_result, nullptr);
  
  EXPECT_STREQ(ft_result, std_result);
  EXPECT_STREQ(ft_result, long_str.c_str());
  
  free(ft_result);
  free(std_result);
}

TEST_F(FtStrdupTest, boundary_characters) {
  // Test with boundary ASCII characters
  const char boundary_chars[] = "\x01\x02\x7F\xFF";
  char *ft_result = ft_strdup(boundary_chars);
  char *std_result = strdup(boundary_chars);
  
  ASSERT_NE(ft_result, nullptr);
  ASSERT_NE(std_result, nullptr);
  
  EXPECT_STREQ(ft_result, std_result);
  EXPECT_STREQ(ft_result, boundary_chars);
  
  free(ft_result);
  free(std_result);
}

TEST_F(FtStrdupTest, errno_behavior) {
  // Test errno behavior during normal operation
  const char *test_str = "hello world";
  
  // Set errno to a specific value
  errno = EINVAL;
  char *ft_result = ft_strdup(test_str);
  int ft_errno = errno;
  
  errno = EINVAL;
  char *std_result = strdup(test_str);
  int std_errno = errno;
  
  // Both should succeed and preserve errno (or both should fail with same errno)
  if (ft_result != nullptr && std_result != nullptr) {
    // Success case - errno should be preserved
    EXPECT_EQ(ft_errno, std_errno);
    EXPECT_STREQ(ft_result, std_result);
    EXPECT_STREQ(ft_result, test_str);
    free(ft_result);
    free(std_result);
  } else {
    // Failure case - both should fail with same errno
    EXPECT_EQ(ft_result, nullptr);
    EXPECT_EQ(std_result, nullptr);
    EXPECT_EQ(ft_errno, std_errno);
    // Don't free NULL pointers
  }
  
  // Test with empty string
  errno = EACCES;
  ft_result = ft_strdup("");
  ft_errno = errno;
  
  errno = EACCES;
  std_result = strdup("");
  std_errno = errno;
  
  if (ft_result != nullptr && std_result != nullptr) {
    EXPECT_EQ(ft_errno, std_errno);
    EXPECT_STREQ(ft_result, std_result);
    EXPECT_STREQ(ft_result, "");
    free(ft_result);
    free(std_result);
  } else {
    EXPECT_EQ(ft_result, nullptr);
    EXPECT_EQ(std_result, nullptr);
    EXPECT_EQ(ft_errno, std_errno);
  }
}