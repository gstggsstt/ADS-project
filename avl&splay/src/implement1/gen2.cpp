#include <bits/stdc++.h>

using namespace std;

int main(int argv,char ** argc)
{
	assert(argv>=3);

	int n=atoi(argc[1]);
	mt19937	RND(atoi(argc[2]));

	cout << n*2 << endl;
	for(int i=1;i<=n;++i)
		printf("i %d\n",i);
	for(int i=n;i>=1;--i)
		printf("d %d\n",i);
	return 0;
}
