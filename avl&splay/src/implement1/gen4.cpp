#include <bits/stdc++.h>

using namespace std;

int main(int argv,char ** argc)
{
	assert(argv>=3);

	int n=atoi(argc[1]);
	mt19937	RND(atoi(argc[2]));

	cout << n*4 << endl;
	for(int i=1;i<=n;++i) printf("i %d\n",i);
	for(int i=1;i<=n;++i) printf("f 0\n");
	for(int i=1;i<=n;++i) printf("l %d\n",n+1);
	for(int i=1;i<=n;++i) printf("g 0\n");
	return 0;
}
