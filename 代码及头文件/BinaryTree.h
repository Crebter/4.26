#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
typedef char TElemType;     // �������������Ԫ������Ϊ�ַ�

typedef struct  BiTNode {
    TElemType      data;     // ������
    struct BiTNode  *lchild,*rchild;  // ���Һ���ָ��
} BiTNode,*BiTree;   // ��������

//�ö���ʵ�ֲ������
typedef struct Node
{
    BiTree data;                   //������
    struct Node *next;            //ָ���� 
}Node,*pNode;

typedef struct LQueue
{
    Node *front;                   //��ͷ
    Node *rear;                    //��β
}LQueue,*pLQueue;




typedef enum Status{
	ERROR = 0,
	SUCCESS = 1
}Status;

void Init(BiTree *T); 
Status InitBiTree(BiTree *T);
//�������������ն�����T

void Destroy(BiTree T);
Status DestroyBiTree(BiTree T);
//��ʼ������������T����
//����������ݻٶ�����T

void create(BiTree *T);
char* createBiTree(BiTree *T,char* definition); 
//��ʼ������ definition�����������Ķ���
//�����������definition���������T



void print(TElemType e);
//���²��ֺ�������δָ����������
Status PreOrderTraverse(BiTree T, void (*visit)(TElemType e));		//ǰ����� 

Status InOrderTraverse(BiTree T, void (*visit)(TElemType e));		//�������

Status PostOrderTraverse(BiTree T, void (*visit)(TElemType e)); 	//�������

Status LevelOrderTraverse(BiTree T, void (*visit)(TElemType e));	//�������
int Value(BiTree T);			//������Ķ�������ֵ
/*
��ʾ�����ڽ��ṹ�������ø�Tagֵ��־������������������������
�ɸ�����Ҫ�������Ӳ���.
*/
#endif // BINARYTREE_H_INCLUDED
