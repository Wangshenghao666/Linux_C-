#include<stdio.h>
int main()
{
  //printf("hahahahahahahaha,I am you exe!\n");
  extern char** environ;
  for(int i = 0; environ[i]; i++)
  {
    printf("%s\n",environ[i]);
  }
  printf("my exe runing ---- done\n");
  return 0;
}
