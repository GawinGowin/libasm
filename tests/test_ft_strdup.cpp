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