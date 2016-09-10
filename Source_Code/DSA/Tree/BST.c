#include<stdio.h>
#include<stdlib.h>

typedef struct BST
{
	int data;
	struct BST * left;
	struct BST * right;
}BST;

BST*createNode()
{
	int data;
	BST* newNode;
	newNode=(BST*)malloc(sizeof(BST));
	printf("Enter the node data :");
	scanf("%d",&newNode->data);
	newNode->left=NULL;
	newNode->right=NULL;
   return newNode;
}

BST*InsertNode(BST*newNode,BST*root)
{
	if(!root)
		root=newNode;
	else{
		if(root->data < newNode->data)
			root->right=InsertNode(newNode,root->right);
		else	
			root->left=InsertNode(newNode,root->left);
	}
     return root;
}

void Inorder(BST*root)
{
	if(!root)
	    return;
	Inorder(root->left);
	printf("%d->",root->data);
	Inorder(root->right);
}

void Preorder(BST*root)
{
	if(!root)
	    return;
	printf("%d->",root->data);
	Preorder(root->left);
	Preorder(root->right);
}

void Postorder(BST*root)
{
	if(!root)
	    return;
	Postorder(root->left);
	Postorder(root->right);
	printf("%d->",root->data);
}

int countNode(BST*root)
{
	int n;
	if(!root)
		return 0;
	n=countNode(root->left)+1;
	n=n+countNode(root->right);
   return n;
}

int heightTree(BST*root)
{
	int lh,rh;
	if(!root)
		return 0;
	lh=heightTree(root->left)+1;
	rh=heightTree(root->right)+1;
    return (lh>rh)?lh:rh;
}

int main()
{
	int ch;
		
	BST*root=NULL,*newNode;
	
   while(1){
	printf("\n");
	printf("\t1.Insert new node\n\t2.Delete a node\n\t3.Preorder Traversal\n\t4.Inorder Traversal\n\t5.Postorder Traversal\n\t6.Count Nodes\n\t7.Height of Tree\n\t9.Exit\n");
	printf("Enter Your choice \n");
	scanf("%d",&ch);
	switch(ch)
	  { 
		case 1:		newNode=createNode();
				root=InsertNode(newNode,root);	
				break;
		case 2:	
				break;
		case 3:		Preorder(root);
				break;
		case 4:		Inorder(root);
				break;
		case 5:		Postorder(root);
				break;
		case 6:		printf("Total no of nodes is %d \n",countNode(root));
				break;
		case 7:		printf("Height of tree is %d \n",heightTree(root));
				break;
		case 9:		exit(0);
				break;
		default:	printf("Please enter correct choice\n");
				break;
	  }
	}
	
}
