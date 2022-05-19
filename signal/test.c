#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>











////自主实现kill命令
//static void Usage(const char* proc)
//{
//  printf("Usage:\n\t %s signo who\n",proc);
//}
//int main(int argc,char* argv[])
//{
//  if(argc != 3)
//  {
//    Usage(argv[0]);
//    return 1;
//  }
//  
//  int signo = atoi(argv[1]);
//  int who = atoi(argv[2]);
//
//  kill(who,signo);
//  printf("signo:%d,who:%d\n",signo,who);
//  return 0;
//}




//验证core dump选项
int main()
{
  if(fork() == 0)
  {
    while(1)
    {
      printf("I an child...\n");
      int a = 10;
      a /= 0;
    }
  }
  int status = 0;
  waitpid(-1,&status,0);
  printf("exit code:%d,exit sig:%d\n,core dump flag:%d\n",(status >> 8)&0xFF,status&0x7F,(status>>7)&1);
  return 0;
}




////验证信号量的存在
//void handler(int signo)
//{
//  switch(signo)
//  {
//    case 2:
//      printf("hello 222,get a signal:%d\n",signo);
//      break;
//    case 3:
//      printf("hello 333,get a signal:%d\n",signo);
//      break;
//    case 9:
//      printf("hello 999,get a signal:%d\n",signo);
//      break;
//    default:
//      break;
//  }
//  printf("get a signal:%d\n",signo);
//  //exit(-1);
//}
//int main()
//{
//  int sig = 1;
//  for(; sig <= 31; ++sig)
//  {
//    signal(sig,handler);
//  }
//  while(1)
//  {
//    printf("zhangjin shizuinubider\n");
//    sleep(1);
//  }
//  return 0;
//}
//9号信号不可以捕捉




//void handler(int signo)
//{
//  printf("get a signal:singal no:%d,pid:%d\n",signo,getpid());
//}
//int main()
//{
//  //通过signal注册对2号信号的处理动作，改成我们的自定义动作
//  signal(2,handler);
//  //handler注册函数的时候，不是调用这个函数，只有当信号到来的时候，这个函数，才会被调用
//  while(1)
//  {
//    printf("hello world!,pid:%d\n\n",getpid());
//    sleep(1);
//  }
//  return 0;
//}
