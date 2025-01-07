#include "fdf.h"

int main(int argc, char **argv)
{
    int **matrix;
    int rows, cols;
    int i_row, i_col;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return (1);
    }

    matrix = convert_map_matrix(argv[1]);
    if (!matrix)
    {
        fprintf(stderr, "Error: Failed to convert map to matrix.\n");
        return (1);
    }

    t_r_c dims = num_rows_and_cols(argv[1]);
    rows = dims.rows;
    cols = dims.cols;

    printf("Matrix dimensions: %d rows x %d columns\n", rows, cols);

    for (i_row = 0; i_row < rows; i_row++)
    {
        for (i_col = 0; i_col < cols; i_col++)
        {
            printf("(%d, %d, %d) ", i_row, i_col, matrix[i_row][i_col]);
        }
        printf("\n");
    }

    // Free the matrix
    for (i_row = 0; i_row < rows; i_row++)
        free(matrix[i_row]);
    free(matrix);

    return (0);
}
