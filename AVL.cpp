// AVL tree implementation 
// AVL should self balance if any element gets deleted

#include<stdio.h>
#include<iostream>

using namespace std;

struct node
{
  int data;
  int height;
  struct node* left;
  struct node* right;
};

struct node* insert(struct node*,int);
struct node* rightRotate(struct node*);
struct node* leftRotate(struct node*);
int max(int,int);
int height(struct node*);
int findHeight(struct node*);
void bfs(struct node*);
void printLevel(struct node*, int);
void deleteNode(struct node**,int);
void search(struct node**,int,struct node**,struct node**,int*);
struct node* balance(struct node*,int);

int main()
{
 struct node* root=NULL;
 
 //int arr[]={10,20,30,40,50,60};
 int arr[]={30,20,10,5,1,15,25,40,35,50,60};
 for(int i=0;i<11;i++)
 {
  root=insert(root,arr[i]);
 // bfs(root);
  }

 bfs(root);
 cout<<"Node deleted\n";
 deleteNode(&root,35);
 
 bfs(root);
 return 0;
}


struct node* insert(struct node* node, int data)
{
   //cout<<"insert\n";
   if(node==NULL)
   {
   	 //cout<<"newNode\n";
     node=(struct node*)malloc(sizeof(struct node));
     node->data=data;
     node->left=NULL;
     node->right=NULL;
     node->height=1;
     return(node);
   }
	
	if(data<node->data)
	 node->left=insert(node->left,data);
	else if (data>node->data)
	{
	 node->right=insert(node->right,data);
    }
	else
	 return node;
	 
	node->height=1+max(height(node->left),height(node->right));	
	
	int balance=(height(node->left)- height(node->right));
	
	if (balance>1 && data<node->left->data)
	 return(rightRotate(node));
	else if (balance<-1 && data>node->right->data)
	 return(leftRotate(node));
	else if(balance>1 && data>node->left->data)
	{
	 node->left=leftRotate(node->left);
	 return(rightRotate(node));
	}
	else if(balance<-1 && data<node->right->data)
	{
	 node->right=rightRotate(node->right);
	 return(leftRotate(node)); 
	}  

return(node);	
	
}

struct node* rightRotate(struct node* node)
{
	//cout<<"Right\n";
	struct node* x=node->left;
	struct node* temp=x->right;
	
	x->right=node;
	node->left=temp;
	
	node->height=1+max(height(node->left),height(node->right));
	x->height=1+max(height(x->left),height(x->right));
	
	return x;
}

struct node* leftRotate(struct node* node)
{
	cout<<"Left\n";
	struct node* x=node->right;
	struct node* temp=x->left;
	
	x->left=node;
	node->right=temp;
	
	node->height=1+max(height(node->left),height(node->right));
	x->height=1+max(height(x->left),height(x->right));
	
	return x;
}


int max(int a, int b)
{
  return(a>b?a:b);
}

int height(struct node* node)
{
 if(node==NULL)
  return 0;
 return(node->height);	
}

void bfs(struct node* sr)
{
 int h=findHeight(sr);
// cout<<"Height "<<h<<"\n\n";
 
 for(int i=1;i<=h;i++)
 {
  printLevel(sr,i);
  cout<<endl;
  }
	
}

void printLevel(struct node* sr, int h)
{
  if(sr==NULL)
   return;
  else if(h==1)
   cout<<sr->data<<" ";
  else if(h>1)
  {
  	printLevel(sr->left,h-1);
  	printLevel(sr->right,h-1);
  }
   	
}


int findHeight(struct node* sr)
{
  if(sr==NULL)
   return 0;
  else
  {
  	int lheight=findHeight(sr->left);
  	int rheight=findHeight(sr->right);
  	
  	if(lheight>rheight)
  	 return(lheight+1);
  	else
  	 return(rheight+1);	 
  }
}


void deleteNode(struct node** sr, int num)
{
  int found;
  struct node *parent,*x,*xsucc;
  
  if(*sr==NULL)
   return;
   
  parent=x=NULL;
  
  search(sr,num,&parent,&x,&found);	
  
  if(found==0)
  {
  	printf("Not found");
  	return;
  }
  
  if(x->left!=NULL && x->right!=NULL)   //If node to be deleted has 2 children
  {
  	parent=x;
  	xsucc=x->right;
  	
  	while(xsucc->left!=NULL)
  	{
  	  parent=xsucc;
	  xsucc->left;	
	}
	
	x->data=xsucc->data;
	x=xsucc;	
  }                           //Two child node has been converted to 1 child
  
  
  if(x->left==NULL && x->right!=NULL)
  {
  	if(parent->left==x)
  	  parent->left=x->right;
  	else
  	 parent->right=x->right;
  	 
  	free(x);
  	x=balance(*sr,parent->data);
  	return;  	
  }
  
  if(x->left!=NULL && x->right==NULL)
  {
  	if(parent->left==x)
  	  parent->left=x->right;
  	else
  	 parent->right=x->right;
  	 
  	free(x);
  	x=balance(*sr,parent->data);
  	return;  	
  }
  
  
  if(x->left==NULL && x->right==NULL)
  {
  	if(parent->left==x)
  	  parent->left=NULL;
  	else
  	 parent->right=NULL;
  	 
  	free(x);
  	cout<<"balance called\n";
  	x=balance(*sr,parent->data);
  	return;  	
  }  
	
}

void search(struct node** sr,int num, struct node** parent,struct node** x, int *found)
{
 struct node *q;
 
 q=*sr;
 *found=0;
 *parent=NULL;
 
 while(q!=NULL)
 {
 	if(q->data==num)
 	{
 		*found=1;
 		*x=q;
 		return;
	 }
	 
	*parent=q;
	
	
	if(q->data > num)
	  q=q->left;
	else
	  q=q->right;	
	
 }
	
}

// First traverse till data and then recursively check till root whether all the nodes are balanced
struct node* balance(struct node* node,int data)   //Need re-work
{
	
	if(data<node->data)
	 node->left=balance(node->left,data);
	else if (data>node->data)
	 node->right=balance(node->right,data);
	else          //Node found
	{ cout<<"found\n";
	  node->height=1+max(height(node->left),height(node->right));	
	
	int balance=(height(node->left)- height(node->right));
	cout<<balance<<endl;
	if (balance>1 && data<node->left->data)
	 return(rightRotate(node));
	else if (balance<-1 && node->right->right->data>node->right->data)
	 return(leftRotate(node));
	else if(balance>1 && data>node->left->data)
	{
	 node->left=leftRotate(node->left);
	 return(rightRotate(node));
	}
	else if(balance<-1 && data<node->right->data)
	{
	 node->right=rightRotate(node->right);
	 return(leftRotate(node)); 
	}  
	
	  return node;	
	}
	 
	 
	node->height=1+max(height(node->left),height(node->right));	
	
	int balance=(height(node->left)- height(node->right));
	
	if (balance>1 && data<node->left->data)
	 return(rightRotate(node));
	else if (balance<-1 && data>node->right->data)
	 return(leftRotate(node));
	else if(balance>1 && data>node->left->data)
	{
	 node->left=leftRotate(node->left);
	 return(rightRotate(node));
	}
	else if(balance<-1 && data<node->right->data)
	{
	 node->right=rightRotate(node->right);
	 return(leftRotate(node)); 
	}  

return(node);
}







