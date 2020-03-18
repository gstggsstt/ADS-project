#include <bits/stdc++.h>

using namespace std;

int main()
{
	set<int> T;	
	int n,x;
	char op[10];
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s",op);
		scanf("%d",&x);
		if(op[0]=='i')
		{
			T.insert(x);
			printf("%d\n",T.size());
		}
		else if(op[0]=='d')
		{
			T.erase(x);
			printf("%d\n",T.size());
		}
		else if(op[0]=='f')
			printf(T.find(x)!=T.end()?"True\n":"False\n");
		else if(op[0]=='l')
		{
			auto temp=T.lower_bound(x);
			if(T.empty()) printf("0\n");
			else if(temp!=T.end())
			{
				if(x<=*temp && temp!=T.begin())temp--;
				printf("%d\n",*temp);
			}
			else { temp--; printf("%d\n",*temp); }
		}
		else if(op[0]=='g')
		{
			auto temp=T.upper_bound(x);
			if(T.empty()) printf("%d\n",*temp);
			else if(temp!=T.end()) printf("%d\n",*temp);
			else { temp--; printf("%d\n",*temp); }
		}
	}

	auto endd=T.end();
	for(auto it=T.begin();it!=endd;++it)
		printf("%d ",*it);
	printf("\n");

	return 0;
}
