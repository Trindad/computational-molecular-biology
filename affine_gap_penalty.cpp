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

#define M 9
#define N 9

int g = 1;//gap
int h = 20;

vector<char> s = {'t','a','c','g','g','g','t','a','t'};
vector<char> t = {'g','g','a','c','g','t','a','c','g'};

void execute(vector< vector<int> > &, 
		vector< vector<int> > &, vector< vector<int> > &);

int maximum(int, int, int);

int score(char, char);

int w(int);

int main(int argc, char const *argv[])
{
	vector< vector<int> > a, b, c;

	a = vector< vector<int> > (M + 1, vector<int> ( N + 1, -999 ) );
	b = vector< vector<int> > (M + 1, vector<int> ( N + 1, 0 ) );
	c = vector< vector<int> > (M + 1, vector<int> ( N + 1, 0 ) );

	for (int j = 1; j <= N; j++)  c[0][j] = -999;
	for (int i = 1; i <= M; i++)  b[i][0] = -999;

	execute(a,b,c);

	return 0;
}

void execute(vector< vector<int> > &a, vector< vector<int> > &b, 
	vector< vector<int> > &c) {

	int i = 0, j = 0;
	
	//inicializando linha e coluna
	a[0][0] = 0;
	b[0][0] = -999;
	c[0][0] = -999;

	for (int i = 1; i <= N; i++)
	{
		a[i][0] = -999;
		b[i][0] = -999;
		c[i][0] = -w(i);
	}

	for (int i = 1; i <= M; i++)
	{
		a[0][i] = -999;
		b[0][i] = -w(i);
		c[0][i] = -999;
	}

	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= M; j++)
		{
			a[i][j] = score(s[i-1], t[j-1]) + maximum( a[i-1][j-1],
													 b[i-1][j-1], c[i-1][j-1] );
			
			int m1, m2, m3;
			m1 = a[i][j-1] -h-g;
			m2 = b[i][j-1] -g;
			m3 = c[i][j-1] -h-g;
			b[i][j] = maximum(m1,m2,m3);

			m1 = a[i-1][j] -h-g;
			m2 = b[i-1][j] -h-g;
			m3 = c[i-1][j] -g;
			c[i][j] = maximum(m1,m2,m3);
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

	//imprime matriz de valores
	for (int i = 0; i <= M; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			cout<<b[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n";

	//imprime matriz de valores
	for (int i = 0; i <= M; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			cout<<c[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n";
}

int maximum(int a, int b, int c) {

	int m = max(a,b);
	m = max(m,c);
	
	return m;
}

int score(char a, char b){

	if (a == b)
	{
		return 1;
	}

	return -1;
}

int w(int k){

	return h + k*g;
}