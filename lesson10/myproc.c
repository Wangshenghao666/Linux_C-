#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
  //轮询等待：
  pid_t id = fork();
  if(id == 0)
  {
    int cnt =10;
    while(cnt)
    {
      printf("child[%d] is running cnt is:%d\n",getpid(),cnt);
      cnt--;
      sleep(1);
    }
    exit(1);
  }
  int status = 0;
  while(1)
  {
    pid_t ret = waitpid(id,&status,WNOHANG);
    if(ret == 0)
    {
      //子进程没有退出，但是waitpid等待是成功的，需要父进程重复进行等待
      printf("Do father things!\n");
    }
    else if(ret > 0)
    {
      //子进程退出了，waitpid也成功了，获取了对应的结果
      printf("father wait:%d,success,status exit code:%d,status exit signal:%d\n",ret,(status<<8) & 0xff,status & 0x7f);
      break;
    }
    else{
      //失败ret<0
      perror("waitpid");
      break;
    }
    sleep(1);
  }
  


  //pid_t id = fork();
  //if(id == 0)
  //{
  //  //child
  //  int cnt = 3;
  //  while(cnt)
  //  {
  //    printf("child[%d] is running:cnt is:%d\n",getpid(),cnt);
  //    cnt--;
  //    sleep(1);
  //  }
  //  exit(1);
  //}
  //int status = 0;
  //pid_t ret = waitpid(id,&status,0);
  //if(ret>0)
  //{
  //  if(WIFEXITED(status))//没有收到任何退出信号
  //  {
  //    printf("exit code:%d\n",WEXITSTATUS(status));//正常结束的获取退出码
  //  }
  //  else{
  //    printf("error,get a signal!\n");
  //  }
  //}
  





 // printf("father wait begin!\n");
 // int status = 0;
 // pid_t ret = waitpid(id,&status,0);
 // if(ret > 0)
 // {
 //   printf("father wait:%d,status exit code:%d,status exit signal:%d\n",ret,(status>>8) & 0xff,status&0x7f);
 // }
 // else{
 //   printf("father wait failed\n");
 // }
//父进程拿到什么status的结果，一定和子进程如何退出强相关
//最终一定要让父进程通过status得到子进程执行结果








  //查看错误码
  //for(int i = 0; i < 140; ++i)
  //{
  //  printf("%d:%s\n",i,strerror(i));
  //}
  //退出
 // printf("hello world!");
 // sleep(4);
 // exit(EXIT_SUCCESS);
  

 // pid_t id = fork();
 // if(id == 0)
 // {
 //   //child
 //   int cnt = 5;
 //   while(cnt)
 //   {
 //     printf("child[%d] is running cnt is : %d\n",getpid(),cnt);
 //     cnt--;
 //     sleep(1);
 //   }
 //   exit(0);
 // }
 // sleep(10);
 // printf("father wait begin!\n");
 // pid_t ret = wait(NULL);//等待指定一个进程
 // pid_t ret = waitpid(id,NULL,0);
 // pid_t ret = waitpid(-1,NULL,0);//等待任意一个进程
 // if(ret > 0)
 // {
 //   printf("father wait:%d,success\n",ret);
 // }
 // else{
 //   printf("father wait failed\n");
 // }
 // sleep(10);
  return 0;
}
