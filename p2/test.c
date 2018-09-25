#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char** argv){
  char c;
  FILE* fp = fopen( argv[1], "r" );
  if( argc == 1 ) {
    printf("usage: ./test <filename>\n");
    return -1;
  }

  if(fp==NULL) {
    printf("cannot open: \"%s\"\n", argv[1]);
    return -1;
  }
  do {
    c = fgetc(fp);
    if(!isprint(c)) {
      if( c == '\n' )
        printf("0x\'%X\'%c", c, c);
      else if( c == EOF ) {
        printf("EOF = %d\n", c);
      }
      else
        printf("\'0x%X\'", c);
    }
    else
      putchar(c);
  }while(c != EOF);
  return 0;
}
