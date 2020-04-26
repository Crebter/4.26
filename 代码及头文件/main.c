#include<stdio.h>
#include<stdlib.h>
#include"BinaryTree.h"



int main()
{
	BiTree root = NULL;
    char choice;
	menu();
	printf("\n输入你选择的操作(以输入的第一个字符为准): ");
    while((choice = getchar()) != 'f')
	{
		if(choice == '\n')
			continue;
		if('a' <= choice && choice <= 'f')
		{	
			switch(choice)
			{
				case 'a':
					Init(&root);
					go();
					break;
				case 'b':
					Destroy(root);
                    root = NULL;
					go();
					break;
				case 'c':
					create(&root);
					go();
					break;
				case 'd':
					Traverse(root);
					go();
					break;
				case 'e':
					Expression(&root);
					go();
					break;
				case 'f':
					exit(0);
					break;	
			}
			
		}
		else 
			printf("输入有误,请重新输入: ");

		while(getchar() != '\n')
			continue;
	}
}  
