#include<stdio.h>
#include<string.h>
#include<unistd.h>
int main()
{
#define NUM 100
  char bar[NUM+1];
  memset(bar,'\0',sizeof(bar));
  const char* lable = "|/-\\";
  int i = 0;
  while(i <= 100)
  {
    printf("\033[31m[%-100s][%3d%%][%c]\r",bar,i,lable[i%4]);
    fflush(stdout);
    bar[i] = '#';
    bar[i+1] = '>';
    i++;
    usleep(50000);
  }
  printf("\n");
  return 0;
}
