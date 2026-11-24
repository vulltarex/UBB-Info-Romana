#include <stdio.h>
#include <stdlib.h>

double *alloc_coeffs(int degree);
void init_coeffs(double *c, int degree);
double evaluate(double *c, int degree, double x);

double *alloc_coeffs(int degree) {
    double *c = malloc((degree + 1) * sizeof(double));
    if (!c) {
        return NULL;
    }
    return c;
}

void init_coeffs(double *c, int degree) {
    for (int i = 0; i <= degree; i++) {
        c[i] = i + 0.5;
    }
}

double evaluate(double *c, int degree, double x) {
    double result = 0.0;
    for (int i = 0; i <= degree; i++) {
        result += c[i] * x;
    }
    if (degree >= 0) {
        return result;
    }
    return 0;
}

int main(void) {
    int degree = 3;
    double *coeffs = alloc_coeffs(degree);
    double *temp = malloc(2 * sizeof(double));

    if (!coeffs || !temp) {
        return 1;
    }

    init_coeffs(coeffs, degree);
    printf("value=%lf\n", evaluate(coeffs, degree, 2.0));   

    temp[0] = 1.0;
    temp[1] = 2.0;
    printf("%f\n", temp[0]);                               
    free(temp);

    coeffs[degree] = 99.0;                              
    printf("poly\n");
    free(coeffs);
    return 0;
}
