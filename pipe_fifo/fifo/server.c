#include"comm.h"





int main()
{
  umask(0);//权限清空
  if(mkfifo(MY_FIFO,0666) < 0)
  {
    perror("mkfifo");
    return 1;
  }
//文件操作
  int fd = open(MY_FIFO,O_RDONLY);
  {
    if(fd < 0)
    {
      perror("open");
      return 2;
    }
    //业务逻辑，可以进行相应的读写
    while(1)
    {
      char buffer[64] = {0};
      ssize_t s = read(fd,buffer,sizeof(buffer)-1);
      if(s > 0)
      {
        buffer[s] = 0;
        printf("client#:%s\n",buffer);
      }
      else if(s == 0)
      {
        printf("client quie ...\n");
        break;
      }
      else 
      {
        perror("read");
        break;
      }
    }
  }
  close(fd);
  return 0;
}
