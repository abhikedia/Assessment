#include <stdio.h>
#include <stdlib.h>

void calculateValueToAdd(int a, int b, int c, int x, int *temp)
{
    int temp3 = c - a * (x - 10);
    int val1 = temp3 / b;
    temp3 = c - a * (x + 10);
    int val2 = temp3 / b;
    int x1 = (x - 10) < (x + 10) ? x - 10 : x + 10;
    int y1 = val1 < val2 ? val1 : val2;
    int valueToAdd = 0;
    if (!(x1 >= 0 && y1 >= 0))
        valueToAdd = x1 < y1 ? x1 : y1;
    x1 = (x - 10) > (x + 10) ? x - 10 : x + 10;
    y1 = val1 > val2 ? val1 : val2;
    valueToAdd = abs(valueToAdd);
    *temp = x1;
    *(temp + 1) = y1;
    *(temp + 2) = valueToAdd;
}

void plotGraph(int a, int b, int c, int p, int q, int r, int x, int y)
{
    int temp[3];
    calculateValueToAdd(a, b, c, x, temp);
    int x1 = temp[0], y1 = temp[1], v1 = temp[2];
    calculateValueToAdd(p, q, r, x, temp);
    int x2 = temp[0], y2 = temp[1], v2 = temp[2];
    int valueToAdd = v1 < v2 ? v2 : v1;

    int x3 = x1 < x2 ? x2 : x1;
    int y3 = y1 < y2 ? y2 : y1;
    int arr[x3 + valueToAdd][y3 + valueToAdd];
    int i, j;
    for (i = 0; i < x3 + valueToAdd; i++)
    {
        for (j = 0; j < y3 + valueToAdd; j++)
            arr[i][j] = 0;
    }

    for (i = x - 10; i < x + 10; i++)
    {
        int temp3 = c - a * i;
        y = temp3 / b;
        arr[i + valueToAdd][y + valueToAdd] = 1;
    }

    for (i = x - 10; i < x + 10; i++)
    {
        int temp3 = r - p * i;
        y = temp3 / q;
        arr[i + valueToAdd][y + valueToAdd] = 2;
    }
    printf("\n");
    for (i = 0; i < x3 + valueToAdd; i++)
    {
        for (j = 0; j < y3 + valueToAdd; j++)
            arr[i][j] == 0 ? printf("%c ", ' ') : printf("%d ", arr[i][j]);

        printf("\n");
    }
}

int compare_float(float f1, float f2)
{
    float precision = 0.00001;
    if (((f1 - precision) < f2) && ((f1 + precision) > f2))
        return 1;
    return 0;
}

void substitution(int a, int b, int c, int p, int q, int r, float *ans)
{
    printf("\n\nCalculating using Substitution Method\n\n");
    int temp1 = b * r - q * c;
    int temp2 = b * p - q * a;
    float x = (float)temp1 / temp2;
    printf("The calculated value of x is = %.2f\n", x);
    int temp3 = c - a * x;
    float y = (float)temp3 / b;
    printf("The calculated value of y is = %.2f\n", y);
    *ans = x;
    *(ans + 1) = y;
}

void matrixMultiplication(int a, int b, int c, int p, int q, int r, float *ans)
{
    printf("\n\nCalculating using Matrix Multiplication Method (X = inverse(A)B)\n");
    int determinant = a * q - b * p;
    printf("The value of determinant is = %d", determinant);
    printf("\nThe calculated value of A inverse is:\n");
    float inverse[2][2] = {{q, -b}, {-p, a}};
    int B[2][1] = {{c}, {r}};
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%.2f\t", (float)inverse[i][j] / determinant);
            inverse[i][j] = (float)inverse[i][j] / determinant;
        }
        printf("\n");
    }
    printf("\nThe value of B is:\n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 1; j++)
            printf("%d", B[i][j]);
        printf("\n");
    }
    float res[2][1];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < 2; k++)
                res[i][j] += inverse[i][k] * B[k][j];
        }
    }
    printf("The value of resultant matrix is:\n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 1; j++)
            printf("%.2f", res[i][j]);
        printf("\n");
    }
    printf("\nThe calculated value of x is = %.2f\n", res[0][0]);
    printf("The calculated value of y is = %.2f\n", res[1][0]);
    *ans = res[0][0];
    *(ans + 1) = res[1][0];
}

int main()
{
    int a, b, c, p, q, r;
    printf("The equations are in the format of:\nax + by = c and\npx + qy = r");
    printf("\nEnter the value of a = ");
    scanf("%d", &a);
    printf("Enter the value of b = ");
    scanf("%d", &b);
    printf("Enter the value of c = ");
    scanf("%d", &c);
    printf("Enter the value of p = ");
    scanf("%d", &p);
    printf("Enter the value of q = ");
    scanf("%d", &q);
    printf("Enter the value of r = ");
    scanf("%d", &r);
    float m1 = -(float)a / b;
    float m2 = -(float)p / q;
    if (compare_float(m1, m2))
    {
        printf("\nThe lines are parallel and solution doesn't exist");
        return 0;
    }
    float ans1[2], ans2[2];
    substitution(a, b, c, p, q, r, ans1);
    matrixMultiplication(a, b, c, p, q, r, ans2);
    if (compare_float(ans1[1], ans2[1]) && compare_float(ans1[0], ans2[0]))
    {
        printf("\n\nThe coordinates from both the methods match!");
        plotGraph(a, b, c, p, q, r, ans1[0], ans1[1]);
    }
    else
        printf("\n\nThe coordinates from both methods are different");
    return 0;
}