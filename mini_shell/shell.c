#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

#define NUM 128
#define CMD_NUM 64

int main()
{
  char command[NUM];
  for(; ;)
  {
    char *argv[CMD_NUM] = { NULL };
    //1.打印提示符
    command[0] = 0;//用这种方法，可以做到o(1)的时间复杂度，清空字符串
    printf("[who@myhostname mydir]# ");
    fflush(stdout);
    
    //2.获取命令字符串
    fgets(command,NUM,stdin);//输入的字符串读入
    command[strlen(command) - 1] = '\0';//这呀\n就不会换行了 eg:ls\n\0
    //printf("echo:%s\n",command);//显示命令行参数
    
    //3.解析命令字符串，char *argv[]; eg:ls -a -l -n 把他们分割出来
    //用strtok来分割
    const char* seq = " ";
    argv[0] = strtok(command,seq);
    int i = 1;
    while(argv[i] = strtok(NULL,seq))
    {
      ++i;
    }
    //4.检测命令是否需要本身shell执行（内建命令）
    if(strcmp(argv[0],"cd") == 0)
    {
      if(argv[1] != NULL)
      {
        chdir(argv[1]);
      }
      continue;
    }
    //for(i = 0; argv[i]; ++i)
    //{
    //  printf("argv[%d]:%s\n",i,argv[i]);
    //}
    //5.执行第三方命令
    if(fork() == 0)
    {
      //child
      execvp(argv[0],argv);
      exit(-1);
    }
    waitpid(-1,NULL,0);

  }

  return 0;
}
