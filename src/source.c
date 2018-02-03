#include "source.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>




int encode_string(char* source, char* dest, int col_count, char pad) {
  int k=0, row_count=0;
  char **matrix1=NULL;


  row_count=rows(source,col_count);

  if ((matrix1=sort_into_matrix(col_count,row_count,source,pad))==0) {
    return -1;
  }

  //now encrypt!
  for (int i=0;i<col_count;i++) {
    for (int j=0;j<row_count;j++) {
      dest[k]=matrix1[j][i];
      k++;
    }
  }
  dest[k]='\0';


return strlen(dest);
}


int decode_string(char* source, char* dest, int col_count) {
  int row_count=0,k=0;
  char **matrix=NULL;

  row_count=rows(source,col_count);
  if ((matrix=sort_into_matrix_p2(col_count,row_count,source))==0) {
    return -1;
  }

  //now decrypt!

  for (int i=0;i<row_count;i++) {
    for (int j=0;j<col_count;j++) {
      dest[k]=matrix[i][j];
      k++;
    }
  }
  dest[k]='\0';

return strlen(dest);
}

int encode_string_with_key(char* source, char* dest, char* key, char pad) {
  int *key_order=order_alfa(key);
  int cols=strlen(key),k=0;
  char temp[cols];
  int row_count=rows(source, cols)+1;
  char **matrix=put_into_grid(source, pad, key_order,cols,row_count);

  if (matrix==NULL) return -1;

  for (int a=0;a<cols;a++) {
    temp[a]=matrix[0][a];
  }

  //this might not work!!
  for (int i=1; i<=cols;i++) {
    int index=strchr(temp,(char)i)-temp;  //this returns the right indexes. i think
    // printf("%d\n", index );
    //above might return some shit so change if needed
    for (int j=1;j<row_count;j++) {
      dest[k]=matrix[j][index];
      k++;
    }
  }

  dest[k]='\0';


return strlen(dest);
}


int decode_string_with_key(char* source, char* dest, char* key) {
  //key lenght (cols) and rows
  int x=0;
  int col_count=strlen(key);
  int row_count=rows(source,col_count)+1;

  //key order
  int *ko=order_alfa(key);

  //sort into a matrix. again

  char **matrix=put_into_grid2(source,col_count,row_count);

  if (matrix==NULL) {
    fprintf(stderr, "%s\n", "error in putting string to matrix");
    return -1;
  }

  // for (int i=0;i<row_count;i++) {
  //   for (int j=0;j<col_count;j++) {
  //     printf("%d ",matrix[i][j] );
  //   }
  //   printf("\n");
  // }

  //read to dest

  for (int i=1; i<row_count; i++) {
    for (int j=0; j<col_count;j++) {
      int index=0;
      for (int k=0; k<col_count;k++) {
        if ((char)(ko[j])==matrix[0][k]) {
          index=k;
        }
        // printf("%d\n",index );
      }
      dest[x]=matrix[i][index];
      x++;
    }
  }

  // printf("%d\n",x);

  dest[x]='\0';

  return strlen(dest);
}

char ** sort_into_matrix(int cols, int rows, char *source, char pad) {
  // char (*matrix)[cols]=malloc(rows*sizeof(*matrix));
  char **matrix=malloc(sizeof(char*)*rows);
  for (int m=0;m<rows;m++) {
    matrix[m]=malloc(sizeof(char)*cols);
  }


  if (matrix==NULL) return 0;

  int k=0;

  for (int i=0;i<rows;i++) {
    for (int j=0;j<cols;j++) {
      if (k<strlen(source)) {
        matrix[i][j]=source[k];
        k++;
      } else {
        matrix[i][j]=pad;
      }
    }
  }

  return matrix;
}

char ** sort_into_matrix_p2(int cols, int rows, char *source) {
  int k=0;

  char **matrix=malloc(sizeof(char*)*rows);
  for (int m=0;m<rows;m++) {
    matrix[m]=malloc(sizeof(char)*cols);
  }

  if (matrix==NULL) return NULL;

  for (int i=0;i<cols;i++) {
    for (int j=0;j<rows;j++) {
      matrix[j][i]=source[k];
      k++;
    }
  }
  return matrix;
}

int rows(char *source, int cols) {
  return strlen(source)/cols+(strlen(source) % cols != 0);
}

int *order_alfa(char *key) {
  int len=strlen(key),x=1;
  int *order=malloc(len*sizeof(int));
  char mini='0';

  while(x<=strlen(key)) {
    mini=min(key,mini);
    for (int i=0;i<len;i++) {
      if (key[i]==mini) {
        order[i]=x;
        x++;
      }
      // mini++;
    }
    mini++;

  }

  return order;
}

char min(char *string, char a) {
  char min=CHAR_MAX;
  for (int i=0; i < strlen(string); i++) {
    if (string[i]<min && string[i]>=a) {
      min=string[i];
    }
  }
  return min;
}

char **put_into_grid(char *source,char pad, int *key_order, int cols,int row_count) {

  char **matrix=malloc(sizeof(char*)*row_count);

  for (int m=0;m<row_count;m++) {
    matrix[m]=malloc(sizeof(char)*cols);
  }


  if (matrix==NULL) return NULL;

  int k=0,l=0;

  for (int i=0;i<row_count;i++) {
    for (int j=0;j<cols;j++) {
      if (k<cols) {
        matrix[i][j]=(char)key_order[k];
        k++;
      } else if (l<strlen(source)) {
        matrix[i][j]=source[l];
        l++;
      } else {
        matrix[i][j]=pad;
      }
    }
  }

  return matrix;

}

char **put_into_grid2(char *source, int cols, int rows) {
  int k=0;
  //create the matrix.
  char **matrix=malloc(sizeof(char*)*rows);

  for (int m=0;m<rows;m++) {
    matrix[m]=malloc(sizeof(char)*cols);
  }


  if (matrix==NULL) return NULL;

  for (int j=0;j<cols;j++) {
    for (int i=0; i<rows;i++) {
      if (i==0) {
        matrix[i][j]=(char)(j+1);
      } else {
        matrix[i][j]=source[k];
        // printf("%c\n",source[k]);
        k++;
      }
    }
  }



  return matrix;
}
