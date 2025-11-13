#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory for a matrix
int **allocate_matrix(int size) {
  int **matrix = (int **)malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) {
    matrix[i] = (int *)malloc(size * sizeof(int));
  }
  return matrix;
}

// Function to free memory of a matrix
void free_matrix(int **matrix, int size) {
  for (int i = 0; i < size; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

// Function to add two matrices
void add_matrix(int **A, int **B, int **C, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      C[i][j] = A[i][j] + B[i][j];
    }
  }
}

// Function to subtract two matrices
void subtract_matrix(int **A, int **B, int **C, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      C[i][j] = A[i][j] - B[i][j];
    }
  }
}

// Strassen's matrix multiplication algorithm
void strassen_multiply(int **A, int **B, int **C, int size) {
  if (size == 1) {
    C[0][0] = A[0][0] * B[0][0];
    return;
  }

  int new_size = size / 2;

  int **A11 = allocate_matrix(new_size);
  int **A12 = allocate_matrix(new_size);
  int **A21 = allocate_matrix(new_size);
  int **A22 = allocate_matrix(new_size);
  int **B11 = allocate_matrix(new_size);
  int **B12 = allocate_matrix(new_size);
  int **B21 = allocate_matrix(new_size);
  int **B22 = allocate_matrix(new_size);

  int **M1 = allocate_matrix(new_size);
  int **M2 = allocate_matrix(new_size);
  int **M3 = allocate_matrix(new_size);
  int **M4 = allocate_matrix(new_size);
  int **M5 = allocate_matrix(new_size);
  int **M6 = allocate_matrix(new_size);
  int **M7 = allocate_matrix(new_size);

  int **temp1 = allocate_matrix(new_size);
  int **temp2 = allocate_matrix(new_size);

  for (int i = 0; i < new_size; i++) {
    for (int j = 0; j < new_size; j++) {
      A11[i][j] = A[i][j];
      A12[i][j] = A[i][j + new_size];
      A21[i][j] = A[i + new_size][j];
      A22[i][j] = A[i + new_size][j + new_size];

      B11[i][j] = B[i][j];
      B12[i][j] = B[i][j + new_size];
      B21[i][j] = B[i + new_size][j];
      B22[i][j] = B[i + new_size][j + new_size];
    }
  }

  // M1 = (A11 + A22) × (B11 + B22)
  add_matrix(A11, A22, temp1, new_size);
  add_matrix(B11, B22, temp2, new_size);
  strassen_multiply(temp1, temp2, M1, new_size);

  // M2 = (A21 + A22) × B11
  add_matrix(A21, A22, temp1, new_size);
  strassen_multiply(temp1, B11, M2, new_size);

  // M3 = A11 × (B12 - B22)
  subtract_matrix(B12, B22, temp1, new_size);
  strassen_multiply(A11, temp1, M3, new_size);

  // M4 = A22 × (B21 - B11)
  subtract_matrix(B21, B11, temp1, new_size);
  strassen_multiply(A22, temp1, M4, new_size);

  // M5 = (A11 + A12) × B22
  add_matrix(A11, A12, temp1, new_size);
  strassen_multiply(temp1, B22, M5, new_size);

  // M6 = (A21 - A11) × (B11 + B12)
  subtract_matrix(A21, A11, temp1, new_size);
  add_matrix(B11, B12, temp2, new_size);
  strassen_multiply(temp1, temp2, M6, new_size);

  // M7 = (A12 - A22) × (B21 + B22)
  subtract_matrix(A12, A22, temp1, new_size);
  add_matrix(B21, B22, temp2, new_size);
  strassen_multiply(temp1, temp2, M7, new_size);

  // C11 = M1 + M4 - M5 + M7
  add_matrix(M1, M4, temp1, new_size);
  subtract_matrix(temp1, M5, temp2, new_size);
  add_matrix(temp2, M7, temp1, new_size);
  for (int i = 0; i < new_size; i++) {
    for (int j = 0; j < new_size; j++) {
      C[i][j] = temp1[i][j];
    }
  }

  // C12 = M3 + M5
  add_matrix(M3, M5, temp1, new_size);
  for (int i = 0; i < new_size; i++) {
    for (int j = 0; j < new_size; j++) {
      C[i][j + new_size] = temp1[i][j];
    }
  }

  // C21 = M2 + M4
  add_matrix(M2, M4, temp1, new_size);
  for (int i = 0; i < new_size; i++) {
    for (int j = 0; j < new_size; j++) {
      C[i + new_size][j] = temp1[i][j];
    }
  }

  // C22 = M1 - M2 + M3 + M6
  subtract_matrix(M1, M2, temp1, new_size);
  add_matrix(temp1, M3, temp2, new_size);
  add_matrix(temp2, M6, temp1, new_size);
  for (int i = 0; i < new_size; i++) {
    for (int j = 0; j < new_size; j++) {
      C[i + new_size][j + new_size] = temp1[i][j];
    }
  }

  free_matrix(A11, new_size);
  free_matrix(A12, new_size);
  free_matrix(A21, new_size);
  free_matrix(A22, new_size);
  free_matrix(B11, new_size);
  free_matrix(B12, new_size);
  free_matrix(B21, new_size);
  free_matrix(B22, new_size);
  free_matrix(M1, new_size);
  free_matrix(M2, new_size);
  free_matrix(M3, new_size);
  free_matrix(M4, new_size);
  free_matrix(M5, new_size);
  free_matrix(M6, new_size);
  free_matrix(M7, new_size);
  free_matrix(temp1, new_size);
  free_matrix(temp2, new_size);
}

int main() { return EXIT_SUCCESS; }
