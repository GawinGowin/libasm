#include <stdio.h>
#include <string.h>
#include <stdint.h>

extern void *my_memcpy(void *dest, const void *src, size_t n);

int main() {
    printf("my_memcpy テスト:\n");
    printf("========================================\n");
    
    // Test 1: Basic string copy
    {
        char src1[] = "Hello, World!";
        char dest1[20];
        char dest1_std[20];
        
        my_memcpy(dest1, src1, strlen(src1) + 1);
        memcpy(dest1_std, src1, strlen(src1) + 1);
        
        printf("テスト 1: 文字列コピー\n");
        printf("  元:     \"%s\"\n", src1);
        printf("  my_memcpy: \"%s\"\n", dest1);
        printf("  memcpy:    \"%s\"\n", dest1_std);
        printf("  結果: %s\n", (strcmp(dest1, dest1_std) == 0) ? "✓ PASS" : "✗ FAIL");
        printf("\n");
    }
    
    // Test 2: Integer array copy
    {
        int src2[] = {1, 2, 3, 4, 5};
        int dest2[5];
        int dest2_std[5];
        
        my_memcpy(dest2, src2, sizeof(src2));
        memcpy(dest2_std, src2, sizeof(src2));
        
        printf("テスト 2: 整数配列コピー\n");
        printf("  元:     [%d, %d, %d, %d, %d]\n", src2[0], src2[1], src2[2], src2[3], src2[4]);
        printf("  my_memcpy: [%d, %d, %d, %d, %d]\n", dest2[0], dest2[1], dest2[2], dest2[3], dest2[4]);
        printf("  memcpy:    [%d, %d, %d, %d, %d]\n", dest2_std[0], dest2_std[1], dest2_std[2], dest2_std[3], dest2_std[4]);
        printf("  結果: %s\n", (memcmp(dest2, dest2_std, sizeof(src2)) == 0) ? "✓ PASS" : "✗ FAIL");
        printf("\n");
    }
    
    // Test 3: Empty copy
    {
        char src3[] = "test";
        char dest3[10] = "original";
        char dest3_std[10] = "original";
        
        my_memcpy(dest3, src3, 0);
        memcpy(dest3_std, src3, 0);
        
        printf("テスト 3: 0バイトコピー\n");
        printf("  my_memcpy: \"%s\"\n", dest3);
        printf("  memcpy:    \"%s\"\n", dest3_std);
        printf("  結果: %s\n", (strcmp(dest3, dest3_std) == 0) ? "✓ PASS" : "✗ FAIL");
        printf("\n");
    }
    
    return 0;
}