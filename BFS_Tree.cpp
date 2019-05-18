// Create a binary tree and perform BFS(Level Order Traversal)

#include<stdio.h>
#include<iostream>

struct treenode
{
  int data;
  struct treenode* left;
  struct treenode* right;
};

void insert(struct treenode**,int);
int findHeight(struct treenode*);
void bfs(struct treenode*);
void printLevel(struct treenode*, int);

using namespace std;

int main()
{
 
 int arr[]={40,20,10,30,50,60};
 
 struct treenode* tree;
 tree=NULL;
 
 for(int i=0;i<6;i++)
 {
 	insert(&tree,arr[i]);
 }
 
 bfs(tree);

 return 0;
}

void bfs(struct treenode* sr)
{
 int h=findHeight(sr);
 cout<<"Height "<<h<<"\n\n";
 
 for(int i=1;i<=h;i++)
 {
  printLevel(sr,i);
  cout<<endl;
  }
	
}

void printLevel(struct treenode* sr, int h)
{
  if(sr==NULL)
   return;
  else if(h==1)
  {
   cout<<sr->data<<" ";
//   return;
  }
  else if(h>1)
  {
  	printLevel(sr->left,h-1);
  	printLevel(sr->right,h-1);
  }
   	
}


int findHeight(struct treenode* sr)
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
