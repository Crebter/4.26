#include"BinaryTree.h" 
#include<stdio.h>
#include<stdlib.h> 

//�����ʼ���߼�
void Init(BiTree *T)
{
	if(*T != NULL)
		printf("��������ԭ�е�����");
	else
	{
	 	int flag = InitBiTree(T);
	 	if(flag == SUCCESS)
		 	printf("��ʼ���ɹ�");
		else
			printf("��ʼ��ʧ��");	
	}
			 
} 

//��ʼ���� 
Status InitBiTree(BiTree *T)
{
    *T = (BiTree)malloc(sizeof(BiTNode));
    if(*T == NULL)
		return ERROR;
    (*T)->lchild = NULL;
    (*T)->rchild = NULL;
    return SUCCESS;
}





//����ݻ��߼� 
void Destroy(BiTree T)
{
	if(T == NULL)
		printf("���ȳ�ʼ����������");
	else
	{
	 	int flag = DestroyBiTree(T);//����ݻ� 
	 	if(flag == SUCCESS)
		 	printf("�ݻٳɹ�");
		else
			printf("�ݻ�ʧ��");	
	}
}

//�ݻٶ����� 
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
	T = NULL;   //��ֹ����Ұָ�� 
	DestroyBiTree(pLeft);
	DestroyBiTree(pRight);
	return SUCCESS;	
}


//�������߼� 
void create(BiTree *T)
{
	char ch[100];
	if(*T == NULL)
	{
		printf("���ȳ�ʼ������");
		return;
	}
	printf("�밴ǰ������ķ�ʽ����('#'�����)��");
	scanf("%s",ch);
	int i;
	int totalCh = 0;
	int totalBlank = 0;
	for(totalCh = totalBlank = i = 0; ch[i] != '\0' ; i++ ) //��ȡ������ַ���,������ЧԪ�صĸ�����հ׵ĸ��� 
	{
		if(ch[i] == '#')
			totalBlank++;
		if(ch[i] >='0' && ch[i] <= '9')
			totalCh++;	
	}
	//���ڵ㲻�ǿ�    ��ЧԪ�صĽ�� + �սڵ� = �ܽ�����          Ҷ�ӽ���ڶ�Ϊ2�Ľ��+1 --> �հ׸��� = �ǿհ׸��� + 1 
	if( ch[0] != '#' && totalBlank + totalCh == i && totalCh + 1 == totalBlank  )
		createBiTree(T,ch);
	else
		printf("������������,���ʵ�����");	
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
		(*T)->data = ch;			//����ָ�� 
		definition = createBiTree(&((*T)->lchild),definition+1);//������ 
		definition = createBiTree(&((*T)->rchild),definition+1);//������	
	}
	return definition;			
}
	






//ǰ����� 
Status PreOrderTraverse(BiTree T, void (*visit)(TElemType e))
{
    if(T == NULL)
		return ERROR;
    (*visit)(T->data);
    PreOrderTraverse(T->lchild,visit);
    PreOrderTraverse(T->rchild,visit);
    return SUCCESS;	
}



//�������
Status InOrderTraverse(BiTree T, void (*visit)(TElemType e))
{
    if(T == NULL)
		return ERROR;
    InOrderTraverse(T->lchild,visit);
    (*visit)(T->data);             
    InOrderTraverse(T->rchild,visit);
    return SUCCESS;
} 



//�������
Status PostOrderTraverse(BiTree T, void (*visit)(TElemType e))
{
	if(T == NULL )
		return ERROR;
    PostOrderTraverse(T->lchild,visit);
    PostOrderTraverse(T->rchild,visit);
    (*visit)(T->data);  
    return SUCCESS;
}




 
//���в������������T
//���г�ʼ�� 
pLQueue initQueue(pLQueue Q)
{
	Q->front=(pNode)malloc(sizeof(Node));
	Q->front->next=NULL;
	Q->rear=Q->front;
	return Q;
}

//���ٶ��� 
void destoryQueue(pLQueue Q)
{
	free(Q);
	Q = NULL;
}

//��� 
void enQueue(pLQueue Q,BiTree t)
{
	pNode pNew=(pNode)malloc(sizeof(Node));
	pNew->data=t;
	pNew->next=NULL;
	Q->rear->next=pNew;
	Q->rear=pNew;
}

//���� 
BiTree deQueue(pLQueue Q)
{
	BiTree out;
	pNode temp=(pNode)malloc(sizeof(Node));
	temp=Q->front->next;
	//���ֻ��һ�����ݣ��ö�βָ���ͷ 
	if(temp->next==NULL){
		Q->rear=Q->front;
	}else{
		Q->front->next=temp->next;
	}
	out=temp->data;
	free(temp);
	return out;
}
 
 


