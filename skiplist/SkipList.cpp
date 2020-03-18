#include <bits/stdc++.h>

using namespace std;

class SkipList
{
	// node of list
	class node
	{
		public:
		node * next;
		node * last;
		node * down;
		int val; // actual data
		node()
		{
			next=last=down=NULL;
			val=0;
		}
	};

	typedef node* List;

	//Max height of skiplist
#define MAX_RANK (20)

	//Skip list is stored line by line.
	//L[i] is the head of list of rank i.
	List L[MAX_RANK];

	//Random seed from system status.
	//  In linux, gernerate data from /dev/urandom 
	random_device seed;
	//Random gernerator MT19937.
	mt19937 RND;

	public:
		SkipList()
		{
			//Init random generator
			RND=mt19937(seed());

			//Init list head
			//  At the beginning, lists of each rank has two elements,
			//    INT_MAX and INT_MIN
			for(int i=0;i<MAX_RANK;++i)
			{
				L[i]=new node;
				L[i]->next=new node;
				L[i]->next->last=L[i];

				// node.down is the deeper node of the same value
				if(i) L[i]->down=L[i-1],
					L[i]->next->down=L[i-1]->next;

				L[i]->val=INT_MIN;
				L[i]->next->val=INT_MAX;
			}
		}

	protected:
		// get rank randomly
		int get_rank()
		{
			int k=0;
			while(RND()&1) k++;
			return min(MAX_RANK-1,k);
		}

		// start at node 't', finding value 'x', current rank is 'rank', 
		// 'vec' contains the result of all the nodes 
		//   after which we should insert 'x', in ascending order of rank
		void get_pos(node* t, int x, int rank, int threshold, vector<node *>& vec)
		{
			if(!t || rank<0) return ;
			for(node * it=t;it->next;it=it->next)
				if(it->next->val>x)
				{
					get_pos(it->down,x,rank-1,threshold,vec);
					if(rank<=threshold)vec.push_back(it);
					return ;
				}
		}

		// returns the first appeared, top node of value 'x'
		node * find_top(int x)
		{
			node * it=L[MAX_RANK-1];
			while(it)
			{
				if(it->next->val==x) return it;
				if(it->next->val>x) it=it->down;
				else it=it->next;
			}
			return NULL;
		}

		// insert nodes of value 'x', after each node in 'vec'
		void insert_after(vector<node *>& vec, int x)
		{
			node * p=NULL;
			for(auto it=vec.begin();it!=vec.end();++it)
			{
				node * temp=new node;
				temp->val=x;
				temp->next=(*it)->next;
				(*it)->next=temp;
				temp->next->last=temp;
				temp->last=(*it);
				temp->down=p;
				p=temp;
			}
		}

	public:
		// insert x into skiplist
		void insert(int x)
		{
			int rank=get_rank();
			vector<node *> vec;
			get_pos(L[MAX_RANK-1],x,MAX_RANK-1,rank,vec);
			insert_after(vec,x);
		}

		// erase x from skiplist
		void erase(int x)
		{
			node * t=find_top(x);
			if(!t) return ;
			t=t->next;
			while(t)
			{
				t->last->next=t->next;
				t->next->last=t->last;
				node * temp=t;
				t=t->down;
				delete temp;
			}
		}

		// returns wheher x is in the skiplist
		bool find(int x)
		{
			node * t=find_top(x);
			return t!=NULL;
		}
};

int main()
{	
	int n,x;
	SkipList L;
	string op;
	cin >> n;
	while(n--)
	{
		cin >> op >> x;
		if(op=="i") L.insert(x);
		if(op=="d") L.erase(x);
		if(op=="f") printf("%s\n",L.find(x)? "Y":"N");
	}
	return 0;
}
