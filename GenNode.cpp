/******************************************************************************
 ***** File Name : GenNode.cpp
 **** Created By : kyaz758
 *** Description :
 * Creation Date : 2016-09-23
 * Last Modified : 2016-11-23 22:16
 ******************************************************************************/

#include<iostream>
#include <malloc.h> // malloc 
#include <string.h> // memset
#include <stdlib.h> // exit
#include <stdio.h>
using namespace std;


typedef enum { HEAD = 0, INT, CHAR, LIST } NodeType;
struct GenNode;
typedef union
{
	int ref;        // HEAD;
	int intinfo;    // INT
	char chinfo;    // CHAR;
	GenNode *hlink; // LIST;
}ElemType;
struct GenNode
{
	NodeType utype; // HEAD INT CHAR LIST;
	ElemType value; // 
	GenNode *tlink;
};

class GenList
{
private:
	GenNode *first;
	static GenNode * _Buynode()
	{
		GenNode *s = (GenNode *)malloc(sizeof(GenNode));
		if (NULL == s) exit(1);
		memset(s, 0, sizeof(GenNode));
		return s;
	}
	static void _Freenode(GenNode *p)
	{
		free(p);
	}
	static GenNode * _BuyGenNode(NodeType utype, ElemType x)
	{
		GenNode *s = _Buynode();
		s->utype = utype;
		s->value = x;
		s->tlink = NULL;
		return s;
	}
	static void Print(GenNode *head)
	{
		GenNode *p = head->tlink;
		printf("(");
		while (p != NULL)
		{
			if (p->utype == INT)
			{
				printf("%d ,", p->value.intinfo);
			}
			else if (p->utype == CHAR)
			{
				printf("'%c', ", p->value.chinfo);
			}
			else
			{
				Print(p->value.hlink);
			}
			p = p->tlink;
		}
		printf(")");
	}
	static void Del_StrLR_Parentheses(char *sub, char *str)
	{
		int len = strlen(str);
		strncpy(sub, str + 1, len - 2);
		sub[len - 2] = '\0';
	}
	static bool serve(char *hsub, char *sub)
	{
		int len = strlen(sub);
		int i = 0;
		int tag = 0;
		while (i<len)
		{
			if (sub[i] == '(') ++tag;
			if (sub[i] == ')') --tag;
			if (tag == 0 && sub[i] == ',')
				break;
			++i;
		}
		if (tag != 0)
			return false;
		if (i == len)
		{
			strcpy(hsub, sub);
			sub[0] = '\0';
		}
		else
		{
			strncpy(hsub, sub, i);
			hsub[i] = '\0';
			strcpy(sub, sub + i + 1);
		}
		return true;
	}

	static GenNode * Create(char *str)
	{
		ElemType tmp;
		tmp.ref = 1;
		GenNode *s = _BuyGenNode(HEAD, tmp);
		if (strlen(str) > 0 && strcmp(str, "()") != 0)
		{
			GenNode *p = s;
			int len = strlen(str);
			char *sub = new char[len + 1];
			char *hsub = new char[len + 1];
			Del_StrLR_Parentheses(sub, str);
			while (strlen(sub) > 0)
			{
				if (!serve(hsub, sub)) exit(1);
				if (hsub[0] != '(' && hsub[0] != '\'')
				{
					tmp.intinfo = atoi(hsub);
					p = p->tlink = _BuyGenNode(INT, tmp);
				}
				else if (hsub[0] != '(' && hsub[0] == '\'')
				{
					tmp.chinfo = hsub[1];
					p = p->tlink = _BuyGenNode(CHAR, tmp);
				}
				else
				{
					tmp.hlink = Create(hsub);
					p = p->tlink = _BuyGenNode(LIST, tmp);
				}
			}
			delete[]sub;
			delete[]hsub;
		}
		return s;
	}
	static void Clear(GenNode *p)
	{
		while (p != NULL)
		{
			GenNode *q = p;
			p = p->tlink;
			if (q->utype == LIST)
			{
				Clear(q->value.hlink);
			}
			_Freenode(q);
		}
	}
	static bool equal(GenNode *p, GenNode *q)
	{
		if (p->value.intinfo == q->value.intinfo && p->utype == q->utype)
		{
			if (p->tlink == NULL && q->tlink == NULL)
			{
				return true;
			}
			else
			{
				equal(p->tlink, q->tlink);
			}
		}
		if (p->utype == LIST && q->utype == LIST)
		{
			equal(p->value.hlink, q->value.hlink);
		}
		else return false;
	}
public:
	GenList() :first(NULL) {}
	static GenNode * Copy(GenNode *ptr)
	{
	}
	GenList(const GenList &g)
	{
		first = Copy(g.first);
	}
	GenList & operator=(const GenList &g)
	{
		if (this != &g)
		{
			Clear();
			first = Copy(g.first);
		}
		return *this;
	}
	~GenList()
	{
		Clear();
	}
	bool GetSub(GenList &g) 
	{
		GenNode *p = first;
		//GenNode *q = g;
		while (p != NULL)
		{
			if (p->utype == LIST)
			{
				return equal(p, g.first);
			}
			else
			{
				p = p->tlink;
			}
		}
	}
	bool operator==(const GenList &g) const
	{
		return equal(first, g.first);
	}

	static int depth(GenNode *ptr)
	{
		int max = 0;
		if (ptr != NULL)
		{
			GenNode *p = ptr->tlink;
			while (p != NULL)
			{
				if (p->utype == LIST)
				{
					int tx = depth(p->value.hlink);
					if (tx > max)
					{
						max = tx;
					}
				}
				p = p->tlink;
			}
		}
		return max + 1;
	}
	int depth() const
	{
		if (first == NULL) return 0;
		else return depth(first);
	}
	int size() const
	{
		int num = 0;
		if (first != NULL)
		{
			GenNode *p = first->tlink;
			while (p != NULL)
			{
				num += 1;
				p = p->tlink;
			}
		}
		return num;
	}
	void Clear()
	{
		Clear(first);
		first = NULL;
	}
	void CreateList(char *str)
	{
		if (str != NULL)
		{
			first = Create(str);
		}
	}
	void Print_GenList() const
	{
		if (first != NULL)
		{
			printf("\"");
			Print(first);
			printf("\"");
		}
		printf("\n");
	}
};


int main()
{
	GenList myg, youg, gg;
	char *s1 = NULL;
	char *s2 = "()";
	char *s3 = "(12,('a',23),'x')";
	char *s4 = "(12,'x',(23,'y',(34,'z'),'r'),56,(12,'z'),'a')";
	char *s5 = "(12,'x',(23,'y',(34,'z'),'r'),56,(34,'z'),'a')";
	myg.CreateList(s4);
	youg.CreateList(s3);
	myg.GetSub(youg);

	cout << (myg == youg) << endl;
	//gg.Print_GenList();
    return 0;
}
