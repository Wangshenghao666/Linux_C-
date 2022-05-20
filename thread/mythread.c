#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define NUM 1

void* thread_run(void* args)
{
  int num = *(int*)args;
  while(1)
  {
    printf("我是新线程 %d ,我们创建的线程id是：%lu\n",num,pthread_self());
    sleep(10);
    break;
  }
  return (void*)111;
}
int main()
{
  pthread_t tid[NUM];
  for(int i = 0; i < NUM; i++)
  {
    pthread_create(tid+i,NULL,thread_run,(void*)&i);
    sleep(1);
  }
  //void* 32/4 64/8 指针变量，本身就可以充当某种容器保存数据.
  void* status = NULL;

  pthread_join(tid[0],&status);
  printf("ret:%d\n",status);
  return 0;
}











//创建一批线程
void* thread_run(void* args)
{
  while(1)
  {
    sleep(3);
  }
}
int main()
{
  pthread_t tid[5];
  for(int i = 0; i < 5; i++)
  {
    pthread_create(tid+i,NULL,thread_run,(void*)"new thread");
  }
  while(1)
  {
    printf("我是主线程，我的thread_ID:%lu\n",pthread_self());
    printf("----------------begin--------------------\n");
    for(int i = 0; i < 5; i++)
    {
      printf("我创建的线程【%d】: %lu\n",i,tid[i]);
    }
    printf("---------------- end --------------------\n");
    sleep(1);
  }
  
  return 0;
}




void* thread_run(void* args)
{
  while(1)
  {
    printf("我是新线程【%s】,我创建的线程ID是：%lu\n",(const char*)args,pthread_self());
    sleep(1);
  }
}
int main()
{
  //创建一个新线程
  pthread_t tid;
  pthread_create(&tid,NULL,thread_run,(void*)"new thread");
  while(1)
  {
    printf("我是主线程,我创建的线程ID是：%lu,我的thread_ID:%lu\n",tid,pthread_self());
    sleep(1);
  }
  return 0;
}
