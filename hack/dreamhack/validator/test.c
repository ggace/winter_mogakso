#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* correct= "DREAMHACK!";

int validate(char *s, unsigned int a2)
{
  unsigned int i; // [rsp+1Ch] [rbp-4h]
  signed int j; // [rsp+1Ch] [rbp-4h]

  for ( i = 0; i <= 9; ++i )
  {
    printf("i: %d\n", i);
    if ( s[i] != correct[i] )
      exit(0);
  }
  for ( j = 11; a2 > j; ++j )
  {
    printf("j: %d\n", j);
    printf("%d %d\n", s[j], s[j+1]);
    if ( (unsigned int)s[j] != s[j + 1] + 1 )
      exit(0);
  }
  return 0LL;
}

int main(int argc, const char **argv, const char **envp)
{
  char s[0x80]; // [rsp+0h] [rbp-80h]

  memset(s, 0, 16uLL);
  read(0, s, 1024uLL);
  validate(s, 128uLL);
  return 0;
}

