#include <iostream>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <climits>
#include <list>
#include <vector>
#include <random>

using namespace std;

class SkipList
{
	//Random seed
	random_device seed;
	//Random gernerator MT19937
	mt19937 RND;

	typedef pair<int,LIIt> IPIt;
	typedef list<IPIt>::iterator LIIPIt; // List <Int, IntPairIterator> Iterator
	typedef list<pair<int,LIIPIt> > LIPIt; // List <Int Pair Iterator>

	typedef list<pair<int,iterator> >

#define MAX_RANK (20)

	// Stored by line
	// Each node X is of type 
	//					pair<int,list<int>::iterator> >
	//   [X.first]  is the value of the node.
	//   [X.second] points to the node on the same column, which has the same
	//     value but lower rank.
	//
	// The structure loos like this:
	// L[2]: <1,2> -------------------> <1,2> 
	//          |                          |
	// L[1]: <1,2> -> <1,2> ----------> <1,2>
	//          |        |                 |
	// L[0]: <1,2> -> <1,2> -> <1,2> -> <1,2>
	//
	LIPIt L[MAX_RANK];
	LIPIt E;

	SkipList()
	{
		//Init random generator
		RND=mt19937(seed());
		// Insert INF and -INF
		for(int i=0;i<MAX_RANK;++i)
			L[i].push_front(make_pair(INT_MAX,i?L[i-1].begin():E.end()));
		for(int i=0;i<MAX_RANK;++i)
			L[i].push_front(make_pair(INT_MIN,i?L[i-1].begin():E.end()));
	}

	int get_rank()
	{
		int k=0;
		while(RND()&1) k++;
		return k;
	}

	LIIt find_position(int x,int rank)
	{
		auto it=L[rank].begin();
		while(*it.next()<=x) ++it;
		return it;
	}

	LIIt insert_by_rank(int x,int rank)
	{
		if(rank<0) return E.end();

		auto it=find_position(x,rank);

		auto temp=make_pair( x, insert_by_rank(x,rand+1,rank_lim) );
		
		L[rank].insert(it,temp);
		return it.next();
	}

	void insert(int x)
	{
		int k=get_rank();
		insert_by_rank(x,k);
	}

	void get_deeper_if_possible(LIIt &it)
	{
		if(it->second!=E.end())it=it->second;
	}

	pair<LIIt,int> find_top_it(int x)
	{
		int k=MAX_RANK;
		do
		{
			auto it=find_position(x,k);
			if(it->first==x) break;
			get_deeper_if_possible(it);
			k--;
		}while(k>0);
		return make_pair(it,k);
	}

	bool find(int x)
	{
		auto it=find_top_it(x).first;
		if(it->first==x) return true;
		return false;
	}
	
	void erase(int x)
	{
		auto rtn=find_top_it(x);
		auto it=rtn.first;
		if(it->first==x)
		{
			int k=rtn.second;
			do
			{
				auto temp=it;
				it=it.second;
				L[k--].erase(temp);
			}while(it->second!=E.end());
		}
	}
};
		

int main()
{
	int n,x;
	string op;
	cin >> n;
	while(n--)
	{
		cin >> op >> x;
		if(op=="I") L.insert(x);
		if(op=="D") L.erase(x);
		if(op=="F") printf("%s\n",L.find(x)? "T":"F");
	}
	return 0;
}

