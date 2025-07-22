#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <gtest/gtest.h>
#include <unistd.h>

extern "C" {
#include "libasm.h"
}

class FtReadTest : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper to create temp file with data
  int createTempFile(const char* filename, const char* data) {
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd >= 0 && data) {
      write(fd, data, strlen(data));
      close(fd);
    }
    return fd;
  }

  // Helper to open file for reading
  int openForReading(const char* filename) {
    return open(filename, O_RDONLY);
  }

  // Helper to compare ft_read with standard read behavior
  void compareReadBehavior(int fd, void* buffer, size_t count) {
    errno = 0;
    ssize_t ft_result = ft_read(fd, buffer, count);
    int ft_errno = errno;
    
    lseek(fd, 0, SEEK_SET);
    errno = 0;
    ssize_t std_result = read(fd, buffer, count);
    int std_errno = errno;
    
    EXPECT_EQ(ft_result, std_result);
    EXPECT_EQ(ft_errno, std_errno);
  }

  // Helper to compare error behavior (no seek needed)
  void compareErrorBehavior(int fd, void* buffer, size_t count) {
    errno = 0;
    ssize_t ft_result = ft_read(fd, buffer, count);
    int ft_errno = errno;
    
    errno = 0;
    ssize_t std_result = read(fd, buffer, count);
    int std_errno = errno;
    
    EXPECT_EQ(ft_result, std_result);
    EXPECT_EQ(ft_errno, std_errno);
  }
};

TEST_F(FtReadTest, read_from_file) {
  const char *temp_file = "/tmp/test_ft_read.txt";
  const char *test_data = "Hello, World!";
  
  ASSERT_GE(createTempFile(temp_file, test_data), 0);
  int fd = openForReading(temp_file);
  ASSERT_GE(fd, 0);

  char buffer[100];
  ssize_t bytes_read = ft_read(fd, buffer, 13);
  EXPECT_EQ(bytes_read, 13);
  buffer[bytes_read] = '\0';
  EXPECT_STREQ(buffer, "Hello, World!");

  close(fd);
  unlink(temp_file);
}

TEST_F(FtReadTest, read_partial) {
  const char *temp_file = "/tmp/test_ft_read_partial.txt";
  const char *test_data = "Hello, World!";
  
  ASSERT_GE(createTempFile(temp_file, test_data), 0);
  int fd = openForReading(temp_file);
  ASSERT_GE(fd, 0);

  char buffer[6];
  ssize_t bytes_read = ft_read(fd, buffer, 5);
  EXPECT_EQ(bytes_read, 5);
  buffer[bytes_read] = '\0';
  EXPECT_STREQ(buffer, "Hello");

  close(fd);
  unlink(temp_file);
}

TEST_F(FtReadTest, read_empty_file) {
  const char *temp_file = "/tmp/test_ft_read_empty.txt";
  
  ASSERT_GE(createTempFile(temp_file, nullptr), 0);
  int fd = openForReading(temp_file);
  ASSERT_GE(fd, 0);

  char buffer[10];
  ssize_t bytes_read = ft_read(fd, buffer, 10);
  EXPECT_EQ(bytes_read, 0);

  close(fd);
  unlink(temp_file);
}

TEST_F(FtReadTest, read_zero_bytes) {
  const char *temp_file = "/tmp/test_ft_read_zero.txt";
  
  ASSERT_GE(createTempFile(temp_file, "Hello"), 0);
  int fd = openForReading(temp_file);
  ASSERT_GE(fd, 0);

  char buffer[10];
  ssize_t bytes_read = ft_read(fd, buffer, 0);
  EXPECT_EQ(bytes_read, 0);

  close(fd);
  unlink(temp_file);
}

TEST_F(FtReadTest, read_invalid_fd) {
  char buffer[10];
  compareErrorBehavior(-1, buffer, 10);
  
  errno = 0;
  EXPECT_EQ(ft_read(-1, buffer, 10), -1);
  EXPECT_EQ(errno, EBADF);
}

TEST_F(FtReadTest, read_closed_fd) {
  const char *temp_file = "/tmp/test_ft_read_closed.txt";
  int fd = createTempFile(temp_file, "test");
  ASSERT_GE(fd, 0);
  close(fd);

  char buffer[10];
  compareErrorBehavior(fd, buffer, 10);
  
  errno = 0;
  EXPECT_EQ(ft_read(fd, buffer, 10), -1);
  EXPECT_EQ(errno, EBADF);

  unlink(temp_file);
}


TEST_F(FtReadTest, read_large_buffer) {
  const char *temp_file = "/tmp/test_ft_read_large.txt";
  
  ASSERT_GE(createTempFile(temp_file, "test"), 0);
  int fd = openForReading(temp_file);
  ASSERT_GE(fd, 0);

  char buffer[1000];
  compareReadBehavior(fd, buffer, 1000);
  
  lseek(fd, 0, SEEK_SET);
  ssize_t result = ft_read(fd, buffer, 1000);
  EXPECT_EQ(result, 4);

  close(fd);
  unlink(temp_file);
}

TEST_F(FtReadTest, read_from_writeonly_file) {
  const char *temp_file = "/tmp/test_ft_read_writeonly.txt";
  int fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
  ASSERT_GE(fd, 0);
  write(fd, "test", 4);

  char buffer[10];
  compareErrorBehavior(fd, buffer, 10);
  
  errno = 0;
  EXPECT_EQ(ft_read(fd, buffer, 10), -1);
  EXPECT_EQ(errno, EBADF);

  close(fd);
  unlink(temp_file);
}

/**
 * @brief nullバッファでの読み込みテスト（コメントアウト）
 * 
 * このテストはGCC属性__fortified_attr_access(__write_only__, 2, 3)により
 * コンパイル時エラーが発生するためコメントアウトしています。
 * nullptrを第二引数に渡すとコンパイラが静的解析で検出し、
 * "argument 2 is null but the corresponding size argument 3 value is 10 [-Werror=nonnull]"
 * エラーが発生します。このため実行時テストではなく、
 * コンパイル時にnullポインタアクセスが防止されます。
 */
// TEST_F(FtReadTest, DISABLED_read_null_buffer) {
//   const char *temp_file = "/tmp/test_ft_read_null.txt";
  
//   ASSERT_GE(createTempFile(temp_file, "test"), 0);
//   int fd = openForReading(temp_file);
//   ASSERT_GE(fd, 0);

//   compareErrorBehavior(fd, nullptr, 10);
  
//   errno = 0;
//   EXPECT_EQ(ft_read(fd, nullptr, 10), -1);
//   EXPECT_EQ(errno, EFAULT);

//   close(fd);
//   unlink(temp_file);
// }