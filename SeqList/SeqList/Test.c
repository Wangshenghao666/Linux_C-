#define _CRT_SECURE_NO_WARNINGS 1
#include"SL.h"

void Test1()
{
	SL sl;
	SeqListInit(&sl);
	SeqListPushBack(&sl, 1);
	SeqListPushBack(&sl, 2);
	SeqListPushBack(&sl, 3);
	SeqListPushBack(&sl, 4);
	SeqListPrint(&sl);
	/*SeqListPopFront(&sl);
	SeqListPopFront(&sl);
	SeqListPopFront(&sl);*/

	int find = SeqListFind(&sl, 1);
	if (find != -1)
	{
		SeqListInsert(&sl, find, 9);
		SeqListPrint(&sl);

		SeqListErase(&sl, SeqListFind(&sl, 9));
		SeqListPrint(&sl);

	}

	SeqListDestroy(&sl);

}
int main()
{
	//Test1();

	return 0;
}