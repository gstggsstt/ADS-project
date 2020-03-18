#include <bits/stdc++.h>

using namespace std;

int main(int argv,char ** argc)
{
	assert(argv>=3);

	int n=atoi(argc[1]);
	mt19937	RND(atoi(argc[2]));

	cout << n << endl;
	int tempn=n;
	while(n--)
	{
		int temp=RND()%100;
		if(temp<20)
			cout << "i " << RND()%tempn << endl;
		else if(temp<40)
			cout << "d " << RND()%tempn << endl;
		else if(temp<60)
			cout << "f " << RND()%tempn << endl;
		else if(temp<80)
			cout << "l " << RND()%tempn << endl;
		else
			cout << "g " << RND()%tempn << endl;
	}
	return 0;
}
