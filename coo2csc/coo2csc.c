/**
 *   \file coo2csc.c
 *   \brief An example of COO to CSC matrix conversion
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*****************************************************************************/
/*                             routine definition                            */
/*****************************************************************************/

/**
 *  \brief COO to CSC conversion
 *
 *  Converts a square matrix from COO to CSC format.
 *
 *  Note: The routine assumes the input COO and the output CSC matrix
 *  to be square.
 *
 */
void coo2csc(
  uint32_t       * const row,       /*!< CSC row start indices */
  uint32_t       * const col,       /*!< CSC column indices */
  uint32_t const * const row_coo,   /*!< COO row indices */
  uint32_t const * const col_coo,   /*!< COO column indices */
  uint32_t const         nnz,       /*!< Number of nonzero elements */
  uint32_t const         n,         /*!< Number of rows/columns */
  uint32_t const         isOneBased /*!< Whether COO is 0- or 1-based */
) {

  // ----- cannot assume that input is already 0!
  for (uint32_t l = 0; l < n+1; l++) col[l] = 0;


  // ----- find the correct column sizes
  for (uint32_t l = 0; l < nnz; l++)
    col[col_coo[l] - isOneBased]++;

  // ----- cumulative sum
  for (uint32_t i = 0, cumsum = 0; i < n; i++) {
    uint32_t temp = col[i];
    col[i] = cumsum;
    cumsum += temp;
  }
  col[n] = nnz;
  // ----- copy the row indices to the correct place
  for (uint32_t l = 0; l < nnz; l++) {
    uint32_t col_l;
    col_l = col_coo[l] - isOneBased;

    uint32_t dst = col[col_l];
    row[dst] = row_coo[l] - isOneBased;

    col[col_l]++;
  }
  // ----- revert the column pointers
  for (uint32_t i = 0, last = 0; i < n; i++) {
    uint32_t temp = col[i];
    col[i] = last;
    last = temp;
  }

}

/*****************************************************************************/
/*                 setup example and assert correct behavior                 */
/*****************************************************************************/

int main() {

  const uint32_t nnz = 7;
  const uint32_t n   = 5;

  uint32_t * csc_row = (uint32_t *)malloc(nnz     * sizeof(uint32_t));
  uint32_t * csc_col = (uint32_t *)malloc((n + 1) * sizeof(uint32_t));

  // Example from
  // https://medium.com/swlh/an-in-depth-introduction-to-sparse-matrix-a5972d7e8c86

  uint32_t coo_row[7] = {1,2,3,4,5,5,5};
  uint32_t coo_col[7] = {4,1,3,2,3,4,5};
  uint32_t isOneBased = 1;

  uint32_t csc_col_gold[6] = {0,1,2,4,6,7};
  uint32_t csc_row_gold[7] = {1,3,2,4,0,4,4};

  // Call coo2csc for isOneBase false
  coo2csc(csc_row, csc_col,
          coo_row, coo_col,
          nnz, n,
          isOneBased);

  // Verify output
  uint32_t pass = 1;
  for (int i = 0; i < n + 1; i++) {
    printf("%d ", csc_col[i]);
    pass &= (csc_col[i] == csc_col_gold[i]);
  }
  printf("\n");
  for (uint32_t i = 0; i < nnz; i++) {
    printf("%d ", csc_row[i]);
    pass &= (csc_row[i] == csc_row_gold[i]);
  }
  printf("\n");
  if (pass) printf("Tests: PASSed\n");
  else      printf("Tests: FAILed\n");

  /* cleanup variables */
  free( csc_row );
  free( csc_col );


}
