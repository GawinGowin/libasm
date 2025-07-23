#include <gtest/gtest.h>

extern "C" {
#include "libasm_bonus.h"
#include <ctype.h>
}

TEST(FtIsSpaceTest, HandlesAllCharacters) {
  for (int c = -256; c <= 512; c++) {
    EXPECT_EQ(bool(isspace(c)), bool(ft_isspace(c))) 
      << "Character " << c << " (0x" << std::hex << c << ")";
  }
}
