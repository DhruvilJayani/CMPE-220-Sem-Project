#include <stdio.h>

// recursive factorial function
int factorial(int n) {
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    int num = 7;
    int result = factorial(num);
    printf("Factorial of %d = %d\n", num, result);
    return 0;
}
