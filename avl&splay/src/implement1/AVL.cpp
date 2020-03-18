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
class AVL
{
	private:
		class AVL_node
		{
			friend class AVL;
			private:
				_tp val;
				AVL_node *l,*r;
				int h; // Height of tree
			public:
				AVL_node():val() { l=r=NULL; h=0; }
				AVL_node(const _tp & x) { val=x; l=r=NULL; h=0; }
		};

		typedef AVL_node node;

		node *U;
		node **Trash,*ALL;
		node *Root;
		int Top,size;

		// Create a new node with value x
		node* ALLOC(const _tp & x)
		{ size++; return new(Top?Trash[Top--]:ALL++)node(x); }
		
		// Recycle a node in the tree
		void RECYCLE(node *& t)
		{ size--; if(!t) return ; Trash[++Top]=t; return ; }

		int AVL_abs(const int x) { return x>=0?x:-x; }

		// In case of accessing NULL
		int geth(node * t) { return t?t->h:0; }

		// Left-Rotate
		void RotateL(node *& t)
		{
			node *temp=t->r;
			t->r=temp->l;
			temp->l=t; t=temp;
			t->l->h=max(geth(t->l->l),geth(t->l->r))+1;
			t->h=max(geth(t->l),geth(t->r))+1;
			return ;
		}

		// Right-Rotate
		void RotateR(node *& t)
		{
			node *temp=t->l;
			t->l=temp->r;
			temp->r=t; t=temp;
			t->r->h=max(geth(t->r->l),geth(t->r->r))+1;
			t->h=max(geth(t->l),geth(t->r))+1;
			return ;
		}

		// Fix Height after insert or delete
		void update_node(node *& t)
		{
			// Update height
			t->h=max(geth(t->l),geth(t->r))+1;
			// Unbalanced
			if(AVL_abs(geth(t->l) - geth(t->r)) >  1)
			{
				if(geth(t->l) > geth(t->r))
					if(geth(t->l->l) > geth(t->l->r)) RotateR(t);
					else RotateL(t->l), RotateR(t);
				else 
					if(geth(t->r->l) < geth(t->r->r)) RotateL(t);
					else RotateR(t->r), RotateL(t);
			}
		}

		void Insert(node *& t,const _tp & x)
		{
			if(!t) { t=ALLOC(x); t->h=1; return ; }
			if(x==t->val) return ;
			if(x<t->val) Insert(t->l,x);
			else Insert(t->r,x);
			update_node(t);
			return ;
		}

		node * Find(node * t,const _tp & x)
		{
			while(t && x!=t->val)
				if(x < t->val) t=t->l;
				else if(x > t->val) t=t->r;
			return t;
		}

		node * Find_Max(node * t)
		{ while(t && t->r) t=t->r; return t; }
		node * Find_Min(node * t)
		{ while(t && t->l) t=t->l; return t; }


		void Delete(node *& t,const _tp & x)
		{
			if(!t) { return ; }
			// Found x, delete it
			if(x==t->val)
				if(!t->l && !t->r) RECYCLE(t),t=NULL;
				else if(t->l && !t->r) RECYCLE(t),t=t->l;
				else if(t->r && !t->l) RECYCLE(t),t=t->r;
				// replace t with min node 'P' in left subtree
				//   or max node 'P' in right subtree
				// Delete 'P' recursively
				else
					if(geth(t->l) > geth(t->r))
						t->val=Find_Max(t->l)->val,
						Delete(t->l,t->val);
					else 
						t->val=Find_Min(t->r)->val,
						Delete(t->r,t->val);
			else if(x<t->val) Delete(t->l,x);
			else              Delete(t->r,x);

			// keep balance
			if(t) update_node(t);
			return ;
		}

	protected:
		node * Find_greater(node * t, _tp x)
		{
			node * temp=0;
			while(t)
				if(x<t->val) temp=t,t=t->l;
				else t=t->r;
			return temp;
		}

		node * Find_less(node * t, _tp x)
		{
			node * temp=0;
			while(t)
				if(x<=t->val) t=t->l;
				else temp=t,t=t->r;
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
		AVL()
		{
			U=new node[MAXN];
			Trash=new node*[MAXN];
			memset(U,0,sizeof(_tp)*MAXN);
			ALL=U; Top=0; Root=0; size=0;
		}
		~AVL()
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
			// if empty tree, return _tp()
			// if x<Min return Min
		{
			node * temp=Find_less(Root,x);
			if(size) return temp?temp->val:Find_Min(Root)->val;
			return _tp();
		}
		_tp Find_greater(const _tp & x)
			// if empty tree, return _tp()
			// if x>Max return Max
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
	AVL<int,1000000> T;

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
