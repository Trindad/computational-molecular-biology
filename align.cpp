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

int sim[M+1][N+1];//m+1 e n+1
vector<char> align_s;
vector<char> align_t;

int similarity(vector<char>,vector<char>);
int score(char, char);
void align(int, int, int, vector<char> x, vector<char> y);

int main(int argc, char const *argv[])
{
	vector<char> x = {'a','a','a','c'};
	vector<char> y = {'a','g','c'};

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			sim[i][j] = 0;
		}
	}

	// sim = vector< vector<int> > (m,vector<int>(n,0));//armazena similaridade

	similarity(x,y);
	int len = 0;
	align(M,N,len, x,y);

	for (int i = 0; i < (int)align_t.size(); i++)
	{
		cout<<" "<<align_t[i];
	}
	cout<<"\n";
	for (int i = 0; i < (int)align_s.size(); i++)
	{
		cout<<" "<<align_s[i];
	}
	
	return 0;
}

int similarity(vector<char> x, vector<char> y) {

	int i = 0, j = 0;
	
	for (i = 0; i < M+1; i++)
	{
		sim[i][0] = i * g;
	}

	for (j = 1; j < N+1; j++)
	{
		sim[0][j] = j * g;
	}

	for (i = 1; i < M+1; i++)
	{
		for (j = 1; j < N+1; j++)
		{
			int _m =  max ( sim[i-1][j-1] + score( x[i-1], y[j-1] ), 
				sim[i-1][j] + g);

			sim[i][j] = max(_m, sim[i][j-1] + g );
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


void align(int i, int j, int len,vector<char> x, vector<char> y)
{
	cout<<" "<<i<<""<<j<<endl;
	if (i == 0 && j == 0)
	{
		len = 0;
	}
	else if (i > 0 && (sim[i][j] == (sim[i-1][j] + g )) )
	{
		align(i-1,j,len,x,y);
		len += 1;
		align_s.push_back(x[i-1]);
		align_t.push_back('_');
	}
	else if (i > 0 && j > 0 && (sim[i][j] == (sim[i-1][j-1] + score(x[i-1],y[j-1]) ) ) )
	{
		align(i-1,j-1,len,x,y);
		len += 1;
		align_s.push_back(x[i-1]);
		align_t.push_back(y[j-1]);
	}
	else
	{
		align(i,j-1,len,x,y);
		len += 1;
		align_s.push_back('_');
		align_t.push_back(y[j-1]);
	}
}