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