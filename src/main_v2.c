#include "source.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>


int main() {

  char string[]={"This is the ultramegasecret message about my excellent coconut icecream to kill for"};

  char key[]={"HACK"};

  char pad='X';

  char encoded[300];

  char decoded[300];

  encode_string_with_key(string,encoded,key,pad);

  decode_string_with_key(encoded,decoded,key);

  printf("%s\n", string);

  printf("%s\n", encoded);

  printf("%s\n", decoded);

  return 0;
}
