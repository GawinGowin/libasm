#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <gtest/gtest.h>
#include <unistd.h>

extern "C" {
#include "libasm.h"
}

class FtWriteTest : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(FtWriteTest, write_to_file) {
  const char *temp_file = "/tmp/test_ft_write.txt";
  int fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
  ASSERT_GE(fd, 0);

  const char *test_data = "Hello, World!";
  ssize_t bytes_written = ft_write(fd, test_data, strlen(test_data));
  EXPECT_EQ(bytes_written, 13);

  close(fd);

  // Verify the content
  fd = open(temp_file, O_RDONLY);
  ASSERT_GE(fd, 0);

  char buffer[20];
  ssize_t bytes_read = read(fd, buffer, 20);
  buffer[bytes_read] = '\0';
  EXPECT_STREQ(buffer, "Hello, World!");

  close(fd);
  unlink(temp_file);
}

TEST_F(FtWriteTest, write_partial) {
  const char *temp_file = "/tmp/test_ft_write_partial.txt";
  int fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
  ASSERT_GE(fd, 0);

  const char *test_data = "Hello, World!";
  ssize_t bytes_written = ft_write(fd, test_data, 5);
  EXPECT_EQ(bytes_written, 5);

  close(fd);

  // Verify the content
  fd = open(temp_file, O_RDONLY);
  ASSERT_GE(fd, 0);

  char buffer[10];
  ssize_t bytes_read = read(fd, buffer, 10);
  buffer[bytes_read] = '\0';
  EXPECT_STREQ(buffer, "Hello");

  close(fd);
  unlink(temp_file);
}

TEST_F(FtWriteTest, write_empty_buffer) {
  const char *temp_file = "/tmp/test_ft_write_empty.txt";
  int fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
  ASSERT_GE(fd, 0);

  ssize_t bytes_written = ft_write(fd, "", 0);
  EXPECT_EQ(bytes_written, 0);

  close(fd);
  unlink(temp_file);
}

TEST_F(FtWriteTest, write_zero_bytes) {
  const char *temp_file = "/tmp/test_ft_write_zero.txt";
  int fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
  ASSERT_GE(fd, 0);

  const char *test_data = "Hello";
  ssize_t bytes_written = ft_write(fd, test_data, 0);
  EXPECT_EQ(bytes_written, 0);

  close(fd);
  unlink(temp_file);
}

TEST_F(FtWriteTest, write_invalid_fd) {
  const char *test_data = "Hello";
  ssize_t result = ft_write(-1, test_data, 5);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(errno, EBADF);
}

TEST_F(FtWriteTest, write_to_readonly_file) {
  const char *temp_file = "/tmp/test_ft_write_readonly.txt";

  // Create file and close it
  int fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
  ASSERT_GE(fd, 0);
  close(fd);

  // Open as read-only
  fd = open(temp_file, O_RDONLY);
  ASSERT_GE(fd, 0);

  const char *test_data = "Hello";
  ssize_t result = ft_write(fd, test_data, 5);
  EXPECT_EQ(result, -1);
  EXPECT_EQ(errno, EBADF);

  close(fd);
  unlink(temp_file);
}

TEST_F(FtWriteTest, write_large_data) {
  const char *temp_file = "/tmp/test_ft_write_large.txt";
  int fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
  ASSERT_GE(fd, 0);

  std::string large_data(1000, 'A');
  ssize_t bytes_written = ft_write(fd, large_data.c_str(), large_data.size());
  EXPECT_EQ(bytes_written, 1000);

  close(fd);

  // Verify the content
  fd = open(temp_file, O_RDONLY);
  ASSERT_GE(fd, 0);

  char buffer[1100];
  ssize_t bytes_read = read(fd, buffer, 1100);
  buffer[bytes_read] = '\0';
  EXPECT_STREQ(buffer, large_data.c_str());

  close(fd);
  unlink(temp_file);
}