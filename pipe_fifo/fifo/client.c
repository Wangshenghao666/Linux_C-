#include"comm.h"
#include<string.h>

int main()
{
  //不需要再创建fifo，只要获取到即可
  int fd = open(MY_FIFO,O_WRONLY);
  if(fd < 0)
  {
    perror("open");
    return 1;
  }
  //业务逻辑
  while(1)
  {
    printf("请输入#");
    fflush(stdout);
    char buffer[64] = {0};
    //先把数据从标准输入拿到我们的client进程内部
    ssize_t s = read(0,buffer,sizeof(buffer)-1);
    if(s>0)
    {
      buffer[s-1] = 0;
      printf("%s\n",buffer);//拿到了数据

      write(fd,buffer,strlen(buffer));//不需要-1，strlen也是文件
    }
  }
  close(fd);
  return 0;
}
