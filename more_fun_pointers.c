#include <math.h>
#include <stdio.h>

// Function taking a function pointer as an argument
double compute_sum(double (*funcp)(double), double lo, double hi) {
    double sum = 0.0;

    // Add values returned by the pointed-to function '*funcp'
    int i;
    for (i = 0; i <= 100; i++) {
        // Use the function pointer 'funcp' to invoke the function
        double x = i / 100.0 * (hi - lo) + lo;
        double y = funcp(x);
        sum += y;
    }
    return sum / 101.0 * (hi - lo);
}

double square(double x) {
     return x * x;
}

int main(void) {
    double  sum;

    // Use standard library function 'sin()' as the pointed-to function
    sum = compute_sum(sin, 0.0, 1.0);
    printf("sum(sin): %g\n", sum);

    // Use standard library function 'cos()' as the pointed-to function
    sum = compute_sum(cos, 0.0, 1.0);
    printf("sum(cos): %g\n", sum);

    // Use user-defined function 'square()' as the pointed-to function
    sum = compute_sum(square, 0.0, 1.0);
    printf("sum(square): %g\n", sum);

    return 0;
}
