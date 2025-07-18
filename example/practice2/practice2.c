#include <stdio.h>
#include <stdint.h>

extern uint64_t factorial(uint64_t n);

int main() {
    uint64_t test_cases[] = {0, 1, 3, 5, 10};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    printf("階乗計算テスト:\n");
    printf("================\n");
    
    for (int i = 0; i < num_tests; i++) {
        uint64_t n = test_cases[i];
        uint64_t result = factorial(n);
        printf("factorial(%lu) = %lu\n", n, result);
    }
    
    return 0;
}