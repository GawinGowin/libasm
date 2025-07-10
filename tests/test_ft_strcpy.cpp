#include <cstring>
#include <gtest/gtest.h>

extern "C" {
#include "libasm.h"
}

class FtStrcpyTest : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(FtStrcpyTest, empty_string) {
  const char *src = "";
  char dst1[10], dst2[10];
  char *ft_result = ft_strcpy(dst1, src);
  char *std_result = strcpy(dst2, src);
  EXPECT_STREQ(dst1, dst2);
  EXPECT_EQ(ft_result, dst1);
  EXPECT_EQ(std_result, dst2);
}

TEST_F(FtStrcpyTest, single_character) {
  const char *src = "a";
  char dst1[10], dst2[10];
  char *ft_result = ft_strcpy(dst1, src);
  char *std_result = strcpy(dst2, src);
  EXPECT_STREQ(dst1, dst2);
  EXPECT_EQ(ft_result, dst1);
  EXPECT_EQ(std_result, dst2);
}

TEST_F(FtStrcpyTest, normal_string) {
  const char *src = "hello";
  char dst1[20], dst2[20];
  char *ft_result = ft_strcpy(dst1, src);
  char *std_result = strcpy(dst2, src);
  EXPECT_STREQ(dst1, dst2);
  EXPECT_EQ(ft_result, dst1);
  EXPECT_EQ(std_result, dst2);
}

TEST_F(FtStrcpyTest, long_string) {
  std::string src(100, 'x');
  char dst1[200], dst2[200];
  char *ft_result = ft_strcpy(dst1, src.c_str());
  char *std_result = strcpy(dst2, src.c_str());
  EXPECT_STREQ(dst1, dst2);
  EXPECT_EQ(ft_result, dst1);
  EXPECT_EQ(std_result, dst2);
}

TEST_F(FtStrcpyTest, string_with_spaces) {
  const char *src = "hello world";
  char dst1[20], dst2[20];
  char *ft_result = ft_strcpy(dst1, src);
  char *std_result = strcpy(dst2, src);
  EXPECT_STREQ(dst1, dst2);
  EXPECT_EQ(ft_result, dst1);
  EXPECT_EQ(std_result, dst2);
}

TEST_F(FtStrcpyTest, string_with_special_chars) {
  const char *src = "test\n\t!@#";
  char dst1[20], dst2[20];
  char *ft_result = ft_strcpy(dst1, src);
  char *std_result = strcpy(dst2, src);
  EXPECT_STREQ(dst1, dst2);
  EXPECT_EQ(ft_result, dst1);
  EXPECT_EQ(std_result, dst2);
}

TEST_F(FtStrcpyTest, compare_with_stdlib) {
  const char *test_strings[] = {"",        "a",           "hello", "world",
                                "test123", "hello world", "123!@#"};
  for (const char *str : test_strings) {
    char dst1[100], dst2[100];
    char *ft_result = ft_strcpy(dst1, str);
    char *std_result = strcpy(dst2, str);

    EXPECT_STREQ(dst1, dst2) << "Failed for string: " << str;
    EXPECT_EQ(ft_result, dst1) << "Return value mismatch for: " << str;
    EXPECT_EQ(std_result, dst2)
        << "Standard return value mismatch for: " << str;
  }
}


TEST_F(FtStrcpyTest, very_long_string) {
  // Test with very long strings
  std::string long_str(5000, 'z');
  char dst1[6000], dst2[6000];
  
  char *ft_result = ft_strcpy(dst1, long_str.c_str());
  char *std_result = strcpy(dst2, long_str.c_str());
  
  EXPECT_STREQ(dst1, dst2);
  EXPECT_EQ(ft_result, dst1);
  EXPECT_EQ(std_result, dst2);
}

TEST_F(FtStrcpyTest, boundary_characters) {
  // Test with boundary ASCII characters
  const char boundary_chars[] = "\x01\x02\x7F\xFF";
  char dst1[10], dst2[10];
  
  char *ft_result = ft_strcpy(dst1, boundary_chars);
  char *std_result = strcpy(dst2, boundary_chars);
  
  EXPECT_STREQ(dst1, dst2);
  EXPECT_EQ(ft_result, dst1);
  EXPECT_EQ(std_result, dst2);
}

TEST_F(FtStrcpyTest, errno_not_modified) {
  // Test that errno is not modified during normal operation
  const char *src = "hello world";
  char dst1[20], dst2[20];
  
  // Set errno to a specific value
  errno = EINVAL;
  char *ft_result = ft_strcpy(dst1, src);
  int ft_errno = errno;
  
  errno = EINVAL;
  char *std_result = strcpy(dst2, src);
  int std_errno = errno;
  
  // Both should preserve errno
  EXPECT_EQ(ft_errno, std_errno);
  EXPECT_EQ(ft_errno, EINVAL);
  EXPECT_STREQ(dst1, dst2);
  EXPECT_EQ(ft_result, dst1);
  EXPECT_EQ(std_result, dst2);
  
  // Test with empty string
  errno = EACCES;
  ft_result = ft_strcpy(dst1, "");
  ft_errno = errno;
  
  errno = EACCES;
  std_result = strcpy(dst2, "");
  std_errno = errno;
  
  EXPECT_EQ(ft_errno, std_errno);
  EXPECT_EQ(ft_errno, EACCES);
  EXPECT_STREQ(dst1, dst2);
  EXPECT_EQ(ft_result, dst1);
  EXPECT_EQ(std_result, dst2);
}