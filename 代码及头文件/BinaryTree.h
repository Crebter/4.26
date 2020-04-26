#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
typedef char TElemType;     // 假设二叉树结点的元素类型为字符

typedef struct  BiTNode {
    TElemType      data;     // 数据域
    struct BiTNode  *lchild,*rchild;  // 左、右孩子指针
} BiTNode,*BiTree;   // 二叉链表

//用队列实现层序遍历
typedef struct Node
{
    BiTree data;                   //数据域
    struct Node *next;            //指针域 
}Node,*pNode;

typedef struct LQueue
{
    Node *front;                   //队头
    Node *rear;                    //队尾
}LQueue,*pLQueue;




typedef enum Status{
	ERROR = 0,
	SUCCESS = 1
}Status;

void Init(BiTree *T); 
Status InitBiTree(BiTree *T);
//操作结果：构造空二叉树T

void Destroy(BiTree T);
Status DestroyBiTree(BiTree T);
//初始条件：二叉树T存在
//操作结果：摧毁二叉树T

void create(BiTree *T);
char* createBiTree(BiTree *T,char* definition); 
//初始条件： definition给出二叉树的定义
//操作结果：按definition构造二叉树T



void print(TElemType e);
//以下部分函数定义未指定参数类型
Status PreOrderTraverse(BiTree T, void (*visit)(TElemType e));		//前序遍历 

Status InOrderTraverse(BiTree T, void (*visit)(TElemType e));		//中序遍历

Status PostOrderTraverse(BiTree T, void (*visit)(TElemType e)); 	//后序遍历

Status LevelOrderTraverse(BiTree T, void (*visit)(TElemType e));	//层序遍历
int Value(BiTree T);			//构造出的二叉树求值
/*
提示：可在结点结构体中设置个Tag值标志数字与操作符来构造二叉树，
可根据需要自行增加操作.
*/
#endif // BINARYTREE_H_INCLUDED
