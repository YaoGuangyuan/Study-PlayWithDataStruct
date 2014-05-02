#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */

#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 12 /* 定义散列表长为数组的长度 */
#define NULLKEY -32768 

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */ 

typedef struct
{
   int *elem; /* 数据元素存储基址，动态分配数组 */
   int count; /*  当前数据元素个数 */
}HashTable;

int m=0; /* 散列表表长，全局变量 */

/* 初始化散列表 */
Status InitHashTable(HashTable *H)
{
	int i;
	m=HASHSIZE;
	H->count=m;
	H->elem=(int *)malloc(m*sizeof(int));
	for(i=0;i<m;i++)
		H->elem[i]=NULLKEY; 
	return OK;
}

/* 散列函数 */
int Hash(int key)
{
	return key % m; /* 除留余数法 */
}

/* 插入关键字进散列表 */
void InsertHash(HashTable *H,int key)
{
	int addr = Hash(key); /* 求散列地址 */
	while (H->elem[addr] != NULLKEY) /* 如果不为空，则冲突 */
	{
		addr = (addr+1) % m; /* 开放定址法的线性探测 */
	}
	H->elem[addr] = key; /* 直到有空位后插入关键字 */
}

/* 散列表查找关键字 */
Status SearchHash(HashTable H,int key,int *addr)
{
	*addr = Hash(key);  /* 求散列地址 */
	while(H.elem[*addr] != key) /* 如果不为空，则冲突 */
	{
		*addr = (*addr+1) % m; /* 开放定址法的线性探测 */
		if (H.elem[*addr] == NULLKEY || *addr == Hash(key)) /* 如果循环回到原点 */
			return UNSUCCESS;	/* 则说明关键字不存在 */
	}
	return SUCCESS;
}

int main()
{
	int arr[HASHSIZE]={12,67,56,16,25,37,22,29,15,47,48,34};
	int i,p,key,result;
	HashTable H;

	key=39;

	InitHashTable(&H);
	for(i=0;i<m;i++)
		 InsertHash(&H,arr[i]);
	
	result=SearchHash(H,key,&p);
	if (result)
		printf("查找 %d 的地址为：%d \n",key,p);
	else
		printf("查找 %d 失败。\n",key);

	for(i=0;i<m;i++)
	{
		key=arr[i];
		SearchHash(H,key,&p);
		printf("查找 %d 的地址为：%d \n",key,p);
	}

	return 0;
}
