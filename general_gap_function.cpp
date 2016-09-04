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

#define M 2
#define N 4

int u = 4;

vector<char> t = {'a','c','t','g'};
vector<char> s = {'a','g'};

void generalGapFunction(vector< vector<int> > &, 
		vector< vector<int> > &, vector< vector<int> > &);

int max_1(vector< vector<int> > &, int, int);
int max_2(vector< vector<int> > &, int, int);

int maximum(int, int, int);

int score(char, char);

int w(int,int);

int main(int argc, char const *argv[])
{
	vector< vector<int> > a, b, c;

	a = vector< vector<int> > (M + 1, vector<int> ( N + 1, -999 ) );
	b = vector< vector<int> > (M + 1, vector<int> ( N + 1, 0 ) );
	c = vector< vector<int> > (M + 1, vector<int> ( N + 1, 0 ) );

	for (int j = 1; j <= N; j++)  c[0][j] = -999;
	for (int i = 1; i <= M; i++)  b[i][0] = -999;

	generalGapFunction(a,b,c);

	return 0;
}

void generalGapFunction(vector< vector<int> > &a, vector< vector<int> > &b, 
	vector< vector<int> > &c) {

	int i = 0, j = 0;
	
	//inicializando linha e coluna
	a[0][0] = 0;
	b[0][j] = 0;
	c[i][0] = 0;



	for (i = 1; i <= M; i++)
	{
		for (j = 1; j <= N; j++)
		{
			a[i][j] = score(s[i-1], t[j-1]) + maximum( a[i-1][j-1], b[i-1][j-1], c[i-1][j-1] );
			
			b[i][j] = max( max_1(a,i,j), max_1(c,i,j) );
			cout<<"*************************************\n";
			c[i][j] = max( max_2(a,i,j), max_2(b,i,j) );
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

	return max(m,c);
}

int score(char a, char b){

	if (a == b)
	{
		return 1;
	}

	return -1;
}

int w(int k){

	int b = 1;

	return u + k*b;
}

int max_1(vector< vector<int> > &a, int i, int j){

	int k = 1;
	int n = -999;

	while (k >= 1 && k <= j)
	{
		int temp = a[i][j-k] - w(k);

		if (temp > n)
		{
			// cout<<" "<<temp<<" "<<n<<" "<<a[i][j-k]<<" "<<w(k)<<endl;
			n = temp;
		}

		k++;
	}


	return n;
}

int max_2(vector< vector<int> > &a, int i, int j){

	int k = 1;
	int n = -999;

	while (k >= 1 && k <= i)
	{
		int temp = a[i-k][j] - w(k);
		
		if (temp > n)
		{
			// cout<<" "<<temp<<" "<<n<<" "<<a[i-k][j]<<" "<<w(k)<<endl;
			n = temp;
		}

		k++;
	}

	return n;
}