/******************************************************************************
 ***** File Name : BSTree.cpp
 **** Created By : kyaz758
 *** Description :
 * Creation Date : 2016-10-21
 * Last Modified : 2016-11-21 23:24
 ******************************************************************************/

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

#define END -1
typedef int KeyType;
typedef struct _BstNode
{
	KeyType key;
	struct _BstNode *leftChild;
	struct _BstNode *rightChild;
	struct _BstNode *parent;
}BstNode, *BSTree;

BstNode *_BuyNode()
{
	BstNode *s = (BstNode *)malloc(sizeof(BstNode));
	if (s == NULL)	
		exit(-1);
	memset(s, 0, sizeof(BstNode));
	return s;
}

bool Insert_BST(BSTree *ptree,KeyType kx)
{
	if(ptree == NULL) return false;
	BstNode *p = *ptree, *pa = NULL;
	while(p != NULL && p->key != kx)
	{
		pa = p;
		p = kx < p->key? p->leftChild:p->rightChild;
	}
	if(p != NULL) return false;
	p = _BuyNode();
	p->key = kx;
	p->parent = pa;
	p->leftChild = p->rightChild = NULL;
	if(pa == NULL)
	{
		*ptree = p;
	}else
	{
		if(p->key < pa->key)
		{
			pa->leftChild = p;
		}
		else
		{
			pa->rightChild = p;
		}
	}
	return true;
}

BstNode *FindValue(BstNode *ptr, KeyType kx)
{
	if (ptr == NULL || kx == END)
		return NULL;
	else 
	{
		BstNode *p = ptr;
		while (p!=NULL && p->key!=kx)
			p = p->key>kx?p=p->leftChild:p=p->rightChild;
		return p;
	}
}

BstNode *Search(BstNode *ptr, KeyType kx)
{
	if (ptr==NULL || ptr->key==kx)
		return ptr;
	else
	{
		if (ptr->key > kx)
			return Search(ptr->leftChild, kx);
		else return Search(ptr->rightChild, kx);
	}
}
BstNode *SearchValue(BstNode *ptr, KeyType kx)
{
	if (kx == END)
		return NULL;
	else return Search(ptr, kx);
}

BstNode *First(BstNode *ptr)
{
	while (ptr!=NULL && ptr->leftChild!=NULL)
		ptr = ptr->leftChild;
	return ptr;
}
BstNode *Next(BstNode *p)
{
    if (p == NULL) 
	  return p;
	if (p->rightChild != NULL)
		return First(p->rightChild);
	else
	{
		if (p->key < p->parent->key)
			return p->parent;
		else
		{
			BstNode *pa = p->parent;
			while (pa!=NULL && pa->key<p->key)
				pa = pa->parent;
			return pa;
		}
	}
	
}
void NiceInOrder(BstNode *ptr)
{
	if (ptr == NULL) return ;
	for (BstNode *p=First(ptr); p!=NULL; p=Next(p))
		cout<<p->key<<" ";
	cout<<endl;
}

BstNode *Last(BstNode *ptr)
{
	while (ptr!=NULL && ptr->rightChild!=NULL)
		ptr = ptr->rightChild;
	return ptr;
}
BstNode *Prev(BstNode *p)
{
	if (p == NULL) 
		return p;
	if (p->leftChild != NULL)
		return Last(p->leftChild);
	else
	{
		if (p->key > p->parent->key)
		{
			return p->parent;
		}
		else
		{
			BstNode *pa = p->parent;
			while (pa!=NULL && pa->key > p->key)
				pa = pa->parent;
			return pa;
		}
	}
}
void ResNiceInOrder(BstNode *ptr)
{
	if (ptr == NULL) return ;
	for (BstNode *p=Last(ptr); p!=NULL; p=Prev(p))
		cout<<p->key<<" ";
	cout<<endl;
}

void _FreeNode(BstNode *p)
{
	free(p);
}
bool Remove_BST(BSTree *ptree, KeyType kx)
{
		if (ptree==NULL || *ptree==NULL)
			return false;
		BstNode *p = *ptree, *pa = NULL;
		while(p!=NULL && p->key!=kx)
		{
			pa = p;
			p = kx<p->key?p->leftChild:p->rightChild;
		}
		if (p == NULL) 
			return false;
		if (p->leftChild!=NULL && p->rightChild!=NULL)
		{
			BstNode *s = Next(p);
			p->key = s->key;
			pa = s->parent;
			p = s;
		}
		BstNode *child = p->leftChild!=NULL?p->leftChild:p->rightChild;
		if (child != NULL)
			child->parent = pa;
		if (pa == NULL)
			*ptree = child;
		else
		{
			if (pa->leftChild == p)
				 pa->leftChild = child;
			else
				 pa->rightChild = child;
		}
		_FreeNode(p);
		return true;
}

void InOrder(BstNode *p)
{
	if(p != NULL)
	{
		InOrder(p->leftChild);
		cout<<p->key<<" ";
		InOrder(p->rightChild);
	}
}

 
int main()
{
	BSTree root = NULL;
	int x;
	int ar[]={53,17,78,9,45,65,87,23,81,94,88,100,17,9};
	int n = sizeof(ar)/sizeof(ar[0]);

	for(int i = 0;i<n;++i)
	{
		cout<<Insert_BST(&root,ar[i]);
	}
	cout<<endl;
	InOrder(root);
	cout<<endl;
	NiceInOrder(root);
	ResNiceInOrder(root);
	while(cin>>x, x != -1)
	{
		cout<<Remove_BST(&root,x)<<endl;
		InOrder(root);
		cout<<endl;
	}
	return 0;
}
