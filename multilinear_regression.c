// #include<stdio.h>
// #include<stdlib.h>
// #include<math.h>

// void mult(int m,int n,int l,float matrix1[m][n], float matrix2[n][l], float matrix[m][l]) {
//     for (int k = 0; k < m; k++) {
//         for (int i = 0; i < l; i++) {
//             matrix[k][i] = 0; 
//             for (int j = 0; j < n; j++) {
//                 matrix[k][i] += matrix1[k][j] * matrix2[j][i];
//             }
//         }
//     }
// }

// void transpose(int m,int n,float matrix1[m][n], float matrix5[n][m]) {
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             matrix5[i][j] = matrix1[j][i];
//         }
//     }
// }

// void swapRows(double matrix[4][8], int row1, int row2) {
//     for (int i = 0; i < 8; i++) {
//         double temp = matrix[row1][i];
//         matrix[row1][i] = matrix[row2][i];
//         matrix[row2][i] = temp;
//     }
// }

// int inverseMatrix(float matrix[4][4], float inverse[4][4]) {
//     int i, j, k;
//     double temp;

    
//     double augmentedMatrix[4][8];
//     for (i = 0; i < 4; i++) {
//         for (j = 0; j < 4; j++) {
//             augmentedMatrix[i][j] = matrix[i][j];
//             augmentedMatrix[i][j + 4] = (i == j) ? 1.0 : 0.0;
//         }
//     }
   
//     for (i = 0; i < 4; i++) {
      
//         if (augmentedMatrix[i][i] == 0.0) {
            
//             for (j = i + 1; j < 4; j++) {
//                 if (augmentedMatrix[j][i] != 0.0) {
//                     swapRows(augmentedMatrix, i, j);
//                     break;
//                 }
//             }
//             if (j == 4) {
                
//                 return 0;
//             }
//         }
       
//         temp = augmentedMatrix[i][i];
//         for (j = 0; j < 8; j++) {
//             augmentedMatrix[i][j] /= temp;
//         }
       
//         for (j = 0; j < 4; j++) {
//             if (j != i) {
//                 temp = augmentedMatrix[j][i];
//                 for (k = 0; k < 8; k++) {
//                     augmentedMatrix[j][k] -= temp * augmentedMatrix[i][k];
//                 }
//             }
//         }
//     }

//     for (i = 0; i < 4; i++) {
//         for (j = 0; j < 4; j++) {
//             inverse[i][j] = augmentedMatrix[i][j + 4];
//         }
//     }
//     return 1;
 
// }

// int main()
// {
//     int z,k;
//     printf("enter number of parameters:\n");
//     scanf("%i",&z);
    
//     printf("enter number of cities:\n");
//     scanf("%i",&k);
//     FILE *inputFile = fopen("input.txt", "r");
//     if (inputFile == NULL) {
//         perror("Error opening the file");
//         return EXIT_FAILURE;
//     }
    
//     float M[k][z+1];
//     for(int i=0;i<k;i++)
//     {
//         for(int j=0;j<=z;j++)
//         {
//             fscanf(inputFile, "%f", &M[i][j]);
//         }
//     }
//     float D[k][1];
//     for(int i=0;i<k;i++)
//     {
//         for(int j=0;j<1;j++)
//         {
//             fscanf(inputFile, "%f", &D[i][j]);
            
//         }
        
//     }
//     fclose(inputFile);

//     int n=k;
//     printf("%i",n);
//     float inverse[z+1][z+1];
//     float Xtranspose[z+1][n];
//     float product[z+1][z+1];
//     float product1[z+1][n];
//     float product2[z+1][1];
    
//     transpose(n,z+1,M, Xtranspose);
//     mult(z+1,n,z+1,Xtranspose, M, product);
//     inverseMatrix(product, inverse);
//     mult(z+1,z+1,k,inverse, Xtranspose,product1);
//     mult(z+1,n,1,product1, D, product2);
    
//     printf("Regression plane is:\n");
//     printf("AQI=%f+%f(Rainfall)+%f(Temperature)+%f(Population)\n",product2[0][0],product2[1][0],product2[2][0],product2[3][0]);  

// }

