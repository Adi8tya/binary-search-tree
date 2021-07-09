#include<iostream>
#include<conio.h>
#include<malloc.h>
#include<math.h>
using namespace std;
struct node
{
	int data;
	struct node *left;
	struct node *right;
};
struct node *tree=NULL;
struct node *tree2=NULL;
struct node *insertele(struct node *tree,int val)
{
	struct node *ptr,*nodeptr,*parentptr;
	ptr=(struct node *)malloc(sizeof(struct node));
	ptr->data=val;
	ptr->left=NULL;
	ptr->right=NULL;
	if(tree==NULL)
	{
		tree=ptr;
		tree->left=NULL;
		tree->right=NULL;
	}
	else
	{
		parentptr=NULL;
		nodeptr=tree;
		while(nodeptr!=NULL)
		{
			parentptr=nodeptr;
			if(val<nodeptr->data)
			nodeptr=nodeptr->left;
			else
			nodeptr=nodeptr->right;
		}
		if(val<parentptr->data)
		parentptr->left=ptr;
		else
		parentptr->right=ptr;
	}
	return tree;
}

struct node *inst2(struct node *tree2,int val)
{
	struct node *ptr,*nodeptr,*parentptr;
	ptr=(struct node *)malloc(sizeof(struct node));
	ptr->data=val;
	ptr->left=NULL;
	ptr->right=NULL;
	if(tree2==NULL)
	{
		tree2=ptr;
		tree2->left=NULL;
		tree2->right=NULL;
	}
	else
	{
		parentptr=NULL;
		nodeptr=tree2;
		while(nodeptr!=NULL)
		{
			parentptr=nodeptr;
			if(val<nodeptr->data)
			nodeptr=nodeptr->left;
			else
			nodeptr=nodeptr->right;
		}
		if(val<parentptr->data)
		parentptr->left=ptr;
		else
		parentptr->right=ptr;
	}
	return tree2;
}




struct node *findmax(struct node *tree)
{
	if(tree==NULL && tree->right==NULL)
	return tree;
	else
   	return findmax(tree->right);
}
struct node *deleteele(struct node *tree,int data)
{
	struct node *temp;
	if(tree==NULL)
	printf("\n no element exist");
	
	else if(data<tree->data)
	tree->left=deleteele(tree->left,data);
	
	else if(data>tree->data)
	tree->right=deleteele(tree->right,data);
	
	else
	{
		if(tree->left && tree->right)
		{
			temp=findmax(tree->left);
			tree->data=temp->data;
			tree->left=deleteele(tree->left,tree->data);
		}
		else
		{
			temp=tree;
			if(tree->left==NULL)
			tree=tree->right;
			if(tree->right==NULL)
			tree=tree->left;
			free(temp);
		}
	}
	return tree;
}

int height(struct node *tree)
{
	int left,right;
	if(tree==NULL)
	return 0;
	else
	{
		left=height(tree->left);
		right=height(tree->right);
		if(left>right)
		return left+1;
		else
		return right+1;
	}
}

int add(struct node *tree)
{
	if(tree==NULL)
	return 0;
	int sum=tree->data+add(tree->left)+add(tree->right);
	return sum;
}

struct node *find(struct node *tree,int data)
{
	if(tree==NULL)
	return 0;
	if(data<tree->data)
	return find(tree->left,data);
	else if(data>tree->data)
	return find(tree->right,data);
	else
	return tree;
}
void *inorder(struct node *tree,int data)
{
	struct node *y,*z,*store=NULL,*ans=tree;
	z=find(tree,data);
	if(z->right!=NULL)
	{
		
		y=z->right;
		while(y->left!=NULL)
		{
			y=y->left;
		}
		printf(" inorder----->%d",y->data);        //inorder successor
	}
	else
	{
	//	z=find(tree,data);
		while(z->data!=ans->data)
		{
			if(z->data<=ans->data)
			{
				store=ans;
				ans=ans->left;	
			}
			else
			ans=ans->right;
		}	
		printf(" inorder----->%d",store->data);
	}
	
}

