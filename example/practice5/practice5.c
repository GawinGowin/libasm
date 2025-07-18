#include <stdio.h>
#include <string.h>
#include <stdint.h>

extern size_t my_strlen(const char *str);

int main() {
    const char *test_cases[] = {
        "Hello, World!",
        "",
        "a",
        "This is a longer string for testing",
        "12345"
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    printf("my_strlen テスト:\n");
    printf("========================================\n");
    
    for (int i = 0; i < num_tests; i++) {
        size_t my_result = my_strlen(test_cases[i]);
        size_t std_result = strlen(test_cases[i]);
        
        printf("テスト %d: \"%s\"\n", i + 1, test_cases[i]);
        printf("  my_strlen: %zu\n", my_result);
        printf("  strlen:    %zu\n", std_result);
        printf("  結果: %s\n", (my_result == std_result) ? "✓ PASS" : "✗ FAIL");
        printf("\n");
    }
    
    return 0;
}