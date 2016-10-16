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

#define M 7
#define N 7

void allPaths(int, int, int &,vector<char>, vector<char>, vector<char>, vector<char>, vector<vector<int>>);

void execute(vector< vector<int> > &, vector<char>, vector<char>);//executa o algoritmo longest common sequence

int cost(int,int);

int minimum(int, int, int);

int main(int argc, char const *argv[])
{
	vector< vector<int> > a = vector< vector<int> > (M+1, vector<int> ( N+1, 0 ) );
	vector<char> s = {'w','r','i','t','e','r','s'};
	vector<char> t = {'v','i','n','t','n','e','r'};

	execute(a, s, t);

	vector<char> align_s;
	vector<char> align_t;

	int len = 0;
	
	allPaths(M,N,len,s,t, align_s,align_t,a);
	cout<<"\n\n len = "<<len<<endl;
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

	vector< vector<string> > b = vector< vector<string> > (M+1, vector<string> ( N+1,"3") );
	
	for (i = 1; i <= M; i++)
	{
		for (j = 1; j <= N; j++)
		{
			int p = a[i-1][j-1] + cost(s[i-1], t[j-1]);

			a[i][j] = minimum(p, a[i-1][j] + 1, a[i][j-1] + 1);
			
			string str = "";
			
			if (a[i][j] == p)
			{
				str+="1";
			}
			if (a[i][j] == (a[i-1][j] + 1) )
			{
				str+="2";
			}
			if (a[i][j] == (a[i][j-1] + 1) )
			{
				str+="3";
			}

			b[i][j] += str;
		}

	}

	vector< vector<int> > edge = vector< vector<int> > (M+1, vector<int> ( N+1, 0) );
	
	for (i = 0; i <= M; i++)
	{
		for (j = 0; j <= N; j++)
		{
			string str = b[i][j];
			edge[i][j] = (int)b[i][j].size();
		}
	}

	cout<<"number of paths = "<<edge[M-1][N-1]<<endl;

	//imprime matriz de valores
	for (i = 0; i <= M; i++)
	{
		for (j = 0; j <= N; j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n";
}

int minimum(int a, int b, int c){

	int m = a < b ? a : b ;

	return m < c ? m : c;

}

int cost(int a, int b)
{
	if (a == b)
	{
		return 0;	
	}

	return 1;
}

void allPaths(int i, int j, int &len,vector<char> x, vector<char> y, vector<char> align_s, vector<char> align_t, vector<vector<int>> sim)
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
		
		
		len ++;
	}

	if (i > 0 && (sim[i][j] == (sim[i-1][j] + 1 )) )
	{
		align_s.push_back(x[i-1]);
		align_t.push_back('_');

		allPaths(i-1,j,len,x,y,align_s,align_t,sim);

		align_s.pop_back();
		align_t.pop_back();
	}

	if (i > 0 && j > 0 && (sim[i][j] == (sim[i-1][j-1] + cost(x[i-1],y[j-1]) ) ) )
	{
		align_s.push_back(x[i-1]);
		align_t.push_back(y[j-1]);

		allPaths(i-1,j-1,len,x,y, align_s,align_t,sim);

		align_s.pop_back();
		align_t.pop_back();
	}

	if (j > 0 && (sim[i][j] == (sim[i][j-1] + 1 )) )
	{
		align_s.push_back('_');
		align_t.push_back(y[j-1]);

		allPaths(i,j-1,len,x,y,align_s,align_t,sim);

		align_s.pop_back();
		align_t.pop_back();
	}
}