struct node *lca(struct node *tree,int n1,int n2)
{
	while(tree!=NULL)
	{
		if(tree->data>n1 && tree->data>n2)
		tree=tree->left;
		else if(tree->data<n1 && tree->data<n2)
		tree=tree->right;
		else
		break;	
	}
	return tree;
}
int check(struct node *tree,struct node *tree2)
{
	if(tree==NULL && tree2==NULL)
	return 1;
	
	if(tree!=NULL && tree2!=NULL)
	{
		if(tree->data==tree2->data && check(tree->left,tree2->left) && check(tree->right,tree2->right))
		return 1;
	}
	return 0;
}

int sumtree(struct node *tree)
{
	if(tree==NULL)
	return 1;
	
	if(tree->left==NULL && tree->right==NULL)
	return 1;
	
	int left=add(tree->left);
	int right=add(tree->right);
	int total=left+right;
	if(tree->data==total)
	{
		if(sumtree(tree->left) && sumtree(tree->right))
		return 1;
	}
	return 0;
	
}

int traverse(struct node *tree,struct node *target)
{
	if(tree!=NULL)
	{
		if(tree->data==target->data)
		return 1;
		
		if(traverse(tree->left,target) || traverse(tree->right,target))
		{
			printf("%d",tree->data);
			return 1;
		}
	}
	return 0;
}
int max(int a,int b)
{
	if(a>b)
	return a;
	else
	return b;
}
int diameter(struct node *tree)
{
	if(tree==NULL)
	return 0;
	
	int lh=height(tree->left);
	int rh=height(tree->right);
	int ld=diameter(tree->left);
	int rd=diameter(tree->right);
	return max(lh+rh+1,max(ld,rd));
}

bool balance(struct node *tree)
{
	if(tree==NULL)
	return 1;
	
	if(abs(height(tree->left)-height(tree->right))<=1 && balance(tree->left) && balance(tree->right))
	return 1;
	
	return 0;
	
}

int mindepth(struct node *tree)
{
	if(tree==NULL)
	return 0;
	if(tree->left==NULL && tree->right==NULL)
	return 1;
	
	if(tree->left==NULL)
	return mindepth(tree->right)+1;
	if(tree->right==NULL)
	return mindepth(tree->left)+1;
	
	return(min(mindepth(tree->left),mindepth(tree->right))+1);
}
int main()
{
	int option,val;
	struct node *ptr;
	do
	{
		printf("\n Insert element ");
			printf("\n delete element ");
			printf("\n height");
			printf("\n Sum of bst");
			printf("\n inorder");
			printf("\n lcs");
			printf("\n insert in tree2");
			printf("\n idenical");
			printf("\n SumTree");
			printf("\n Balance Tree");
			scanf("%d",&option);
			switch(option)
			{
				case 1:
						printf("\n enter value of node ");
						scanf("%d",&val);
						tree=insertele(tree,val);
						break;
						
				case 2:
						printf("\n element to delete :");
						scanf("%d",&val);
						tree=deleteele(tree,val);
						break;
				case 3:
						printf("\n Height is -----> %d",height(tree));
						break;
				case 4:
						printf("\n sum is------> %d",add(tree));
						break;
				case 5:
						printf("\n enter data to find inorder:  ");
						scanf("%d",&val);
						inorder(tree,val);
//						printf(" value----->%d",ptr->data);
						break;
				case 6:
						int val2;
						printf("\n enter data to chack lcs ");
						scanf("%d%d",&val,&val2);
						ptr=lca(tree,val,val2);
						printf("ans----------->%d",ptr->data);
						break;
				case 7:
						printf("\n enter value of node ");
						scanf("%d",&val);
						tree2=inst2(tree2,val);
						break;
				case 8:
						val=check(tree,tree2);
						if(val==1)
						printf("\n\nsame\n\n");
						else
						printf("\n\n not same\n\n");
						break;
				case 9:
						val =sumtree(tree);
						if(val==1)
						printf("\n\nYes....\n\n");
						else
						printf("\n\n No......\n\n");
						break;
				case 10:
					    ptr=find(tree,15);
						val=traverse(tree,ptr);
						break;
				case 11:
						val=diameter(tree);
						printf("Diameter is------>%d",val);
						break;
				case 12:
						if(balance(tree))
						printf("\n\ntree is balance\n\n");
						else
						printf("\n\ntree is not balance\n\n");
						}			
	}while(option!=0);
	return 0;
}
