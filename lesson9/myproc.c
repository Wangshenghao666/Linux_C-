#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int g_unval;
int g_val = 100;

int main(int argc,char* argv[],char* env[])
{
  const char* s = "hello bit";
  printf("code addr:%p\n",main);
  printf("string rdonly addr:%p\n",s);
  printf("init addr:%p\n",&g_val);
  printf("uninit addr:%p\n",&g_unval);


  char* heap = (char*)malloc(10);
  char* heap1 = (char*)malloc(10);
  char* heap2 = (char*)malloc(10);
  char* heap3 = (char*)malloc(10);
  char* heap4 = (char*)malloc(10);


  printf("heap addr:%p\n",heap1);
  printf("heap addr:%p\n",heap2);
  printf("heap addr:%p\n",heap3);
  printf("heap addr:%p\n",heap4);


  printf("stack addr:%p\n",&s);
  printf("stack addr:%p\n",&heap);
  int a = 10;
  int b = 30;
  printf("stack addr:%p\n",&a);
  printf("stack addr:%p\n",&b);

  for(int i = 0; argv[i]; i++)
  {
    printf("argv[%d]:%p\n",i,argv[i]);
  }
  for(int i = 0; env[i]; i++)
  {
    printf("env[%d]:%p\n",i,env[i]);
  }
  return 0;
}

//int g_val = 0;
//  
//int main()
//{ 
//  pid_t id = fork();
//  if(id < 0)
//  {
//    perror("fork");
//    return 0;
//  }
//  else if(id == 0)//child
//  {
//    printf("child[%d]:%d : %p\n",getpid(),g_val,&g_val);
//  }
//  else{
//    //parent
//    printf("parent[%d]:%d : %p\n",getpid(),g_val,&g_val);
//  }
//  sleep(1);
//  
//  return 0;
//} 
////发现：输出的变量值和地址值是一样的，因为子进程按照父进程为模板





//int g_val = 0;
//
//int main()
//{
//  pid_t id = fork();
//  if(id < 0)
//  {
//    perror("fork");
//    return 0;
//  }
//  else if(id == 0)
//  {
//    //子进程先跑，也就是子进程先修改，完成之后，父进程在读取
//    g_val = 100;
//    printf("child[%d]:%d : %p\n",getpid(),g_val,&g_val);
//  }
//  else{
//    printf("parent[%d]:%d : %p\n",getpid(),g_val,&g_val);
//  }
//  sleep(1);
//  return 0;
//}
////发现：地址一样，变量不一样
////结论：
////1.变量内容不一样，所以父子进程输出的变量绝对不一样
////2.地址一样，说明该地址绝对不是物理地址
////3.在Linux下，叫做虚拟地址
////4.我们在用C/C++语言看到的地址，全部都是虚拟地址！而物理地址，用户看不到，有OS同一管理。
