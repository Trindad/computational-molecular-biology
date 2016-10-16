//longest common subsequence
#include <iostream>
#include <fstream>
#include <deque>
#include <iterator>
#include <algorithm> //reverse vector
#include <limits> //limites numéricos
#include <stdexcept> // for std::runtime_error
#include <vector>
#include <random>
#include <string>

using namespace std;

#define M 6
#define N 3

void execute(vector< vector<int> > &, vector<char>, vector<char>);//executa o algoritmo longest common sequence

int score(int,int);

int maximum(int, int, int);

int main(int argc, char const *argv[])
{
	vector< vector<int> > a = vector< vector<int> > (M+1, vector<int> ( N+1, 0 ) );
	vector<char> s = {'A','T','A','T','A','A'};
	vector<char> t = {'T','T','A'};

	execute(a, s, t);
	return 0;
}

void execute(vector< vector<int> > &a, vector<char> s, vector<char> t) {

	int i = 0, j = 0, g = -2;

	for (i = 1; i <= M; i++)
	{
		a[i][0] = i;
	}

	for (j = 1; j <= N; j++)
	{
		a[0][j] = j;
	}


	for (i = 1; i <= M; i++)
	{
		for (j = 1; j <= N; j++)
		{
			int p = a[i-1][j-1] + score(s[i-1], t[j-1]);

			a[i][j] = minimum(p, a[i-1][j] + 1, a[i][j-1] + 1);
			
		}
	}

	//imprime matriz de valores
	for (int i = 0; i <= M; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n";
}

int minimum(int a, int b, int c){

	int m = min(a,b);

	return min(m,c);

}

int score(int a, int b)
{
	if (a == b)
	{
		return 0;	
	}

	return 1;
}