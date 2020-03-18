#include <bits/stdc++.h>

using namespace std;

int main()
{
	srand(time(0));
	int n;
	char cmd[110];
	scanf("%d",&n);
	//printf("Compiling...\n");
	//system("g++ ./gen1.cpp -o ./gen1 -O2 -static-libgcc -static-libstdc++");
	//system("g++ ./stl.cpp -o ./stl -O2 -static-libgcc -static-libstdc++");
	//system("g++ ./AVL.cpp -o ./AVL -O2 -static-libgcc -static-libstdc++");
	//system("g++ ./Splay.cpp -o ./Splay -O2 -static-libgcc -static-libstdc++");
	//system("g++ ./Normal.cpp -o ./Normal -O2 -static-libgcc -static-libstdc++");
	do
	{
		sprintf(cmd,"gen1 %d %d >in.txt",n,rand());
		printf("Generating Data...\n");
		system(cmd);

		int t0=clock();
		printf("Running STL...\n");
		system("stl <in.txt >out1.txt");
		printf("\tSTL Time: %ldms\n",clock()-t0);

		t0=clock();
		printf("Running Splay...\n");
		system("Splay <in.txt >out2.txt");
		printf("\tSplay Time: %ldms\n",clock()-t0);

		t0=clock();
		printf("Running AVL...\n");
		system("AVL <in.txt >out3.txt");
		printf("\tAVL Time: %ldms\n",clock()-t0);

		t0=clock();
		printf("Running Normal...\n");
		system("Normal <in.txt >out4.txt");
		printf("\tNormal Time: %ldms\n",clock()-t0);
	}while(!system("fc out1.txt out2.txt") &&
			!system("fc out1.txt out3.txt") && 
			!system("fc out1.txt out4.txt"));
	return 0;
}