//�������
//���ڵ����->Ȼ����ӣ�����ʱ�ֱ������Һ�����ӣ�ѭ�����н��г��ӣ�
//ÿ�γ��ӽ������Һ�����ӡ�������Ϊ��ʱ��������������������ꡣ	
Status LevelOrderTraverse(BiTree T, void (*visit)(TElemType e))
{
	if(T == NULL)
		return ERROR;
	pLQueue Q = (pLQueue)malloc(sizeof(LQueue));
	Q = initQueue(Q);
	
	enQueue(Q,T);
		//������в�Ϊ�� 
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






//����ǰ׺���ʽ
//ֻ�з��Ų������Һ���,����û�����Һ��� 
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
	{	//��������,����¼�ַ�λ��
		definition = createExpression(&((*T)->lchild),definition+1);
		definition = createExpression(&((*T)->rchild),definition+1);	
	}
	return definition;
} 

//����ǰ׺���ʽ���߼� 
void Expression(BiTree *T)
{
	char ch[100];
	if(*T == NULL)
	{
		printf("���ȳ�ʼ������");
		return;
	}
	printf("������ǰ׺���ʽ��");
	scanf("%s",ch);
	int i;
	int totalCh = 0;
	int totalSymbol = 0;
	for(totalCh = totalSymbol = i = 0; ch[i] != '\0' ; i++ ) //��ȡ������ַ���,������ЧԪ�صĸ�������ŵĸ��� 
	{
		if(ch[i] == '+' || ch[i] == '-' || ch[i] == '*' || ch[i] == '/')
			totalSymbol++;
		if(ch[i] >='0' && ch[i] <= '9')
			totalCh++;	
	}
	//����Ԫ�صĽ�� + ���Žڵ� = �ܽ�����         ���ʽ���ŵ��������߶������� 
	if(totalSymbol + totalCh == i && totalCh - 1 == totalSymbol )
	{
		createExpression(T,ch);
		printf("������Ϊ��%d",Value(*T)); 
	} 
	else
		printf("������������,���ʵ�����");	
}			


//������Ķ�������ֵ
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
		

//�ǵݹ����ʹ�õ�ջ

//����ȫ�ֱ���,�������,ÿ�α���֮ǰ�����һ��ջ
BiTree stack[100];
int top = 0;
int size = 99;

//�Ƿ�Ϊ�� 
int stackIsEmpty()
{
	if( top == 0)
		return 1;
	else
		return -1;			
} 

//���ջ 
void stackClear()
{
	top = 0;
}

//��ջ 
BiTree stackPop()
{
	if(top == 0)
	{
		printf("ջ�ѿգ�\n");
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
 
//��ջ 
void stackPush(BiTree in)
{
	if(top == 99)
	{
		printf("ջ���ˣ�");
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

//�ǵݹ�ǰ����� 
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


 



//�ǵݹ�������� 
Status in(BiTree T,void (*visit)(TElemType e))
{	
	if(T == NULL)
		return ERROR; 
	BiTree temp = T;
	stackClear();
	
	while( temp != NULL || stackIsEmpty() != 1) 	
	{
		//һ��·�ߵ��� 
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



 

//�ǵݹ������� 
Status post(BiTree T,void (*visit)(TElemType e)) 
{	
	if(T == NULL)
		return ERROR;
	BiTree temp = T;
	BiTree cur = T;
	stackClear();
	
	//�ߵ�����ߵĽ�� 
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
			if(top->rchild && top->rchild != cur)//������Һ��ӣ������Һ���û�б������� 
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

//��ӡ����
void print(TElemType e)
{
	printf("%c --> ",e);	
} 

//��������߼�
void Traverse(BiTree T)
{	
	int flag; 
	if(T == NULL)
		printf("���ȳ�ʼ������\n"); 
	else
	{	
		printf("ǰ�������"); 
		PreOrderTraverse(T,print);
		printf("\n\n");
		printf("���������");
		InOrderTraverse(T,print);
		printf("\n\n");
		printf("���������");
		PostOrderTraverse(T,print);
		printf("\n\n");
		printf("�ǵݹ�ǰ�������");
		pre(T,print);
		printf("\n\n");
		printf("�ǵݹ����������");
		in(T,print);
		printf("\n\n");
		printf("�ǵݹ���������");
		flag = post(T,print);
		printf("\n\n");
		if(flag == ERROR)
			printf("����ʧ�ܣ�\n");	
	}		
} 




//�˵� 
void menu()
{	 
	printf("***************������չʾ****************\n"); 
	printf("*    a.��ʼ����             b.������    *\n");
	printf("*    c.������               d.������    *\n");
	printf("*    e.ǰ׺���ʽ��ֵ       f.�˳�      *\n");
	printf("*****************************************\n");  
}

 
void go()
{
	printf("\n");
	system("PAUSE");
	system("cls");
	menu();
	printf("\n������ѡ��Ĳ���(������ĵ�һ���ַ�Ϊ׼): ");
}

