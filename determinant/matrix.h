#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

// matrix struct with 2 dimensions 
typedef struct {
    int num_rows;
    int num_cols;
    double **data;
} Matrix;

Matrix createMatrix(FILE* file);
void freeMatrix(Matrix m);
void printMatrix(Matrix m);
double calculateMatrix(Matrix m);

#endif