#include <stdio.h>
#include <stdlib.h> 

// matrix struct with 2 dimensions
typedef struct {
    int num_rows;
    int num_cols;
    double **data;   
} Matrix;

Matrix createMatrix(FILE* file)
{
    Matrix m1;
    fscanf(file, "%d %d", &m1.num_rows, &m1.num_cols);

    m1.data = malloc(m1.num_rows * sizeof(double*));

    for(int i = 0; i < m1.num_rows; i++)  
    {
        m1.data[i] = malloc(m1.num_cols * sizeof(double));  
        for(int j = 0; j < m1.num_cols; j++)
        {
            fscanf(file, "%lf", &m1.data[i][j]);    
        }
    }
    return m1;
}

Matrix createSubMatrix(Matrix m, int col)
{
    Matrix sub;
    sub.num_rows = m.num_rows - 1;  
    sub.num_cols = m.num_cols - 1;  
    
    sub.data = malloc(sub.num_rows * sizeof(double*));
    
    
    for(int i = 1; i < m.num_rows; i++) {
        sub.data[i-1] = malloc(sub.num_cols * sizeof(double));
        
        int sub_col_index = 0;
        for(int j = 0; j < m.num_cols; j++) {
           
            if(j == col) {
                continue;
            }
            sub.data[i-1][sub_col_index] = m.data[i][j];
            sub_col_index++;
        }
    }

    return sub;
}

void freeMatrix(Matrix m) {
    for (int i = 0; i < m.num_rows; i++) {
        free(m.data[i]);
    }
    free(m.data);
}

void printMatrix(Matrix m) {
    for(int i = 0; i < m.num_rows; i++) {
        for(int j = 0; j < m.num_cols; j++) {
            printf("%.2lf ", m.data[i][j]);
        }
        printf("\n");
    }
}

double calculateMatrix(Matrix m)
{
    if (m.num_cols == 2 && m.num_rows == 2)
    {
        return m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0]; // this is the base case calculation of a 2x2 matrix
    }
    
    double determinant = 0.0;  // Fixed: initialize determinant to 0
    
    for (int i = 0; i < m.num_cols; i++)
    {
        Matrix sub = createSubMatrix(m, i);
        //even index is plus and single index is minus 
        if(i % 2 == 0) {
            determinant = determinant + m.data[0][i] * calculateMatrix(sub);
        } else {
            determinant = determinant - m.data[0][i] * calculateMatrix(sub);
        }
        freeMatrix(sub);
    }
    return determinant;
}

int main(int argc, char* argv[])
{
    char* filepath = argv[1];
    FILE* fp = fopen(filepath, "r");
    Matrix m = createMatrix(fp);
    fclose(fp);

    double d = calculateMatrix(m);
    printf("The determinant is %.2lf.", d);
    
    freeMatrix(m);  // Free matrix memory before exit

    return 0;
}