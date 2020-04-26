#include"BinaryTree.h" 
#include<stdio.h>
#include<stdlib.h> 

//处理初始化逻辑
void Init(BiTree *T)
{
	if(*T != NULL)
		printf("请先销毁原有的树！");
	else
	{
	 	int flag = InitBiTree(T);
	 	if(flag == SUCCESS)
		 	printf("初始化成功");
		else
			printf("初始化失败");	
	}
			 
} 

//初始化树 
Status InitBiTree(BiTree *T)
{
    *T = (BiTree)malloc(sizeof(BiTNode));
    if(*T == NULL)
		return ERROR;
    (*T)->lchild = NULL;
    (*T)->rchild = NULL;
    return SUCCESS;
}





//处理摧毁逻辑 
void Destroy(BiTree T)
{
	if(T == NULL)
		printf("请先初始化二叉树！");
	else
	{
	 	int flag = DestroyBiTree(T);//负责摧毁 
	 	if(flag == SUCCESS)
		 	printf("摧毁成功");
		else
			printf("摧毁失败");	
	}
}

//摧毁二叉树 
Status DestroyBiTree(BiTree T)
{
	BiTree pLeft = NULL;
	BiTree pRight = NULL;
	if (T == NULL)
		return ERROR;
	pLeft = T->lchild;
	pRight = T->rchild;
	T->lchild = NULL;
	T->rchild = NULL;
	free(T);
	T = NULL;   //防止出现野指针 
	DestroyBiTree(pLeft);
	DestroyBiTree(pRight);
	return SUCCESS;	
}


//处理创建逻辑 
void create(BiTree *T)
{
	char ch[100];
	if(*T == NULL)
	{
		printf("请先初始化树！");
		return;
	}
	printf("请按前序遍历的方式输入('#'代表空)：");
	scanf("%s",ch);
	int i;
	int totalCh = 0;
	int totalBlank = 0;
	for(totalCh = totalBlank = i = 0; ch[i] != '\0' ; i++ ) //截取输入的字符串,计算有效元素的个数与空白的个数 
	{
		if(ch[i] == '#')
			totalBlank++;
		if(ch[i] >='0' && ch[i] <= '9')
			totalCh++;	
	}
	//根节点不是空    有效元素的结点 + 空节点 = 总结点个数          叶子结等于度为2的结点+1 --> 空白个数 = 非空白个数 + 1 
	if( ch[0] != '#' && totalBlank + totalCh == i && totalCh + 1 == totalBlank  )
		createBiTree(T,ch);
	else
		printf("您的输入有误,请核实清楚！");	
}


char* createBiTree(BiTree *T,char* definition)
{
	char ch = *definition;
	if( ch == '#')
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));	
		if(!(*T))
			return;
		(*T)->data = ch;			//二级指针 
		definition = createBiTree(&((*T)->lchild),definition+1);//左子树 
		definition = createBiTree(&((*T)->rchild),definition+1);//右子树	
	}
	return definition;			
}
	






//前序遍历 
Status PreOrderTraverse(BiTree T, void (*visit)(TElemType e))
{
    if(T == NULL)
		return ERROR;
    (*visit)(T->data);
    PreOrderTraverse(T->lchild,visit);
    PreOrderTraverse(T->rchild,visit);
    return SUCCESS;	
}



//中序遍历
Status InOrderTraverse(BiTree T, void (*visit)(TElemType e))
{
    if(T == NULL)
		return ERROR;
    InOrderTraverse(T->lchild,visit);
    (*visit)(T->data);             
    InOrderTraverse(T->rchild,visit);
    return SUCCESS;
} 



//后序遍历
Status PostOrderTraverse(BiTree T, void (*visit)(TElemType e))
{
	if(T == NULL )
		return ERROR;
    PostOrderTraverse(T->lchild,visit);
    PostOrderTraverse(T->rchild,visit);
    (*visit)(T->data);  
    return SUCCESS;
}




 
//队列层序遍历二叉树T
//队列初始化 
pLQueue initQueue(pLQueue Q)
{
	Q->front=(pNode)malloc(sizeof(Node));
	Q->front->next=NULL;
	Q->rear=Q->front;
	return Q;
}

