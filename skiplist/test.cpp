#include <bits/stdc++.h>

using namespace std;

int main()
{
	srand(time(0));
	int n;
	char cmd[110];
	scanf("%d",&n);
	//printf("Compiling...\n");
	//system("g++ ./gen.cpp -o ./gen -O2 -static-libgcc -static-libstdc++");
	//system("g++ ./stl.cpp -o ./stl -O2 -static-libgcc -static-libstdc++");
	//system("g++ ./SkipList.cpp -o ./SkipList -O2 -static-libgcc -static-libstdc++");
	do
	{
		sprintf(cmd,"gen %d %d >in.txt",n,rand());
		printf("Generating Data...\n");
		system(cmd);

		int t0=clock();
		printf("Running STL...\n");
		system("stl <in.txt >out1.txt");
		printf("\tSTL Time: %ldms\n",clock()-t0);

		t0=clock();
		printf("Running SkipList...\n");
		system("Skiplist <in.txt >out2.txt");
		printf("\tSkiplist Time: %ldms\n",clock()-t0);

	}while(!system("fc out1.txt out2.txt"));
	return 0;
}


