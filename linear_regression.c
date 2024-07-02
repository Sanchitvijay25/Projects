#include <stdio.h>
#include <stdlib.h>

void mult(int m,int n,int l,float matrix1[m][n], float matrix2[n][l], float matrix[m][l]) {
    for (int k = 0; k < m; k++) {
        for (int i = 0; i < l; i++) {
            matrix[k][i] = 0; 
            for (int j = 0; j < n; j++) {
                matrix[k][i] += matrix1[k][j] * matrix2[j][i];
            }
        }
    }
}

void transpose(int m,int n,float matrix1[m][2], float matrix5[2][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix5[i][j] = matrix1[j][i];
        }
    }
}

void MatrixInverse(float A[2][2], float inverse[2][2]) {
    inverse[0][0] = A[1][1];
    inverse[0][1] = -A[0][1];
    inverse[1][0] = -A[1][0];
    inverse[1][1] = A[0][0];

    float s = A[0][0] * A[1][1] - A[1][0] * A[0][1];
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inverse[i][j] = inverse[i][j] / s;
        }
    }
}

int main() {
    int n;
    printf("Enter the number of points n: ");
    scanf("%i", &n);
    FILE *linear = fopen("linear.txt", "r");
    if (linear == NULL) {
        perror("Error opening the file");
        return EXIT_FAILURE;
    }
    

    float matrixY[n][1];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<1;j++)
        {
            fscanf(linear, "%f", &matrixY[i][j]);
        }
    }
    
    float matrixX[n][2];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<2;j++)
        {
            fscanf(linear, "%f", &matrixX[i][j]); 
        }
    }
    fclose(linear);
    

   
    float inverse[2][2];
    float Xtranspose[2][n];
    float product[2][2];
    float product1[2][n];
    float product2[2][1];
   

    transpose(n,2,matrixX, Xtranspose);
    mult(2,n,2,Xtranspose, matrixX, product);
    MatrixInverse(product, inverse);
    mult(2,2,n,inverse, Xtranspose,product1);
    mult(2,n,1,product1, matrixY, product2);
    

    printf("Regression line is:\n y=%f+%f(parameter)\n",product2[0][0],product2[1][0]);
    
    return 0;
}