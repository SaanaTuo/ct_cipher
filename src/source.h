/*Header file for columnar transpostion cipher*/



/* create_encode_matrix:
 * Allocates space for the encoding matrix and places the ALPHANUMERIC characters of the string to the matrix
 * arguments:   string - plain text string to be ciphered
                rows and columns define the structure of the matrix
                pad contains the padding character that is used to fill up the encryption matrix
 * returns: pointer to the cipher matrix
 */
//char* create_encode_matrix(char* string, int rows, int columns, char pad);

/* create_decode_matrix:
 * Allocates space for the decoding matrix and places the ALPHANUMERIC characters of the string to the matrix
 * arguments:   string - plain text string to be ciphered
                rows and columns define the structure of the matrix
 * returns: pointer to the cipher matrix (formed for decoding)
 */
//char* create_decode_matrix(char* string, int rows, int columns);


/* encode_string
 * Encode the plain text source to the ciphered destination using matrix size defined with col_count
 * arguments: source - plain text string to be encoded
              dest - pointer to allocated area for the ciphered string
              col_count - defines the matrix size as number of columns.
              pad - contains the padding character needed by the matrix
 * returns the ciphered string in dest and the lenght of it as the return value of the function
 * NOTE: Number of rows depends on the length of the string
 */
int encode_string(char* source, char* dest, int col_count, char pad);


/* decode_string
 * Decode the ciphered source to the plain text destination using matrix size defined with col_count
 * arguments: source - ciphered text string to be decoded
              dest - pointer to allocated area for the plain text string
              col_count - defines the matrix size as number of columns.
 * returns the plain text string in dest and the lenght of it as the return value of the function
 * NOTE: Number of rows depends on the length of the string
 */
int decode_string(char* source, char* dest, int col_count);

/* encode-string_with_key
 * Similar tha encode_string, but the size of matrix and the order of columns in the ciphered string is determined with a key string
 * number of columns equals the length of the string
 * Order of columns equals the alphabetical order of the characters in the key (if identical, then the earlier one is earlier)
 */
int encode_string_with_key(char* source, char* dest, char* key, char pad);

/* decode_string_with_key
 * And finally the last decode to match with the encode_string_with_key
 */
int decode_string_with_key(char* source, char* dest, char* key);

//calculates the rows needed for the marix
int rows(char *source, int cols);

//sorts into matrix when encoding without key
char **sort_into_matrix(int cols, int rows, char *source, char pad);

//sorts into matrix when decoding without key
char **sort_into_matrix_p2(int cols, int rows, char *source);

//orders the key: 'key'->213
int *order_alfa(char *key);

//returns the smallest character from string that is same or bigger as char
char min(char *string, char a);

char **put_into_grid(char *source, char pad, int *key_order, int cols,int row_count );

char **put_into_grid2(char *source, int cols, int rows);
