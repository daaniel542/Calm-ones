#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filepath>\n", argv[0]);
        return 1;
    }
    
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }

    Matrix m = createMatrix(fp);
    fclose(fp);

    double det = calculateMatrix(m);
    printf("The determinant is %.2lf.\n", det);
    
    freeMatrix(m);
    return 0;
}