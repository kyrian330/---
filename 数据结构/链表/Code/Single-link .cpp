#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node {
    ElemType data;       // ������
    struct node *next;   // ָ����
} Node;                  // ��������������


// ��ʼ��
void InitList(Node *& L) {
    L = (Node *)malloc(sizeof(Node));
    L->next = NULL;
}


// β�巨����
void Create(Node *& L, ElemType a[], int n) {
    Node *s, *r;
    int i;
    L = (Node *)malloc(sizeof(Node));
    r = L;
    for (i=0; i<n; i++) {
        s = (Node *)malloc(sizeof(Node));
        s->data = a[i];
        r->next = s;
        r = s;
    }
    r->next=NULL;
}


// ����Ԫ��
int InsElem(Node *& L, int i, ElemType x) {
    int j = 0;
    Node *p = L, *s;
    if (i<=0) return 0;
    while (p!=NULL && j<i-1) {
        j++;
        p = p->next;
    }
    if (p==NULL)
        return 0;
    else {
        s = (Node *)malloc(sizeof(Node));
        s->data = x;
        s->next = p->next;
        p->next = s;
        return 1;
    }
}


// ɾ���� i ��Ԫ��
int DelElem(Node *&L, int i) {
    int j = 0;
    Node *p = L;
    if (i<=0) return 0;
    while (p!=NULL && j<i-1) {
        j++;
        p = p->next;
    }
    if (p==NULL)
        return 0;
    else {
        Node *q;
        q = p->next;
        if (q==NULL)
            return 0;
        else {
            p->next = q->next;
            free(q);
            return 1;
        }
    }
}


// ��ȡ�� i ��Ԫ��
int GetElem(Node *L, int i) {
    int j = 0;
    Node *p = L;
    if (i<=0) return 0;
    while (p!=NULL && j<i) {
        j++;
        p = p->next;
    }
    if (p==NULL)
        return 0;
    else
        return p->data;
}


// ���������
void DispList(Node *L) {
    Node *p = L->next;
    while (p!=NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}


// ���ٱ�
void DestroyList(Node *& L) {
    Node *pre = L,*p = pre->next;
    while (p!=NULL) {
        free(pre);
        pre = p; p = p->next;
    }
    free(pre);
}

#define MAXV 100
int main() {
    int i, n;
    int a[MAXV];
    Node *L;
    InitList(L);
    printf("���������������\n");
    scanf("%d", &n);
    printf("�������� %d ����:\n", n);
    for (i=0; i<n; i++)
        scanf("%d", &a[i]);
    Create(L, a, n);
    printf("������L�����ɹ���\n");
    DispList(L);

    int index=3, data=23;
    printf("�� %d λ�ò������� %d\n", index, data);
    InsElem(L, index, data);
    DispList(L);

    index = 2;
    printf("ɾ���� %d ��Ԫ��\n", index);
    DelElem(L, index);
    DispList(L);

    index = 5;
    printf("��ȡ�� %d ��Ԫ��\n", index);
    printf("%d ", GetElem(L, index));
    return 0;
}