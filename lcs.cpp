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

#define M 7
#define N 6

vector<char> s = {'A','T','C','T','G','A','T'};
vector<char> t = {'T','G','C','A','T','A'};

void execute(vector< vector<int> > &, vector< vector<int> > &);//executa o algoritmo longest common sequence

void printLCS(vector<vector<int>> &, int, int);//imprime

int maximum(int, int, int);//retorna o maior valor entre 3

int main(int argc, char const *argv[])
{
	vector< vector<int> > a, b;

	a = vector< vector<int> > (M + 1, vector<int> ( N + 1, 0 ) );
	b = vector< vector<int> > (M+1, vector<int> (N+1, -1) );

	execute(a,b);
	printLCS(b,N,M);
	cout<<"\n";

	return 0;
}

void execute(vector< vector<int> > &a, vector<vector<int>> &b) {

	int i = 0, j = 0;

	for (i = 1; i <= N; i++)
	{
		a[i][0] = 0;
	}

	for (j = 1; j <= M; j++)
	{
		a[0][j] = 0;
	}

	for (i = 1; i <= N+1; i++)
	{
		for (j = 1; j <= M+1; j++)
		{
			
			if (s[i-1] == t[j-1])
			{
				a[i][j] = a[i-1][j-1] + 1;
				b[i][j] = 2;//valor veio da diagonal
			}
			else if (a[i-1][j] >= a[i][j-1])
			{
				a[i][j] = a[i-1][j];
				b[i][j] = 1;//valor veio de cima
			}
			else 
			{
				a[i][j] = a[i][j-1];
				b[i][j] = 0;//valor veio da esquerda
			}
			cout<<" "<<b[i][j];
		
		}
		cout<<endl;
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

void printLCS(vector<vector<int>> &b, int i, int j)
{
	if (i == 0 || j == 0)
	{
		return;
	}

	if (b[i][j] == 2)
	{
		printLCS(b,i-1,j-1);
		cout<<" "<<s[i-1];
	}
	else if (b[i][j] == 1)
	{
		printLCS(b,i-1,j);
	}
	else
	{
		printLCS(b,i,j-1);
	}
}

