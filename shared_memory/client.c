#include"comm.h"

int main()
{
  key_t key = ftok(PATH_NAME,PROJ_ID);
  if(key < 0)
  {
    perror("ftok");
    return 1;
  }
  printf("%u\n",key);

  return 0;
}
