#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

//操作系统提供一个接口：pipe(管道 <unistd.h>)
//int pipe(int pipefd[2]);
//pipefd[2]是一个输出型参数，我们想通过这个参数读取到打开的两个fd

int main()
{
  int pipefd[2] = {0};
  if(pipe(pipefd) != 0)
  {
    perror("pipe error");
    return 1;
  }
  printf("pipefd[0]:%d\n",pipefd[0]);//3
  printf("pipefd[1]:%d\n",pipefd[1]);//4
  //pipefd[0]:读端         pipefd[1]:写端
  //我们想让父进程进行读取，子进程进行写入
  if(fork() == 0)
  {
    //child
    close(pipefd[0]);
   // const char* msg = "hello wsh!\n";
    int count = 0;
    while(1)
    {
     // write(pipefd[1],msg,strlen(msg));//strlen(msg)+1吗？不需要
      write(pipefd[1],"a",1);
      count++;
      printf("count:%d\n",count);
     // sleep(1);
    }
    exit(0);
  }
  //会写满64kb的时候，write就不写了，管道有大小，等对方来读

  //parent
  close(pipefd[1]);
  while(1)
  {
  //  char buffter[64] = {0};
  //  ssize_t s = read(pipefd[0],buffter,sizeof(buffter)-1);
  //  if(s == 0)
  //  {
  //    break;
  //  }
  //  else if(s > 0)
  //  {
  //    buffter[s] = 0;
  //    printf("child say to father#:%s\n",buffter);
  //  }
  //  else 
  //  {
  //    break;
   

   char c[1024*4+1] = {0};
   ssize_t s = read(pipefd[0],c,sizeof(c));
   c[s] = 0;
   printf("father take:%c\n",c[0]);
   sleep(1);
   }
  return 0;
}
//得出5个特点：
//1.管道是一个只能单向通信的信道
//2.管道是面向字节流的
//3.仅限于父子通信--具有血缘关系的进程，进行进程间通信
//4.管道自带同步机制（原子性写入）
//5.管道的生命周期是随进程的
