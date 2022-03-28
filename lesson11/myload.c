#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
  //execl("./myexe","./myexe",NULL);
  
  char* env[] = {"MYENV = hahahahahahahahaha","MYENV1 = hahahahahahahahaha","MYENV2 = hahahahahahahaha",NULL};
  char* argv[] = {"myexe",NULL};
  execve("./myexe",argv,env);
 // execle("./myexe","myexe",NULL,env);





//  //2.exev
//  if(fork() == 0)
//  {
//    printf("command begin..\n");
//    char* argv[] = {"ls","-a","-l","-i","-n",NULL};
//   // execv("/usr/bin/ls",argv);
//   //3.execlp
//   //execlp("ls","ls","-a","l","-d",NULL);
//   //4.execvp
//   //execvp("ls",argv);
//   
//    printf("command end..!\n");
//
//    exit(1);
//  }
//  waitpid(-1,NULL,0);
//  printf("wait child success!\n");









  ////1.execl
  //if(fork() == 0)
  //{
  //  //child
  //  execl("/usr/bin/ls","ls","-a","-l","-n","-i",NULL);
  //  exit(-1);
  //}
  ////parent
  //waitpid(-1,NULL,0);
  //printf("wait success\n");






  //pid_t id = fork();
  //if(id == 0)
  //{
  //  printf("I am a process! pid:%d\n",getpid());
  //  execl("/usr/bin/ls","ls","-a","-l",NULL);
  //  printf("zhangjin\n");
  //  printf("zhangjin\n");
  //  printf("zhangjin\n");
  //  printf("zhangjin\n");
  //  exit(0);
  //}
  //while(1)
  //{
  //  printf("I am a father!\n");
  //  sleep(1);
  //}
  //waitpid(id,NULL,0);
  //printf("wait success!\n");
  ////进程具有独立性，进程程序替换会更改代码区的代码，发生写时拷贝
  ////只要进程的程序替换成功，就不会执行后续代码，意味着exec*函数成功的时候，不需要返回值检测，只要exec返回了，就一定是因为调用失败









  //printf("I am a process!pid:%d\n",getpid());
  //execl("/usr/bin/ls","ls","-a","-l",NULL);
  ////execl执行程序替换 ， 执行后，打印 ls -a -l 的内容，不打印zhangjin，就是替换
  //printf("zhangjin\n");
  //printf("zhangjin\n");
  //printf("zhangjin\n");
  //printf("zhangjin\n");
  return 0;
}
