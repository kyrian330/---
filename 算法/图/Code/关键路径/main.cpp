#include <stdio.h>
#include <malloc.h>
#include "MatGraph.cpp"
#include "AdjGraph.cpp"

int *etv, *ltv;
int *stack2;
int top2;

// �ڽӾ��� ת���� �ڽӱ�
void MatToAdj(MatGraph g, AdjGraph *&G) {
    int i, j;
    ArcNode *p;
    G = (AdjGraph *)malloc(sizeof(AdjGraph));
    G->n=g.n;  G->e=g.e;
    for (i=0; i<g.n; i++) {
        G->adjlist[i].in = 0;
        G->adjlist[i].data = i;
        G->adjlist[i].firstarc = NULL;
    }
    for (i=0; i<g.n; i++)
        for (j=0; j<=g.n; j++)
            if (g.edges[i][j]!=0 && g.edges[i][j]!=INF) {  // ��һ����
                p=(ArcNode *)malloc(sizeof(ArcNode));
                p->adjvex = j;
                p->weight = g.edges[i][j];
                p->nextarc = G->adjlist[i].firstarc;
                G->adjlist[i].firstarc = p;
                G->adjlist[j].in++;    // �ö������� +1
            }
}


// ��������
int TopologicalSort(AdjGraph* G) {
    ArcNode *p;
    int i, k, gettop;
    int top = 0;
    int count = 0;
    int *stack;
    stack=(int *)malloc(G->n * sizeof(int) );
    for(i = 0; i<G->n; i++)
        if(G->adjlist[i].in==0)
            stack[++top] = i;

    top2 = 0;
    etv = (int *)malloc(G->n * sizeof(int) ); // �¼����緢��ʱ������
    for(i=0; i<G->n; i++)
        etv[i] = 0;    // ��ʼ��
    stack2 = (int *)malloc(G->n * sizeof(int) );  // ��ʼ����������ջ

    printf("��������:  ");
    while(top!=0) {
        gettop = stack[top--];
        printf("%d -> ",G->adjlist[gettop].data);   count++;

        stack2[++top2]=gettop;        // �������Ķ������ѹ���������е�ջ
        p = G->adjlist[gettop].firstarc;
        while(p) {
            k = p->adjvex;
            if( !(-- G->adjlist[k].in) )
                stack[++top] = k;

            if((etv[gettop] + p->weight) > etv[k])    // ��������¼������緢��ʱ�� etvֵ
                etv[k] = etv[gettop] + p->weight;

            p = p->nextarc;
        }
    }
    printf("\n");
    if(count < G->n)
        return 1;
    else
        return 0;
}

// ��ؼ�·��, GΪ������, ���G�ĸ���ؼ��
void CriticalPath(AdjGraph* G) {
    ArcNode *p;
    int i, gettop, k, j;
    int ete, lte;  // ��������緢��ʱ�����ٷ���ʱ�����
    TopologicalSort(G);   // ���������У���������etv��stack2��ֵ
    ltv=(int *)malloc(G->n*sizeof(int));// �¼����緢��ʱ������
    for(i=0; i<G->n; i++)
        ltv[i]=etv[G->n-1];    // ��ʼ��

    printf("etv: \t");
    for(i=0; i<G->n; i++)
        printf("%d -> ",etv[i]);
    printf("\n");

    while(top2!=0) {    // ��ջ����ltv
        gettop=stack2[top2--];
        for(p = G->adjlist[gettop].firstarc; p; p = p->nextarc) {       // ��������¼�����ٷ���ʱ�� ltvֵ
            k = p->adjvex;
            if(ltv[k] - p->weight < ltv[gettop])
                ltv[gettop] = ltv[k] - p->weight;
        }
    }

    printf("ltv: \t");
    for(i=0; i<G->n; i++)
        printf("%d -> ",ltv[i]);
    printf("\n");

    for(j=0; j<G->n; j++) {       // ��ete,lte�͹ؼ��
        for(p = G->adjlist[j].firstarc; p; p = p->nextarc) {
            k = p->adjvex;
            ete = etv[j];        // ����緢��ʱ��
            lte = ltv[k] - p->weight; // ���ٷ���ʱ��
            if(ete == lte)    // ������ȼ��ڹؼ�·����
                printf("<v%d - v%d> length: %d \n",G->adjlist[j].data, G->adjlist[k].data, p->weight);
        }
    }
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

    CriticalPath(G);
	DestroyMat(g);
    DestroyAdj(G);
}

/*
10 13
0 1 3
0 2 4
1 3 5
1 4 6
2 3 8
2 5 7
3 4 3
4 6 9
4 7 4
5 7 6
6 9 2
7 8 5
8 9 3
*/