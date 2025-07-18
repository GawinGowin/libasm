#include <stdio.h>

// Declaration of the assembly function
extern long fibonacci(long n);

int main() {
    printf("Fibonacci sequence test:\n");
    
    // Test cases for fibonacci function
    for (int i = 0; i <= 10; i++) {
        long result = fibonacci(i);
        printf("fibonacci(%d) = %ld\n", i, result);
    }
    
    // Additional test cases
    printf("\nAdditional test cases:\n");
    printf("fibonacci(15) = %ld\n", fibonacci(15));
    printf("fibonacci(20) = %ld\n", fibonacci(20));
    
    return 0;
}