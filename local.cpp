/**
Algoritmo Local
*/
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

#define M 11
#define N 13

int sim[M+1][N+1];//m+1 e n+1
int g = -2;

int similarity(vector<char>,vector<char>);
int score(char, char);

int main(int argc, char const *argv[])
{
	vector<char> x = {'a','b','r','a','c','a','d','a','b','r','a'};
	vector<char> y = {'c','a','b','e','c','a','d','e','c','a','b','r','a'};

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			sim[i][j] = 0;
		}
	}

	// sim = vector< vector<int> > (m,vector<int>(n,0));//armazena similaridade

	similarity(x,y);
	
	return 0;
}

int similarity(vector<char> x, vector<char> y) {

	int i = 0, j = 0;

	for (i = 1; i < M+1; i++)
	{
		for (j = 1; j < N+1; j++)
		{
			int _m =  max ( sim[i][j-1] + g , sim[i-1][j] + g);
			_m = max(_m, sim[i-1][j-1] + score( x[i-1], y[j-1] ));

			sim[i][j] = max(_m,0);
		}

	}

	//imprime matriz de valores
	for (int i = 0; i <= M; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			cout<<sim[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n";

	return sim[M][N];
}

int score(char a, char b){

	if (a == b)
	{
		return 1;
	}

	return -1;
}


