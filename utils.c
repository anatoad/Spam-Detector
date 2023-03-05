#include "./utils.h"

/* Dynamically allocate memory for a matrix of size rows x columns. */
void **calloc_matrix(int rows, int columns, size_t size)
{
	void **mat = calloc(rows, sizeof(void *));
	if (!mat) {
		printf("Allocation of matrix has failed.\n");
		return NULL;
	}

	for (int i = 0; i < rows; i++) {
		mat[i] = calloc(columns, size);
		if (!mat[i]) {
			printf("Allocation of mat[%d] has failed.\n", i);
			for (int j = 0; j < i; j++)
				free(mat[j]);

			free(mat);
			return NULL;
		}
	}

	return mat;
}

/* Free matrix memory. */
void free_matrix(void **matrix, int rows, size_t size)
{
	if (!matrix)
		return;

	if (size == sizeof(int)) {
		for (int i = 0; i < rows; i++)
			free(((int **)matrix)[i]);
	}

	if (size == sizeof(char)) {
		for (int i = 0; i < rows; i++)
			free(((char **)matrix)[i]);
	}

	free(matrix);
}
