#include <bits/stdc++.h>

using namespace std;

int main(int argv,char ** argc)
{
	assert(argv>=3);

	int n=atoi(argc[1]);
	mt19937	RND(atoi(argc[2]));

	cout << n << endl;
	int tempn=n/3;
	while(n--)
	{
		int temp=RND()%100;
		if(temp<40)
			cout << "i " << RND()%tempn << endl;
		else if(temp<50)
			cout << "d " << RND()%tempn << endl;
		else
			cout << "f " << RND()%tempn << endl;
	}
	return 0;
}
