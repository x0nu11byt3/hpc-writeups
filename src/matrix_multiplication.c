#include "matrix_multiplication.h"

void file_read(void) {
    
    char line[MAX_CHARS];
    FILE *file = NULL;
    file = fopen("matrix_a.txt","r+");
    
    if ( file == NULL) {
        printf("Error, Can't open file\n");
        return exit(-1);
    }

    while ( fgets ( line, sizeof(line), file ) != NULL ) 
        fputs ( line, stdout ); 
    fclose ( file );
}


void get_data_row (char *string,long long *data) {
    char *token = strtok(string, " ");
    int i = 0;
    while (token != NULL){        
        long long number = 0;
        sscanf(token, "%d", &number);
        data[i] = number;    
        i++;
        token = strtok(NULL, " ");
    }        
}

void extract_matrix_file(long long matrix[MATRIX_SIZE][MATRIX_SIZE], char *filename,int rows, int columns ) {
    
    char line[MAX_CHARS];
    char character[MAX_CHARS];
    FILE *file = NULL;
    
    file = fopen(filename,"r+");
    
    if ( file == NULL)
        printf("Error, Can't open file\n");
    
    int i = 0;
    while ( fgets ( line, sizeof(line), file ) != NULL ) {
        long long dataline[columns];
        get_data_row (line,dataline);
        
        for (int j = 0; j < columns; j++){
            printf(" %d ", dataline[j]);
            matrix[i][j] = dataline[j];
        }
            
        printf("\n");
        i++;
    }
    fclose ( file );
}

void multiplication_matrix(long long matrix_a[MATRIX_SIZE][MATRIX_SIZE], long long matrix_b[MATRIX_SIZE][MATRIX_SIZE]) {
    // result_matrix[AMOUNT_ROWS][AMOUNT_COLUMNS]
    long long result_matrix[MATRIX_SIZE][MATRIX_SIZE];
    // MATRIX_SIZE -> amount rows first matrix 
    for (int i = 0; i < MATRIX_SIZE; i++) {        
        // MATRIX_SIZE -> amount columns second matrix
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result_matrix[i][j] = 0;
            // MATRIX_SIZE -> amount rows second matrix
            for ( int k = 0; k < MATRIX_SIZE; k++ ) 
                result_matrix[i][j] += matrix_a[i][k] * matrix_b[k][j];
            printf("\t%d", result_matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv){
   
    // means of argv index 
    // 0 -> name exe
    // 1 -> first matrix filename
    // 2 -> second matrix filename
    // 3 -> rows matrix a 
    // 4 -> columns matrix a
    // 5 -> rows matrix b
    // 6 -> columns matrix b
    long long matrix_a[atoi(argv[3])][atoi(argv[4])];
    long long matrix_b[atoi(argv[5])][atoi(argv[6])];
    printf("First matrix\n");
    extract_matrix_file(matrix_a,argv[1],atoi(argv[3]),atoi(argv[4]));
    printf("Second Matrix\n");
    extract_matrix_file(matrix_b,argv[2],atoi(argv[5]),atoi(argv[6]));
    printf("Result Matrix\n");
    multiplication_matrix(matrix_a,matrix_b);
  
    
    return 0;
}