//销毁队列 
void destoryQueue(pLQueue Q)
{
	free(Q);
	Q = NULL;
}

//入队 
void enQueue(pLQueue Q,BiTree t)
{
	pNode pNew=(pNode)malloc(sizeof(Node));
	pNew->data=t;
	pNew->next=NULL;
	Q->rear->next=pNew;
	Q->rear=pNew;
}

//出队 
BiTree deQueue(pLQueue Q)
{
	BiTree out;
	pNode temp=(pNode)malloc(sizeof(Node));
	temp=Q->front->next;
	//如果只有一个数据，让队尾指向队头 
	if(temp->next==NULL){
		Q->rear=Q->front;
	}else{
		Q->front->next=temp->next;
	}
	out=temp->data;
	free(temp);
	return out;
}
 
 


//层序遍历
//根节点入队->然后出队，出队时分别将其左、右孩子入队，循环队列进行出队，
//每次出队将其左右孩子入队。当队列为空时，代表整棵树层序遍历完。	
Status LevelOrderTraverse(BiTree T, void (*visit)(TElemType e))
{
	if(T == NULL)
		return ERROR;
	pLQueue Q = (pLQueue)malloc(sizeof(LQueue));
	Q = initQueue(Q);
	
	enQueue(Q,T);
		//如果队列不为空 
	    while(Q->rear!=Q->front)
		{
		    BiTree t=deQueue(Q);		
			visit(t->data);		
			if(t->lchild){			
				enQueue(Q,t->lchild);		
			}
			if(t->rchild){
				enQueue(Q,t->rchild);
			}
		}
	destoryQueue(Q);	
	return SUCCESS;	
}	






//创建前缀表达式
//只有符号才有左右孩子,数字没有左右孩子 
char* createExpression(BiTree *T,char* definition)
{	
	char ch = *definition; 
	
	*T = (BiTree)malloc(sizeof(BiTNode));
	(*T)->data = ch;
    
	if ('0' <= ch && ch <= '9')            
	{    
		(*T)->lchild = NULL;               
		(*T)->rchild = NULL;   
	}
	else
	{	//构造子树,并记录字符位置
		definition = createExpression(&((*T)->lchild),definition+1);
		definition = createExpression(&((*T)->rchild),definition+1);	
	}
	return definition;
} 

//处理前缀表达式的逻辑 
void Expression(BiTree *T)
{
	char ch[100];
	if(*T == NULL)
	{
		printf("请先初始化树！");
		return;
	}
	printf("请输入前缀表达式：");
	scanf("%s",ch);
	int i;
	int totalCh = 0;
	int totalSymbol = 0;
	for(totalCh = totalSymbol = i = 0; ch[i] != '\0' ; i++ ) //截取输入的字符串,计算有效元素的个数与符号的个数 
	{
		if(ch[i] == '+' || ch[i] == '-' || ch[i] == '*' || ch[i] == '/')
			totalSymbol++;
		if(ch[i] >='0' && ch[i] <= '9')
			totalCh++;	
	}
	//数字元素的结点 + 符号节点 = 总结点个数         表达式符号的左右两边都是数字 
	if(totalSymbol + totalCh == i && totalCh - 1 == totalSymbol )
	{
		createExpression(T,ch);
		printf("计算结果为：%d",Value(*T)); 
	} 
	else
		printf("您的输入有误,请核实清楚！");	
}			


//构造出的二叉树求值
int Value(BiTree T)
{
    if(T == NULL)
		return;
    int left =Value(T->lchild);
    int right =Value(T->rchild);
    switch(T->data)
    {
        case '+':return left + right;
        case '-':return left - right;
        case '*':return left * right;
        case '/':return left / right;
        default:return (T->data - '0');
    }
}
		

//非递归遍历使用的栈

//设置全局变量,方便操作,每次遍历之前都清空一次栈
BiTree stack[100];
int top = 0;
int size = 99;

