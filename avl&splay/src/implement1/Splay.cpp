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
class Splay
{
	private:
		class Splay_node
		{
			friend class Splay;
			private:
				_tp val;
				Splay_node *fa;
				Splay_node *s[2]; // s[0] left child; s[1] right child
				inline bool getlr() { return fa->s[1]==this; }
				Splay_node * link(const int w, Splay_node * t)
					// link t to s[w]
				{ if((s[w]=t)) t->fa=this; return this; }
			public:
				Splay_node():val() { s[0]=s[1]=fa=NULL; }
				Splay_node(const _tp & x) { val=x; s[0]=s[1]=fa=NULL; }
		};

		typedef Splay_node node;

		node *U,*MinNode,*MaxNode;
		node **Trash,*ALL;
		node *Root;
		int Top,size;

		node* ALLOC(const _tp & x)
		{ size++; return new(Top?Trash[Top--]:ALL++)node(x); }
		
		void RECYCLE(node *& t)
		{ size--; if(!t) return ; Trash[++Top]=t; return ; }

		void Rotate(node * t) // rotate up, height(t) reduces
		{
			node * gfa=t->fa->fa;
			// t is right node of t->fa, rotateL
			t->getlr()?t->link(0,t->fa->link(1,t->s[0])):
			// t is left node of t->fa, rotateR
				t->link(1,t->fa->link(0,t->s[1]));
			// fix pointers
			if(gfa) gfa->link(gfa->s[1]==t->fa,t);
			else t->fa=0,Root=t;
		}

		// rotate t up until t->fa==NULL
		// splay(t) means rotate t to root
		node * splay(node * t,node * tar=NULL)
		{
			// double rotate
			while(t->fa!=tar && t->fa->fa!=tar)
				t->getlr()==t->fa->getlr()?
				// same direction
				(Rotate(t->fa),Rotate(t)):
				// differnt direction
				(Rotate(t),    Rotate(t));
			// no grandfather node, sigle rotate
			if(t->fa!=tar) Rotate(t);
			return t;
		}

		void Insert(node *& t,const _tp & x)
		{
			if(Find(x)) return ;
			node * templ, * tempr, * tempx;
			templ=Find_less(Root,x); // precursor position
			tempr=Find_greater(Root,x); // subsequence position
			tempx=ALLOC(x); // newnode
			// insert to root->r-l
			if(templ && tempr)       splay(tempr,splay(templ))->link(0,tempx);
			// x is max
			else if(templ && !tempr) Root=tempx->link(0,splay(templ));
			// x is min
			else if(!templ && tempr) Root=tempx->link(1,splay(tempr));
			// empty tree
			else                     Root=tempx;
		}

		node * Find(node * t,const _tp & x)
		{
			node * last=0;
			while(t && x!=t->val)
			{
				last=t;
				if(x < t->val) t=t->s[0];
				else if(x > t->val) t=t->s[1];
			}
			if(t) splay(t);
			// splay a node no matter x is found or not
			//   if not do so, complexity of Find(x) BOOMBOOM!
			else if(last) splay(last);
			return t;
		}

		node * Find_Max(node * t)
		{ while(t && t->s[1]) t=t->s[1]; return t; }
		node * Find_Min(node * t)
		{ while(t && t->s[0]) t=t->s[0]; return t; }


		void Delete(node *& t,const _tp & x)
		{
			node * tempx, * templ, * tempr;
			tempx=Find(Root,x); // find x
			if(!tempx) return ; // if no such node, return 
			templ=Find_less(Root,x); // precursor position
			tempr=Find_greater(Root,x); // subsequence position
			// delete root->r->l
			if(templ && tempr)       splay(tempr,splay(templ))->s[0]=0;
			// x is max
			else if(templ && !tempr) splay(templ)->s[1]=0;
			// x is min
			else if(!templ && tempr) splay(tempr)->s[0]=0;
			// empty tree
			else                     Root=0;
			RECYCLE(tempx); // recycle memory
		}

	protected:
		node * Find_greater(node * t, _tp x)
		{
			node * temp=0, * last=0;
			while(t)
			{
				last=t;
				if(x<t->val) temp=t,t=t->s[0];
				else t=t->s[1];
			}
			if(temp) splay(temp);
			else if(last) splay(last);
			return temp;
		}

		node * Find_less(node * t, _tp x)
		{
			node * temp=0, * last=0;
			while(t)
			{
				last=t;
				if(x<=t->val) t=t->s[0];
				else temp=t,t=t->s[1];
			}
			if(temp) splay(temp);
			else if(last) splay(last);
			return temp;
		}

		void To_vector(node * t, std::vector<_tp> & vec)
			// In order to avoid recursion, this function is O(NlogN)
		{
			if(!t) return ;
			_tp temp=Find_Min(Root)->val;
			for(int i=0;i<size;++i)
				vec.push_back(temp),temp=Find_greater(temp);
		}

	public:
#ifdef Debug
		void Show_tree() { P(Root); }
		void P(node *t) { cout << "***************" << endl; _P(t);
			cout << "***************" << endl; cout << endl; }
		void _P(node * t)
		{
			if(!t) return ;
			if(t->s[0]) {cout<<t->val<<" --L-- >"<<t->s[0]->val<<endl;_P(t->s[0]);}
			if(t->s[1]) {cout<<t->val<<" --R-- >"<<t->s[1]->val<<endl;_P(t->s[1]);}
		}
#endif
		Splay()
		{
			U=new node[MAXN];
			Trash=new node*[MAXN];
			memset(U,0,sizeof(_tp)*MAXN);
			ALL=U; Top=0; Root=0; size=0;
		}
		~Splay()
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
	Splay<int,1000000> T;

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
