#include <stdio.h>
#include <errno.h>
#include <string.h>

extern long safe_divide(long dividend, long divisor);

int main() {
    long result;
    
    printf("=== Safe Division Function Test ===\n");
    
    // Test case 1: Normal division
    printf("\nTest 1: 20 / 4\n");
    errno = 0;
    result = safe_divide(20, 4);
    printf("Result: %ld, errno: %d\n", result, errno);
    
    // Test case 2: Division with remainder
    printf("\nTest 2: 17 / 3\n");
    errno = 0;
    result = safe_divide(17, 3);
    printf("Result: %ld, errno: %d\n", result, errno);
    
    // Test case 3: Negative numbers
    printf("\nTest 3: -15 / 3\n");
    errno = 0;
    result = safe_divide(-15, 3);
    printf("Result: %ld, errno: %d\n", result, errno);
    
    // Test case 4: Division by zero (error case)
    printf("\nTest 4: 10 / 0 (Division by zero)\n");
    errno = 0;
    result = safe_divide(10, 0);
    printf("Result: %ld, errno: %d (%s)\n", result, errno, strerror(errno));
    
    // Test case 5: Zero divided by number
    printf("\nTest 5: 0 / 5\n");
    errno = 0;
    result = safe_divide(0, 5);
    printf("Result: %ld, errno: %d\n", result, errno);
    
    return 0;
}