//是否为空 
int stackIsEmpty()
{
	if( top == 0)
		return 1;
	else
		return -1;			
} 

//清空栈 
void stackClear()
{
	top = 0;
}

//出栈 
BiTree stackPop()
{
	if(top == 0)
	{
		printf("栈已空！\n");
		return NULL;	
	}
	else
	{
		BiTree out = (BiTree)malloc(sizeof(BiTNode));
		out	= stack[top];
		top--;
		return out;	
	}	
} 
 
//入栈 
void stackPush(BiTree in)
{
	if(top == 99)
	{
		printf("栈满了！");
		return; 
	}
	else
	{
		top++;
		stack[top] = in;
	}
}

BiTree getTop()
{
	if(stackIsEmpty() != 1)
		return stack[top];
	else
		return NULL;	
}

//非递归前序遍历 
Status pre(BiTree T,void (*visit)(TElemType e))
{
	if(T == NULL)
		return ERROR;
	BiTree temp = T;
	stackClear();
	
	while( temp != NULL || stackIsEmpty() != 1 ) 	
	{
		while(temp != NULL)
		{
			(*visit)(temp->data); 
			stackPush(temp);
			temp = temp->lchild;
		}
		if(stackIsEmpty() != 1)
		{
			temp = stackPop();
			temp = temp->rchild;
		}
	}
	return SUCCESS; 
}


 



//非递归中序遍历 
Status in(BiTree T,void (*visit)(TElemType e))
{	
	if(T == NULL)
		return ERROR; 
	BiTree temp = T;
	stackClear();
	
	while( temp != NULL || stackIsEmpty() != 1) 	
	{
		//一条路走到黑 
		while(temp != NULL)
		{
			stackPush(temp);
			temp = temp->lchild;
		}
		if(stackIsEmpty() != 1)
		{
			temp = stackPop();
			(*visit)(temp->data);
			temp = temp->rchild;
		}
	} 
	return SUCCESS;
}



 

//非递归后序遍历 
Status post(BiTree T,void (*visit)(TElemType e)) 
{	
	if(T == NULL)
		return ERROR;
	BiTree temp = T;
	BiTree cur = T;
	stackClear();
	
	//走到最左边的结点 
	while( temp != NULL || stackIsEmpty() != 1 )
	{
		while(temp != NULL )
		{
			stackPush(temp);
			temp = temp->lchild;
		}
		
		if(stackIsEmpty() != 1)
		{
			BiTree top = getTop();
			if(top->rchild && top->rchild != cur)//如果有右孩子，或者右孩子没有被遍历过 
				temp = top->rchild;
			else
			{
				(*visit)(top->data);
				cur = top;
				stackPop();	
			}	
		}
	}
	return SUCCESS;
}

//打印函数
void print(TElemType e)
{
	printf("%c --> ",e);	
} 

//处理遍历逻辑
void Traverse(BiTree T)
{	
	int flag; 
	if(T == NULL)
		printf("请先初始化树！\n"); 
	else
	{	
		printf("前序遍历："); 
		PreOrderTraverse(T,print);
		printf("\n\n");
		printf("中序遍历：");
		InOrderTraverse(T,print);
		printf("\n\n");
		printf("后序遍历：");
		PostOrderTraverse(T,print);
		printf("\n\n");
		printf("非递归前序遍历：");
		pre(T,print);
		printf("\n\n");
		printf("非递归中序遍历：");
		in(T,print);
		printf("\n\n");
		printf("非递归后序遍历：");
		flag = post(T,print);
		printf("\n\n");
		if(flag == ERROR)
			printf("遍历失败！\n");	
	}		
} 




//菜单 
void menu()
{	 
	printf("***************二叉树展示****************\n"); 
	printf("*    a.初始化树             b.销毁树    *\n");
	printf("*    c.构建树               d.遍历树    *\n");
	printf("*    e.前缀表达式求值       f.退出      *\n");
	printf("*****************************************\n");  
}

 
void go()
{
	printf("\n");
	system("PAUSE");
	system("cls");
	menu();
	printf("\n输入你选择的操作(以输入的第一个字符为准): ");
}

