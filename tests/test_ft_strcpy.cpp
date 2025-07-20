#include <cstring>
#include <gtest/gtest.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

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
  const char *test_strings[] = {"", "a", "hello", "world", "test123", "hello world", "123!@#"};
  for (const char *str : test_strings) {
    char dst1[100], dst2[100];
    char *ft_result = ft_strcpy(dst1, str);
    char *std_result = strcpy(dst2, str);

    EXPECT_STREQ(dst1, dst2) << "Failed for string: " << str;
    EXPECT_EQ(ft_result, dst1) << "Return value mismatch for: " << str;
    EXPECT_EQ(std_result, dst2) << "Standard return value mismatch for: " << str;
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

/**
 * @brief 保護されたメモリページを超えて書き込みを試行する際のft_strcpy関数の動作テスト
 * 
 * このテストは、保護されたメモリ領域にアクセスしようとした際に、ft_strcpyが標準strcpyと
 * 同じ動作をすることを検証する。テストの流れ：
 * 1. mmapで2ページのメモリを確保
 * 2. mprotectで2ページ目をアクセス不可に設定
 * 3. 1ページ目の末尾近くにバッファを配置
 * 4. 保護されたページにオーバーフローするような文字列をコピー試行
 * 5. 両実装が同じようにSIGSEGVでクラッシュすることを確認
 * 
 * メモリ保護違反時の動作を捕捉・比較するため、各関数は別々の子プロセスで実行される。
 */
TEST_F(FtStrcpyTest, mmap_overflow_test) {
  const size_t page_size = getpagesize();

  pid_t ft_pid = fork();
  if (ft_pid == 0) {

    void *mem =
        mmap(nullptr, page_size * 2, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED)
      exit(1);
    if (mprotect((char *)mem + page_size, page_size, PROT_NONE) != 0)
      exit(1);

    char *dst = (char *)mem + page_size - 10;

    std::string src(50, 'x');
    ft_strcpy(dst, src.c_str());

    munmap(mem, page_size * 2);
    exit(0);
  }

  pid_t std_pid = fork();
  if (std_pid == 0) {
    void *mem =
        mmap(nullptr, page_size * 2, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED)
      exit(1);
    if (mprotect((char *)mem + page_size, page_size, PROT_NONE) != 0)
      exit(1);

    char *dst = (char *)mem + page_size - 10;
    std::string src(50, 'x');

    strcpy(dst, src.c_str());

    munmap(mem, page_size * 2);
    exit(0);
  }

  int ft_status, std_status;
  waitpid(ft_pid, &ft_status, 0);
  waitpid(std_pid, &std_status, 0);

  std::cout << "ft_strcpy exit status: " << ft_status << std::endl;
  std::cout << "strcpy exit status: " << std_status << std::endl;

  EXPECT_TRUE(WIFSIGNALED(ft_status)) << "ft_strcpy should crash with SIGSEGV";
  EXPECT_TRUE(WIFSIGNALED(std_status)) << "strcpy should crash with SIGSEGV";

  EXPECT_EQ(WTERMSIG(ft_status), WTERMSIG(std_status))
      << "Both functions should crash with same signal";

  EXPECT_EQ(WTERMSIG(ft_status), SIGSEGV) << "Should crash with SIGSEGV";
}