/**
Algoritmo de Needleman-Wunsch para obter a similaridade
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

#define M 4
#define N 3

int g = -2; //gap

int similarity(vector<char>,vector<char>,vector<vector<int>> &);
int score(char, char);
void align(int, int, int, vector<char>, vector<char>,  
		vector<char>, vector<char>, vector<vector<int>>);
int maximum(int a, int b, int c);

int main(int argc, char const *argv[])
{
	vector<char> x = {'A','A','A','G'};
	vector<char> y = {'A','C','G'};

	vector<char> align_s;
	vector<char> align_t;


	vector<vector<int>> sim = vector< vector<int> > (M + 1, vector<int> ( N + 1, 0 ) );

	similarity(x,y,sim);
	int len = 0;
	align(M,N,len,x,y, align_s,align_t,sim);
	
	return 0;
}

int similarity(vector<char> x, vector<char> y, vector<vector<int>> &sim) {

	int i = 0, j = 0;
	
	for (i = 0; i <= M; i++)
	{
		sim[i][0] = i * g;
	}

	for (j = 1; j <= N; j++)
	{
		sim[0][j] = j * g;
	}

	for (i = 1; i <= M; i++)
	{
		for (j = 1; j <= N; j++)
		{
			int t = sim[i-1][j-1] + score(x[i-1],y[j-1]);

			// cout<<" "<<sim[i-1][j-1]<<" "<<sim[i-1][j]<<" "<<sim[i][j-1]<<" "<<t<<endl;

			sim[i][j] = maximum(t, sim[i-1][j] + g, sim[i][j-1] + g );

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


void align(int i, int j, int len,vector<char> x, vector<char> y, vector<char> align_s, vector<char> align_t, vector<vector<int>> sim)
{
	if (i == 0 && j == 0)
	{
		reverse( align_s.begin(),align_s.end() );
		reverse( align_t.begin(),align_t.end() );

		for (int k = 0; k < (int)align_s.size(); k++)
		{
			cout<<" "<<align_s[k];
		}
		cout<<"\n";
		for (int k = 0; k < (int)align_t.size(); k++)
		{
			cout<<" "<<align_t[k];
		}
		cout<<"\n\n";
		
		
		len = 0;
	}

	if (i > 0 && (sim[i][j] == (sim[i-1][j] + g )) )
	{
		len += 1;
		align_s.push_back(x[i-1]);
		align_t.push_back('_');

		align(i-1,j,len,x,y,align_s,align_t,sim);

		align_s.pop_back();
		align_t.pop_back();
	}

	if (i > 0 && j > 0 && (sim[i][j] == (sim[i-1][j-1] + score(x[i-1],y[j-1]) ) ) )
	{
		len += 1;
		align_s.push_back(x[i-1]);
		align_t.push_back(y[j-1]);

		align(i-1,j-1,len,x,y, align_s,align_t,sim);

		align_s.pop_back();
		align_t.pop_back();
	}

	if (j > 0 && (sim[i][j] == (sim[i][j-1] + g )) )
	{
		len += 1;
		align_s.push_back('_');
		align_t.push_back(y[j-1]);

		align(i,j-1,len,x,y,align_s,align_t,sim);

		align_s.pop_back();
		align_t.pop_back();
	}
}
 