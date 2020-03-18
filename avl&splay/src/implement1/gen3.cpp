#include <bits/stdc++.h>

using namespace std;

int main(int argv,char ** argc)
{
	assert(argv>=3);

	int n=atoi(argc[1]);
	mt19937	RND(atoi(argc[2]));

	cout << n*2 << endl;
	vector<int> vec;
	for(int i=1;i<=n;++i) vec.push_back(i);
	shuffle(vec.begin(),vec.end(),RND);
	for(int i=0;i<n;++i) printf("i %d\n",vec[i]);
	shuffle(vec.begin(),vec.end(),RND);
	for(int i=0;i<n;++i) printf("d %d\n",vec[i]);
	return 0;
}
