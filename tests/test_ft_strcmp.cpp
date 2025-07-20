#include <cstring>
#include <gtest/gtest.h>

extern "C" {
#include "libasm.h"
}

class FtStrcmpTest : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(FtStrcmpTest, equal_strings) {
  const char *str1 = "hello";
  const char *str2 = "hello";
  int ft_result = ft_strcmp(str1, str2);
  int std_result = strcmp(str1, str2);
  EXPECT_EQ(ft_result, std_result);
  
  const char *empty1 = "";
  const char *empty2 = "";
  ft_result = ft_strcmp(empty1, empty2);
  std_result = strcmp(empty1, empty2);
  EXPECT_EQ(ft_result, std_result);
  
  const char *single1 = "a";
  const char *single2 = "a";
  ft_result = ft_strcmp(single1, single2);
  std_result = strcmp(single1, single2);
  EXPECT_EQ(ft_result, std_result);
}

TEST_F(FtStrcmpTest, different_strings) {
  const char *str1 = "a";
  const char *str2 = "b";
  int ft_result = ft_strcmp(str1, str2);
  int std_result = strcmp(str1, str2);
  EXPECT_EQ(ft_result, std_result);
  
  ft_result = ft_strcmp(str2, str1);
  std_result = strcmp(str2, str1);
  EXPECT_EQ(ft_result, std_result);
  
  const char *hello = "hello";
  const char *world = "world";
  ft_result = ft_strcmp(hello, world);
  std_result = strcmp(hello, world);
  EXPECT_EQ(ft_result, std_result);
  
  ft_result = ft_strcmp(world, hello);
  std_result = strcmp(world, hello);
  EXPECT_EQ(ft_result, std_result);
}

TEST_F(FtStrcmpTest, different_lengths) {
  const char *short_str = "abc";
  const char *long_str = "abcd";
  int ft_result = ft_strcmp(short_str, long_str);
  int std_result = strcmp(short_str, long_str);
  EXPECT_EQ(ft_result, std_result);
  
  ft_result = ft_strcmp(long_str, short_str);
  std_result = strcmp(long_str, short_str);
  EXPECT_EQ(ft_result, std_result);
  
  const char *empty = "";
  const char *non_empty = "a";
  ft_result = ft_strcmp(empty, non_empty);
  std_result = strcmp(empty, non_empty);
  EXPECT_EQ(ft_result, std_result);
  
  ft_result = ft_strcmp(non_empty, empty);
  std_result = strcmp(non_empty, empty);
  EXPECT_EQ(ft_result, std_result);
}

TEST_F(FtStrcmpTest, case_sensitivity) {
  const char *upper = "Hello";
  const char *lower = "hello";
  int ft_result = ft_strcmp(upper, lower);
  int std_result = strcmp(upper, lower);
  EXPECT_EQ((ft_result != 0), (std_result != 0));
  EXPECT_EQ(ft_result, std_result);
}

TEST_F(FtStrcmpTest, special_characters) {
  const char *str1 = "test\n";
  const char *str2 = "test\n";
  int ft_result = ft_strcmp(str1, str2);
  int std_result = strcmp(str1, str2);
  EXPECT_EQ(ft_result, std_result);
  
  const char *str3 = "test\n";
  const char *str4 = "test\t";
  ft_result = ft_strcmp(str3, str4);
  std_result = strcmp(str3, str4);
  EXPECT_EQ((ft_result != 0), (std_result != 0));
  
  const char *special1 = "!@#";
  const char *special2 = "!@#";
  ft_result = ft_strcmp(special1, special2);
  std_result = strcmp(special1, special2);
  EXPECT_EQ(ft_result, std_result);
}

TEST_F(FtStrcmpTest, compare_with_stdlib) {
  const char *test_pairs[][2] = {
      {"", ""},        {"a", "a"},         {"hello", "hello"},
      {"a", "b"},      {"hello", "world"}, {"abc", "abcd"},
      {"abcd", "abc"}, {"Hello", "hello"}, {"test123", "test456"},
      {"", "nonempty"}};

  for (auto &pair : test_pairs) {
    int ft_result = ft_strcmp(pair[0], pair[1]);
    int std_result = strcmp(pair[0], pair[1]);

    // Check if signs are the same
    if (ft_result == 0) {
      EXPECT_EQ(std_result, 0)
          << "Failed for: " << pair[0] << " vs " << pair[1];
    } else if (ft_result > 0) {
      EXPECT_GT(std_result, 0)
          << "Failed for: " << pair[0] << " vs " << pair[1];
    } else {
      EXPECT_LT(std_result, 0)
          << "Failed for: " << pair[0] << " vs " << pair[1];
    }
  }
}


TEST_F(FtStrcmpTest, very_long_strings) {
  // Test with very long strings
  std::string long_str1(10000, 'a');
  std::string long_str2(10000, 'a');
  std::string long_str3(10000, 'b');
  
  int ft_result = ft_strcmp(long_str1.c_str(), long_str2.c_str());
  int std_result = strcmp(long_str1.c_str(), long_str2.c_str());
  EXPECT_EQ(ft_result, std_result);
  
  ft_result = ft_strcmp(long_str1.c_str(), long_str3.c_str());
  std_result = strcmp(long_str1.c_str(), long_str3.c_str());
  EXPECT_EQ(ft_result, std_result);
}

TEST_F(FtStrcmpTest, boundary_characters) {
  // Test with boundary ASCII characters
  const char *str1 = "\x00\x01\x02";
  const char *str2 = "\x00\x01\x02";
  int ft_result = ft_strcmp(str1, str2);
  int std_result = strcmp(str1, str2);
  EXPECT_EQ(ft_result, std_result);
  
  const char *str3 = "\xFF\xFE\xFD";
  const char *str4 = "\xFF\xFE\xFD";
  ft_result = ft_strcmp(str3, str4);
  std_result = strcmp(str3, str4);
  EXPECT_EQ(ft_result, std_result);
}

TEST_F(FtStrcmpTest, errno_not_modified) {
  // Test that errno is not modified during normal operation
  const char *str1 = "hello";
  const char *str2 = "world";
  
  // Set errno to a specific value
  errno = EINVAL;
  int ft_result = ft_strcmp(str1, str2);
  int ft_errno = errno;
  
  errno = EINVAL;
  int std_result = strcmp(str1, str2);
  int std_errno = errno;
  
  // Both should preserve errno
  EXPECT_EQ(ft_errno, std_errno);
  EXPECT_EQ(ft_errno, EINVAL);
  EXPECT_EQ(ft_result, std_result);
  
  // Test with equal strings
  errno = EACCES;
  ft_result = ft_strcmp(str1, str1);
  ft_errno = errno;
  
  errno = EACCES;
  std_result = strcmp(str1, str1);
  std_errno = errno;
  
  EXPECT_EQ(ft_errno, std_errno);
  EXPECT_EQ(ft_errno, EACCES);
  EXPECT_EQ(ft_result, std_result);
  EXPECT_EQ(ft_result, 0);
}