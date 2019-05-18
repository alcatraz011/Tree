// Create a binary tree and perform DFS (Preorder,Inorder,PostOrder)

#include<stdio.h>
#include<iostream>

struct treenode
{
  int data;
  struct treenode* left;
  struct treenode* right;
};

void insert(struct treenode**,int);
void preorder(struct treenode*);
void inorder(struct treenode*);
void postorder(struct treenode*);

using namespace std;

int main()
{
 
 int arr[]={7,4,9,2,6,8,10,15,13,1};
 
 struct treenode* tree;
 tree=NULL;
 
 for(int i=0;i<10;i++)
 {
 	insert(&tree,arr[i]);
 }
 
 cout<<"PreOrder ";
 preorder(tree);
 cout<<"\nInOrder ";
 inorder(tree);
 cout<<"\nPostOrder ";
 postorder(tree);
 	
 return 0;
}

void insert(struct treenode** sr, int data)
{
  // cout<<data<<endl;
  if((*sr)==NULL)
   {
   	(*sr)=(struct treenode*)malloc(sizeof(struct treenode));
   	(*sr)->data=data;
   	(*sr)->left=NULL;
   	(*sr)->right=NULL;
//   	cout<<"data\n";
   }
   
   else if(data<(*sr)->data)
   {
//    cout<<"left\n";
    insert(&(*sr)->left,data);
   }
   else
   {
//   	cout<<"right\n";
    insert(&(*sr)->right,data);	
   }
}

void preorder(struct treenode* sr)
{
//	cout<<"preorder";
	if(sr!=NULL)
	{	  
	  cout<<sr->data<<" ";
	  
	  preorder(sr->left);
	  
	  preorder(sr->right);
	}	

}


void inorder(struct treenode* sr)
{
//	cout<<"inorder";
	
	if(sr!=NULL)
	{
	  inorder(sr->left);
	  
	  cout<<sr->data<<" ";
	  
	  inorder(sr->right);
	}
}

void postorder(struct treenode* sr)
{
//	cout<<"postorder";
	if(sr!=NULL)
	{
	  postorder(sr->left);
	  
	  postorder(sr->right);
	  
	  cout<<sr->data<<" ";
	}	

}







