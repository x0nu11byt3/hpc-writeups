
#ifndef _MATRIX_MULTIPLICATION_H
#define _MATRIX_MULTIPLICATION_H

#define __PROGRAM_NAME__ "matrix"
#define __PROGRAM_VERSION__ "1.0.0"

#define MAX_CHARS 100
#define MATRIX_SIZE 5

//#define MATRIX_SIZE 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
    
void file_read(void);
void extract_matrix_file(long long matrix[MATRIX_SIZE][MATRIX_SIZE], char *filename,int rows, int columns );
void get_data_row (char *string,long long *data);
void multiplication_matrix(long long matrix_a[MATRIX_SIZE][MATRIX_SIZE], long long matrix_b[MATRIX_SIZE][MATRIX_SIZE]);

#endif  /* !_MATRIX_MULTIPLICATION_H */
