#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void coo2csc(const uint *row_coo, const uint *col_coo, uint *row, uint *col,
             const uint nnz, const uint rows, const uint cols, bool isOneBase) {
  uint n = cols;

  // ----- find the correct column sizes
  for (uint l = 0; l < nnz; l++) {
    if (isOneBase) {
      col[col_coo[l] - 1]++;
    } else {
      col[col_coo[l]]++;
    }
  }
  // ----- cumulative sum
  for (uint i = 0, cumsum = 0; i < n; i++) {
    uint temp = col[i];
    col[i] = cumsum;
    cumsum += temp;
  }
  col[n] = nnz;
  // ----- copy the row indices to the correct place
  for (uint l = 0; l < nnz; l++) {
    uint col_l;
    if (isOneBase) {
      col_l = col_coo[l] - 1;
    } else {
      col_l = col_coo[l];
    }

    uint dst = col[col_l];
    if (isOneBase) {
      row[dst] = row_coo[l] - 1;
    } else {
      row[dst] = row_coo[l];
    }

    col[col_l]++;
  }
  // ----- revert the column pointers
  for (uint i = 0, last = 0; i < n; i++) {
    uint temp = col[i];
    col[i] = last;
    last = temp;
  }
  // Debugging
  printf("Columns\n");
  for (int i = 0; i < cols+1; i++) {
    printf("%i\n", col[i]);
  }
  printf("Rows\n");
  for (uint i = 0; i < nnz ; i++) {
    printf("%i\n", row[i]);
  }
}

int main() {

  //const uint nnz = 8;  // number of non-zero elements
  const uint nnz = 7;
  //const uint rows = 4; // number of matrix rows
  const uint rows = 5; // number of matrix rows

  //const uint cols = 6; // number of matrix columns

  const uint cols = 5; // number of matrix columns

  uint *coo_row, *coo_col, *csr_row, *csr_col, *csc_col, *csc_row;
  double *coo_val;

  coo_row = (uint *)malloc(nnz * sizeof(uint));
  coo_col = (uint *)malloc(nnz * sizeof(uint));
  coo_val = (double *)malloc(nnz * sizeof(double));

  csr_row = (uint *)malloc((rows + 1) * sizeof(uint));
  csr_col = (uint *)malloc(nnz * sizeof(uint));

  csc_row = (uint *)malloc(nnz * sizeof(uint));
  csc_col = (uint *)malloc(cols+1 * sizeof(uint));


  // Example from Wikipedia (https://en.wikipedia.org/wiki/Sparse_matrix)

  // Matrix:
  // 10 20  0  0  0  0
  //  0 30  0 40  0  0
  //  0  0 50 60 70  0
  //  0  0  0  0  0 80



  // Expected output:
  // csr_val: 10 20 30 40 50 60 70 80
  // csr_col:  0  1  1  3  2  3  4  5
  // csr_row:  0  2  4  7  8

  // create the example simple Matrix in 1-index



   // 0 0 0 2 0 
  //  1 0 0 0 0  
  //  0 0 1 0 0
  //  0 0 2 1 2

  bool isOneBase = false;

/*
  coo_val[1] = 10.0;
  coo_val[2] = 20.0;
  coo_val[3] = 30.0;
  coo_val[4] = 40.0;
  coo_val[5] = 50.0;
  coo_val[6] = 60.0;
  coo_val[7] = 70.0;
  coo_val[8] = 80.0;
  coo_row[1] = 0;
  coo_row[2] = 0;
  coo_row[3] = 1;
  coo_row[4] = 1;
  coo_row[5] = 2;
  coo_row[6] = 2;
  coo_row[7] = 2;
  coo_row[8] = 3;

  coo_col[1] = 0;
  coo_col[2] = 1;
  coo_col[3] = 1;
  coo_col[4] = 3;
  coo_col[5] = 2;
  coo_col[6] = 3;
  coo_col[7] = 4;
  coo_col[8] = 5;
*/

//A.data = [2, 1, 1, 2, 2, 1, 2]
//A.row =  [0, 1, 2, 3, 4, 4, 4]
//A.col =  [3, 0, 2, 1, 2, 3, 4]

  coo_val[0] = 2;
  coo_val[1] = 1;
  coo_val[2] = 1;
  coo_val[3] = 2;
  coo_val[4] = 2;
  coo_val[5] = 1;
  coo_val[6] = 2;
  coo_row[0] = 0;
  coo_row[1] = 1;
  coo_row[2] = 2;
  coo_row[3] = 3;
  coo_row[4] = 4;
  coo_row[5] = 4;
  coo_row[6] = 4;
  coo_col[0] = 3; 
  coo_col[1] = 0;
  coo_col[2] = 2;
  coo_col[3] = 1;
  coo_col[4] = 2;
  coo_col[5] = 3;
  coo_col[6] = 4;




  // Call coo2csc for isOneBase false
  coo2csc(coo_row, coo_col, &csc_row[0], &csc_col[0], nnz, rows, cols,
          isOneBase);
}
