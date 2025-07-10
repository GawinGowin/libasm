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
};

TEST_F(FtReadTest, read_from_file) {
  // Create a temporary file
  const char *temp_file = "/tmp/test_ft_read.txt";
  int fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
  ASSERT_GE(fd, 0);

  const char *test_data = "Hello, World!";
  write(fd, test_data, strlen(test_data));
  close(fd);

  // Read using ft_read
  fd = open(temp_file, O_RDONLY);
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
  // Create a temporary file
  const char *temp_file = "/tmp/test_ft_read_partial.txt";
  int fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
  ASSERT_GE(fd, 0);

  const char *test_data = "Hello, World!";
  write(fd, test_data, strlen(test_data));
  close(fd);

  // Read partial data
  fd = open(temp_file, O_RDONLY);
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
  // Create an empty file
  const char *temp_file = "/tmp/test_ft_read_empty.txt";
  int fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
  ASSERT_GE(fd, 0);
  close(fd);

  // Read from empty file
  fd = open(temp_file, O_RDONLY);
  ASSERT_GE(fd, 0);

  char buffer[10];
  ssize_t bytes_read = ft_read(fd, buffer, 10);
  EXPECT_EQ(bytes_read, 0);

  close(fd);
  unlink(temp_file);
}

TEST_F(FtReadTest, read_zero_bytes) {
  // Create a temporary file
  const char *temp_file = "/tmp/test_ft_read_zero.txt";
  int fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
  ASSERT_GE(fd, 0);

  const char *test_data = "Hello";
  write(fd, test_data, strlen(test_data));
  close(fd);

  // Read zero bytes
  fd = open(temp_file, O_RDONLY);
  ASSERT_GE(fd, 0);

  char buffer[10];
  ssize_t bytes_read = ft_read(fd, buffer, 0);
  EXPECT_EQ(bytes_read, 0);

  close(fd);
  unlink(temp_file);
}

TEST_F(FtReadTest, read_invalid_fd) {
  char buffer[10];
  ssize_t result = ft_read(-1, buffer, 10);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(errno, EBADF);
}

TEST_F(FtReadTest, read_closed_fd) {
  // Create and close a file descriptor
  const char *temp_file = "/tmp/test_ft_read_closed.txt";
  int fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
  ASSERT_GE(fd, 0);
  write(fd, "test", 4);
  close(fd);

  // Try to read from closed fd
  char buffer[10];
  ssize_t result = ft_read(fd, buffer, 10);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(errno, EBADF);

  unlink(temp_file);
}