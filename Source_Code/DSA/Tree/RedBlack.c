#include<stdio.h>
#include<stdlib.h>

typedef struct BST
{
	int data;
	struct BST * left;
	struct BST * right;
}BST;

int main()
{
	int ch;
	while(1){
	printf("\t1.Insert new node\n\t2.Delete a node\n\t3.Preorder Traversal\n\t4.Inorder Traversal\n\t5.Postorder Traversal\n\t6.Exit\n");
	printf("Enter Your choice \n");
	scanf("%d",&ch);
	switch(ch)
	  { 
		case 1:		
				break;
		case 2:	
				break;
		case 3:
				break;
		case 4:
				break;
		case 5:
				break;
		case 6:		exit(0);
				break;
		default:	printf("Please enter correct choice\n");
				break;
	  }
	}
	
}
