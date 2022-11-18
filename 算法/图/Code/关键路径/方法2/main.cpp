/*
 * @����: �ؼ�·��
 * @����: �ݺ�
 * @����ʱ��: 2022/11/18 18:20
 */
 
#include <stdio.h>
#include "MatGraph.cpp"
int dis[100];

struct node {
    int adjvex;  // �����±�
    int u;
    int v;
    int w;
};
struct node node[12];    // ����g.e-1���ṹ�壨�ȱ�����1��
int cnt=0;

void bellman(MatGraph g) {
    int i, j, k;
    bool check = false;
    for (i = 0; i < g.n ; ++i)
        dis[i] = -INF;
    dis[0] = 0;

    // Bellman-Ford
    for (k = 0; k < g.n-1 ; ++k) {
        for (i = 0; i < g.e ; ++i) {
            for(j = 0; j < g.e; ++j) {
                if (g.edges[i][j]!=INF && g.edges[i][j]!=0) {
                    if (dis[j] < dis[i] + g.edges[i][j]) {
                        dis[j] = dis[i] + g.edges[i][j];
                        printf("Դ�� %d �ɱ� <%d %d> �ɳڳɹ�, ·����%d\n", j, i, j, dis[j]);
                        // ���������Ϣ
                        node[cnt].adjvex = j;
                        node[cnt].u = i;
                        node[cnt].v = j;
                        node[cnt].w = dis[j];
                        cnt++;
                        check = true;
                    }
                }
            }
        }
        if (!check)
            break;  // dis���鲻�ٸ���, ����ǰ�˳�ѭ��
    }
}


int main() {

    MatGraph g;
    int i;
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

    bellman(g);
    printf("���\n");
    for (i = 0; i < g.n; ++i)
        printf("%d ", dis[i]);

    // ��ؼ�·��
    int adjvex,w1;
    adjvex = node[11].adjvex;   // �ȱ������һ����Ϣ, ����ǰ�Ƶ�
    w1 = node[11].w;

    printf("\n�ؼ�·����\n");
    printf("<%d %d> ", node[11].u, node[11].v);
    for (i=10; i>0; i--) {    // ֻ�ܴӺ���ǰȡ
        // printf("%d %d %d\n", node[i].adjvex, node[i].u, node[i].v, node[i].w);
        if (node[i].adjvex < adjvex && node[i].w < w1) {
            printf("<%d %d> ", node[i].u, node[i].v);
            // ������Ϣ
            adjvex = node[i].adjvex;
            w1 = node[i].w;
        }
    }
    return 0;
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