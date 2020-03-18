#include <bits/stdc++.h>

using namespace std;

int main()
{
	map<int,int> M;
	int n,x;
	char op[10];
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s",op);
		scanf("%d",&x);
		if(op[0]=='i')
		{
			M[x]++;
		}
		else if(op[0]=='d')
		{
			if(M[x])M[x]--;
		}
		else if(op[0]=='f')
			printf(M[x]?"Y\n":"N\n");
	}

	return 0;
}
