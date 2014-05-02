#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXEDGE 20
#define MAXVEX 20
#define INFINITY 65535

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

typedef struct
{
	int vexs[MAXVEX];
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

typedef int Patharc[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];

/* 构件图 */
void CreateMGraph(MGraph *G)
{
	int i, j;

	/* printf("请输入边数和顶点数:"); */
	G->numEdges=16;
	G->numVertexes=9;

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		G->vexs[i]=i;
	}

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			if (i==j)
				G->arc[i][j]=0;
			else
				G->arc[i][j] = G->arc[j][i] = INFINITY;
		}
	}

	G->arc[0][1]=1;
	G->arc[0][2]=5; 
	G->arc[1][2]=3; 
	G->arc[1][3]=7; 
	G->arc[1][4]=5; 

	G->arc[2][4]=1; 
	G->arc[2][5]=7; 
	G->arc[3][4]=2; 
	G->arc[3][6]=3; 
	G->arc[4][5]=3;

	G->arc[4][6]=6;
	G->arc[4][7]=9; 
	G->arc[5][7]=5; 
	G->arc[6][7]=2; 
	G->arc[6][8]=7;

	G->arc[7][8]=4;


	for(i = 0; i < G->numVertexes; i++)
	{
		for(j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] =G->arc[i][j];
		}
	}

}

/* Floyd算法，求网图G中各顶点v到其余顶点w的最短路径P[v][w]及带权长度D[v][w]。 */    
void ShortestPath_Floyd(MGraph G, Patharc *P, ShortPathTable *D)
{    
	int v,w,k;    
	for(v=0; v<G.numVertexes; ++v) /* 初始化D与P */  
	{        
		for(w=0; w<G.numVertexes; ++w)  
		{
			(*D)[v][w]=G.arc[v][w];	/* D[v][w]值即为对应点间的权值 */
			(*P)[v][w]=w;				/* 初始化P */
		}
	}
	for(k=0; k<G.numVertexes; ++k)   
	{
		for(v=0; v<G.numVertexes; ++v)  
		{        
			for(w=0; w<G.numVertexes; ++w)    
			{
				if ((*D)[v][w]>(*D)[v][k]+(*D)[k][w])
				{/* 如果经过下标为k顶点路径比原两点间路径更短 */
					(*D)[v][w]=(*D)[v][k]+(*D)[k][w];/* 将当前两点间权值设为更小的一个 */
					(*P)[v][w]=(*P)[v][k];/* 路径设置为经过下标为k的顶点 */
				}
			}
		}
	}
}

int main(void)
{    
	int v,w,k;  
	MGraph G;    
	
	Patharc P;    
	ShortPathTable D; /* 求某点到其余各点的最短路径 */   
	
	CreateMGraph(&G);
	
	ShortestPath_Floyd(G,&P,&D);  

	printf("各顶点间最短路径如下:\n");    
	for(v=0; v<G.numVertexes; ++v)   
	{        
		for(w=v+1; w<G.numVertexes; w++)  
		{
			printf("v%d-v%d weight: %d ",v,w,D[v][w]);
			k=P[v][w];				/* 获得第一个路径顶点下标 */
			printf(" path: %d",v);	/* 打印源点 */
			while(k!=w)				/* 如果路径顶点下标不是终点 */
			{
				printf(" -> %d",k);	/* 打印路径顶点 */
				k=P[k][w];			/* 获得下一个路径顶点下标 */
			}
			printf(" -> %d\n",w);	/* 打印终点 */
		}
		printf("\n");
	}

	printf("最短路径D\n");
	for(v=0; v<G.numVertexes; ++v)  
	{        
		for(w=0; w<G.numVertexes; ++w)    
		{
			printf("%d\t",D[v][w]);
		}
		printf("\n");
	}
	printf("最短路径P\n");
	for(v=0; v<G.numVertexes; ++v)  
	{        
		for(w=0; w<G.numVertexes; ++w)    
		{
			printf("%d ",P[v][w]);
		}
		printf("\n");
	}

	return 0;
}
