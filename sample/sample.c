#include <stdio.h>

int sum_int(int a, int b)
{
    return a + b;
}

double  sum_double  (double a, double b)
{
    return a + b;
}

int main(int argc, char const *argv[])
{
    int a = sum_int(5, 5);

    printf("%d", sum_int(5, 5));

    return 0;
}
