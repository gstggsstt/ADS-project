#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>

using namespace std;

#define Debug
#define DEFAULT_MAXN 1000

template<typename _tp,int MAXN=DEFAULT_MAXN>
class BST
{
	private:
		class BST_node
		{
			friend class BST;
			private:
				_tp val;
				BST_node *l,*r;
			public:
				BST_node():val() { l=r=NULL; }
				BST_node(const _tp & x) { val=x; l=r=NULL; }
		};

		typedef BST_node node;

		node *U;
		node **Trash,*ALL;
		node *Root;
		int Top,size;

		node* ALLOC(const _tp & x)
		{ size++; return new(Top?Trash[Top--]:ALL++)node(x); }
		
		void RECYCLE(node *& t)
		{ size--; if(!t) return ; Trash[++Top]=t; return ; }

		void Insert(node *& t,const _tp & x)
		{
			if(!t) { t=ALLOC(x); return ; }
			if(x==t->val) return ;
			if(x<t->val) Insert(t->l,x);
			else Insert(t->r,x);
			return ;
		}

		node * Find(node * t,const _tp & x)
		{
			while(t && x!=t->val)
			{
				if(x < t->val) t=t->l;
				else if(x > t->val) t=t->r;
			}
			return t;
		}

		node * Find_Max(node * t)
		{ while(t && t->r) t=t->r; return t; }
		node * Find_Min(node * t)
		{ while(t && t->l) t=t->l; return t; }


		void Delete(node *& t,const _tp & x)
		{
			if(!t) { return ; }
			if(x==t->val)
			{
				node * tempnd;
				if(!t->l && !t->r) RECYCLE(t),t=NULL;
				else if(t->l && !t->r) RECYCLE(t),t=t->l;
				else if(t->r && !t->l) RECYCLE(t),t=t->r;
				else
				{
						tempnd=Find_Min(t->r);
						t->val=tempnd->val;
						Delete(t->r,t->val);
				}
			}
			else
			{
				if(x<t->val) Delete(t->l,x);
				else Delete(t->r,x);
			}
		}

	protected:
		node * Find_greater(node * t, _tp x)
		{
			node * temp=0;
			while(t)
			{
				if(x<t->val) temp=t,t=t->l;
				else t=t->r;
			}
			return temp;
		}

		node * Find_less(node * t, _tp x)
		{
			node * temp=0;
			while(t)
			{
				if(x<=t->val) t=t->l;
				else temp=t,t=t->r;
			}
			return temp;
		}

		void To_vector(node * t, std::vector<_tp> & vec)
		{
			if(!t) return ;
			To_vector(t->l,vec);
			vec.push_back(t->val);
			To_vector(t->r,vec);
		}

	public:
#ifdef Debug
		void Show_tree() { P(Root); }
		void P(node *t) { cout << "***************" << endl; _P(t);
			cout << "***************" << endl; cout << endl; }
		void _P(node * t)
		{
			if(!t) return ;
			if(t->l) {cout<<t->val<<" --L-- >"<<t->l->val<<endl;_P(t->l);}
			if(t->r) {cout<<t->val<<" --R-- >"<<t->r->val<<endl;_P(t->r);}
		}
#endif
		BST()
		{
			U=new node[MAXN];
			Trash=new node*[MAXN];
			memset(U,0,sizeof(_tp)*MAXN);
			ALL=U; Top=0; Root=0; size=0;
		}
		~BST()
		{
			delete[] U;
			delete[] Trash;
		}

		void Insert(const _tp & x) { Insert(Root,x); }
		bool Find(const _tp & x) { return Find(Root,x); }
		void Delete(const _tp & x) { Delete(Root,x); }
		int Size() { return size; }
		bool Empty() { return size==0; }

		_tp Find_less(const _tp & x)
		{
			node * temp=Find_less(Root,x);
			if(size) return temp?temp->val:Find_Min(Root)->val;
			return _tp();
		}
		_tp Find_greater(const _tp & x)
		{
			node * temp=Find_greater(Root,x);
			if(size) return temp?temp->val:Find_Max(Root)->val;
			return _tp();
		}
		std::vector<_tp> To_vector()
		{
			std::vector<_tp> vec;
			To_vector(Root,vec);
			return vec;
		}
};

int main()
{
	BST<int,1000000> T;

	int n,x;
	char op[10];
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s",op);
		scanf("%d",&x);
		if(op[0]=='i')
		{
			T.Insert(x);
			printf("%d\n",T.Size());
		}
		else if(op[0]=='d')
		{
			T.Delete(x);
			printf("%d\n",T.Size());
		}
		else if(op[0]=='f')
			printf(T.Find(x)?"True\n":"False\n");
		else if(op[0]=='l')
			printf("%d\n",T.Find_less(x));
		else if(op[0]=='g')
			printf("%d\n",T.Find_greater(x));
		//T.Show_tree();
	}

	vector<int> vec=T.To_vector();
	for(auto it=vec.begin();it!=vec.end();++it)
		printf("%d ",*it);
	printf("\n");

	return 0;
}
