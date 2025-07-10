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