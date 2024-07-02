#include <stdio.h>
#include <math.h>
#include <stdlib.h> // Include the necessary header for EXIT_FAILURE

int main() // Correct the function signature
{
    int n;
    printf("Enter the number of data sets:\n"); // Correct the prompt
    scanf("%i", &n); // Correct the format specifier

    float MG, VG, MFB, NMSE, R;
    FILE *Error = fopen("Error.txt", "r");

    if (Error == NULL) {
        perror("Error opening the file");
        return EXIT_FAILURE;
    }

    float X0[n];
    float Xp[n];

    for (int i = 0; i < n; i++) {
        fscanf(Error, "%f", &X0[i]);
        fscanf(Error, "%f", &Xp[i]);
    }

    fclose(Error);

    float s = 0, t = 0, r = 0, q = 0, v = 0, w = 0;

    for (int i = 0; i < n; i++) {
        s = s + (log(X0[i])) / n;
        t = t + (log(Xp[i])) / n;
        r = r + (pow((log(X0[i]) - log(Xp[i])), 2)) / n;
        q = q + (Xp[i] - X0[i]) / (Xp[i] + X0[i]);
        v = v + X0[i] / n;
        w = w + Xp[i] / n;
    }

    float x = 0, a = 0, b = 0, c = 0;

    for (int j = 0; j < n; j++) {
        x = x + (pow((Xp[j] - X0[j]), 2)) / (v * w);
        a = a + pow((Xp[j] - w), 2);
        b = b + pow((X0[j] - v), 2);
        c = c + (Xp[j] - w) * (X0[j] - v);
    }

    MG = exp(s - t);
    VG = exp(r);
    MFB = 2 * q / n;
    NMSE = x / n;
    R = c / sqrt(a * b);

    printf("MG=%f\nVG=%f\nMFB=%f\nNMSE=%f\nCorrelation coefficient=%f\n", MG, VG, MFB, NMSE, R);

    return 0; // Indicate successful completion of the program
}
