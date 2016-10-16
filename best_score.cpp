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

#define M 4
#define N 3

void execute(vector< int > &, vector<char>, vector<char>);//executa o algoritmo longest common sequence

int score(int,int);

int maximum(int, int, int);

int main(int argc, char const *argv[])
{
	vector< int > a = vector< int > (M+1,1);
	vector<char> s = {'a','a','a','g'};
	vector<char> t = {'a','c','g'};

	execute(a, s, t);

	return 0;
}

void execute(vector<int> &a, vector<char> s, vector<char> t) {

	int i = 0, j = 0, g = -2;
	int old = 0;

	for (j = 0; j <= N; j++)
	{
		a[j] = j * g;
	}

	for (i = 1; i <= M; i++)
	{
		old = a[0];
		a[0] = i * g;

		for (j = 1; j <= N; j++)
		{
			int temp = a[j];
			a[j] = maximum(a[j] + g, a[j-1] + g, old + score(s[i-1], t[j-1]) );
		
			old = temp;
		}
	}

	cout<<" SPA = "<<a[N]<<endl;
}

int maximum(int a, int b, int c){

	int m = max(a,b);

	return max(m,c);

}

int score(int a, int b)
{
	if (a == b)
	{
		return 1;//match	
	}

	return -1;//mismatch
}
