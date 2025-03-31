#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>


/*
	this function creates the matrix from the user's input
	@file: this is the file pointer with the file path
*/
Matrix createMatrix(FILE* file) {
    Matrix m1;
    fscanf(file, "%d %d", &m1.num_rows, &m1.num_cols);

    m1.data = malloc(m1.num_rows * sizeof(double*));
    for(int i = 0; i < m1.num_rows; i++) {
        m1.data[i] = malloc(m1.num_cols * sizeof(double));
        for(int j = 0; j < m1.num_cols; j++) {
            fscanf(file, "%lf", &m1.data[i][j]);
        }
    }
    return m1;
}
/*
	this function creates the sub-matrix which is key in calculating the result of the determinant
	@m: this is the matrix that we are finding the determinant of

*/
Matrix createSubMatrix(Matrix m, int col) {
    Matrix sub;
    sub.num_rows = m.num_rows - 1;
    sub.num_cols = m.num_cols - 1;
    
    sub.data = malloc(sub.num_rows * sizeof(double*));	// create space for the matrix
    for(int i = 1; i < m.num_rows; i++) {
        sub.data[i-1] = malloc(sub.num_cols * sizeof(double));
        int sub_col_index = 0;
        for(int j = 0; j < m.num_cols; j++) {
            if(j == col) continue;
            sub.data[i-1][sub_col_index] = m.data[i][j]; // this is the step where we are iterating through the matrix and perfoming the determinant calculations ex. (a(ei − fh) − b(di − fg) + c(dh − eg))
            sub_col_index++;
        }
    }
    return sub;
}
// this function frees the space we allocated for the matrix
// @m: this is the matrix we are freeing
void freeMatrix(Matrix m) {
    for (int i = 0; i < m.num_rows; i++) {
        free(m.data[i]);
    }
    free(m.data);
}

// this function prints the matrix after calculating the determinant
// @m: this is the matrix we are printing
void printMatrix(Matrix m) {
    for(int i = 0; i < m.num_rows; i++) {
        for(int j = 0; j < m.num_cols; j++) {
            printf("%.2lf ", m.data[i][j]);
        }
        printf("\n");
    }
}

/*
	this function returns the value of the determinant
	@m: this is the matrix we are finding the determinant of
*/
double calculateMatrix(Matrix m) {
    if (m.num_rows == 2 && m.num_cols == 2) {
        return m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0]; 	// this is the base case where we find the determinant of a 2x2 matrix (ad - cb)
    }
    
    double determinant = 0.0;
    for (int i = 0; i < m.num_cols; i++) {
        Matrix sub = createSubMatrix(m, i);	// create the sub matrix so we can calculate the determinant
        determinant += (i % 2 == 0 ? 1 : -1) * m.data[0][i] * calculateMatrix(sub);	// this is the recursive call to find the determinant
        freeMatrix(sub);
    }
    return determinant;
}