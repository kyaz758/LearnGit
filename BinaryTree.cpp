#include <iostream>
using namespace std;

template<class Type>
class BinaryTree
{
private:
	struct BtNode
	{
		BtNode *leftChild;
		BtNode *rightChild;
		Type data;
	};
	BtNode *root;
	Type refValue;
private:
	static BtNode *_BuyNode()
	{
		BtNode *s = new BtNode;
		if (s == NULL) exit(-1);
		memset(s, 0, sizeof(BtNode));
		return s;
	}
	static void _FreeNode(BtNode *p)
	{
		delete p;
	}
	static BtNode *Create(Type *&str)
	{
		BtNode *s = NULL;
		if (*str != refValue)
		{
			s = _BuyNode();
			s->data = *str;
			s->leftChild = Create(++str);
			s->rightChild = Create(++str);
		}
		return s;
	}
	static void PreOrder(BtNode *ptr)
	{
		if (ptr != NULL)
		{
			cout<<ptr->data<<" ";
			PreOrder(ptr->leftChild);
			PreOrder(ptr->rightChild);
		}
	}
	static void InOrder(BtNode *ptr)
	{
		if (ptr != NULL)
		{
			InOrder(ptr->leftChild);
			cout<<ptr->data<<" ";
			InOrder(ptr->rightChild);
		}
	}
	static void PastOrder(BtNode *ptr)
	{
		if (ptr != NULL)
		{
			PastOrder(ptr->leftChild);
			PastOrder(ptr->rightChild);
			cout<<ptr->data<<" ";
		}
	}
	static void Destroy(BtNode *ptr)
	{
		if (ptr != NULL)
		{
			Destroy(ptr->leftChild);
			Destroy(ptr->rightChild);
			_FreeNode(ptr);
		}
	}

	static BtNode *FindV(BtNode *ptr, const Type &x)
	{
		if (ptr == NULL || ptr->data == x)
		{
			return ptr;
		}
		else
		{
			BtNode *s = Find(ptr->leftChild);
			if (s == NULL)
			{
				s = Find(ptr->rightChild);
			}
			return s;
		}
	}
	//static FindP(BtNode *ptr, BtNode *child)
	//{
	//	if (ptr == NULL
	static int Count(BtNode *ptr)
	{
        int num;
		if (ptr != NULL)
		{
			num = Count(ptr->leftChild)+Count(ptr->rightChild)+1;
		}
		return num;
	}
	static int Deep(BtNode *ptr)
	{
		if (ptr != NULL)
		{
			int leftDep = depth(ptr->leftChild);
			int rightDep = depth(ptr->rightChild);
			int deep = dleftDep>rightDep?leftDep+1:rightDep+1;
		}
		return deep;
	}
	static void Copy(BtNode *ptr ,BtNode *str)
	{
		if (str == NULL)
		{
			ptr == NULL;
		}
		else 
		{  
			if (ptr == NULL)
			{
				ptr = _BuyNode();
			}
			ptr->data = str->data;
			if (str->leftChild != NULL)
			{
				Copy(ptr->leftChild, str->leftChild);
			}
			if (str->rightChild != NULL)
			{
				Copy(ptr->rightChild, str->rightChild);
			}
		}
	}
	
	bool Equal(BtNode *ptr, BtNode *str)
	{
		bool res = false;
		if (ptr==NULL && str==NULL)
		{
			return true;
		}
		if (ptr != NULL && str != NULL)
		{
			if (ptr->data == str->data)
			{
				res = Equal(ptr->leftChild, str->leftChild) 
				&& Equal(ptr->rightChild, str->rightChild);
			}
			else return res;
		}
		else return res;
	}		

public:
	typedef BtNode * PBtNode;
	BinaryTree(const Type &x):root(NULL),refValue(x) {}

	/*
		函数名称：BinaryTree
		函数作用：拷贝构造，构造与传入二叉树相同的二叉树
		传入参数：const Type &x
		返回结果：NULL
	*/
	BinaryTree(const BinaryTree<Type> &bt)
	{
		Copy(root, bt.root);
		return *this;
	}

	/*
		函数名称：operator=
		函数作用：赋值运算符重载，将传入二叉树的所有拷贝给本二叉树
		传入参数：const BinaryTree &bt
		返回结果：NULL
	*/
	BinaryTree<Type> &operator=(const BinaryTree<Type> &bt)
	{
		Copy(root, bt.root);
		return *this;
	}

	~BinaryTree()
	{
		Clear();
	}
	void Clear()
	{
		Destroy(root);
		root = NULL;
	}
	void CreateTree(Type *str)
	{
		if (str != NULL)
		{
			root = Create(str);
		}
	}
	void PreOrder() const
	{
		PreOrder(root);
		cout<<endl;
	}
	void InOrder() const
	{
		InOrder(root);
		cout<<endl;
	}
	void PastOrder() const
	{
		PastOrder(root);
		cout<<endl;
	}
	
	/*
		函数名称：FindValue
		函数作用：寻找并返回与传入参数值相等的节点
		传入参数：const Type &x
		返回结果：BtNode *
	*/
	BtNode *FindValue(const Type &x) const
	{
		return FindV(root, x);
	}
	
	/*
		函数名称：FindParent
		函数作用：寻找并返回与传入二叉树节点的双亲节点
		传入参数：const BtNode *child
		返回结果：BtNode *
	*/
	BtNode *FindParent(const BtNode *child) const
	{
		return FindP(root, child);
	}
	
	/*
		函数名称：Size
		函数作用：返回二叉树的节点个数
		传入参数：NULL
		返回结果：int
	*/
	int Size() const
	{
		return Count(root);
	}

	/*
		函数名称：Depth
		函数作用：返回二叉树的深度
		传入参数：NULL
		返回结果：int 
	*/
	int Depth() const
	{
		return Deep(root);
	}

	/*
		函数名称：operator==
		函数作用：判断传入的二叉树与本二叉树是否相等
		传入参数：const BinaryTree &bt
		返回结果：bool
	*/
	bool operator==(const BinaryTree<Type> &bt) const
	{
		return Equal(root, bt.root);
	}

	/*
		函数名称：operator!=
		函数作用： 判断传入二叉树与本二叉树是否不相等
		传入参数：const BinaryTree &bt
		返回结果：bool
	*/
	bool operator!=(const BinaryTree<Type> &bt) const
	{
		return !(Equal(root, bt.root));
	}
};
//测试用例
int main()
{
	return 0;
}
