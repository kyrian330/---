#include <stdio.h>
#include <malloc.h>
#include "MatGraph.cpp"
#include "AdjGraph.cpp"

// �ڽӾ��� ת���� �ڽӱ�
void MatToAdj(MatGraph g, AdjGraph *&G) {
    int i, j;
    ArcNode *p;
    G = (AdjGraph *)malloc(sizeof(AdjGraph));
    for (i=0; i<g.n; i++) {
        G->adjlist[i].in = 0;   // �����ʼ����0
        G->adjlist[i].data = i;  // ������Ϣ������Ϊ�����±�
        G->adjlist[i].firstarc = NULL;
    }
    for (i=0; i<g.n; i++)  // ����ڽӾ�����ÿ��Ԫ��
        for (j=0; j<=g.n; j++)
            if (g.edges[i][j]!=0 && g.edges[i][j]!=INF) {  // ��һ����
                p=(ArcNode *)malloc(sizeof(ArcNode));
                p->adjvex = j;
                p->weight = g.edges[i][j];
                p->nextarc = G->adjlist[i].firstarc;
                G->adjlist[i].firstarc = p;
                G->adjlist[j].in++;    // �ö������� +1
            }
    G->n=g.n; G->e=g.e;
}


// ��������, ��GL�޻�·, ����������������в�����1, ���л�·����0
int TopologicalSort(AdjGraph* G)
{
    ArcNode *p;
    int i, k, gettop;
    int top = 0;
    int count = 0;
    int *stack;
    stack = (int *)malloc(G->n * sizeof(int) );

    for(i = 0; i<G->n; i++)
        if(G->adjlist[i].in == 0)
            stack[++top]=i;
    while(top != 0) {
        gettop = stack[top];  --top; // ��ջ
        printf("%d -> ",G->adjlist[gettop].data);  ++count;
        // �����ö�������б߽��
        p = G->adjlist[gettop].firstarc;
        while(p) {
            k = p->adjvex;
            if( !(-- G->adjlist[k].in) ) // ��i�Ŷ�����ڽӵ����ȼ�1, �����1��Ϊ0, ����ջ
                stack[++top] = k;
            p = p->nextarc;
        }
    }
    printf("\n");
    if(count < G->n)
        return 0;
    else
        return 1;
}


int main()
{
    AdjGraph *G;
    MatGraph g;
    int n, e;
    int u, v, w;
    printf("����:\n");
    scanf("%d %d", &n, &e);
    InitMat(g, n, e);    // ��ʼ��
    // �����
    for (int i=0; i<e; i++) {
        scanf("%d %d %d", &u, &v, &w);
        InsertEdge(g, u, v, w);
    }

    printf("���:\n");
    printf("ͼG���ڽӾ���:\n");  DispMat(g);
    MatToAdj(g, G);
    printf("ͼG���ڽӱ�:\n");  DispAdj(G);

    // ���
    printf("ͼG�����ж�������:\n");
    printf("  ����\t��\n");
    for (int i=0; i<G->n; i++)
        printf("   %d\t%d\n",i,Degree(G,i));

    int result=TopologicalSort(G);
    printf("result:%d",result);
    DestroyMat(g);
    DestroyAdj(G);
}

/*
14 20
0 4 1
0 5 1
0 11 1
1 2 1
1 4 1
1 8 1
2 5 1
2 6 1
2 9 1
3 2 1
3 13 1
4 7 1
5 8 1
5 12 1
6 5 1
8 7 1
9 10 1
9 11 1
10 13 1
12 9 1
*/