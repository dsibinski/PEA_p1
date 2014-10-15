#include "tsp.h"
#include <ctime>
using namespace std;

tsp::tsp() : sz{ 0 }, A{ nullptr }
{
}

tsp::~tsp()
{
	if (A != nullptr)
	{
		for (int i = 0; i != sz; i++)
		{
			delete[] A[i];
		}
		delete[] A;
	}
}

void tsp::init(int size)
{
	if (A != nullptr)
		this->~tsp();
	sz = size;
	A = new int*[sz];
	for (int i = 0; i != sz; i++)
		A[i] = new int[sz];
}

bool tsp::load(string name)
{
	fstream file;
	file.open(name, ios::in);
	if (!(file.good()))
	{
		cout << "nie udalo sie otworzyc pliku: " << name << endl;
		return false;
	}

	int size;
	file >> size;
	init(size);


	for (int i = 0; i != sz; i++)
		for (int j = 0; j != sz; j++)
		{
			if (i == j) 
				A[i][j] = 0;
			else
				file >> A[i][j];
		}
			

	file.close();
	return true;
}


int tsp::size() { return sz; }

void tsp::print()
{
	for (int i = 0; i != sz; i++)
	{
		for (int j = 0; j != sz; j++)
		{
			cout.width(4);
			cout << A[i][j];
		}
		cout << endl;
	}
}

/*
KOSZT: vector<int> sol = {3, 2, 0, 1, 3};   // przyk³adowy wektor rozwi¹zania
				cost =  A[3][2]
						+  A[2][0]
							+  A[0][1]
								+ A[1][3];
*/
int tsp::cost(vector<int>& sol)
{
	int cost = 0;
	for (int i = 0; i != sol.size() - 1; i++)
		cost += A[sol[i]][sol[i + 1]];
	return cost;
}

vector<int> tsp::annealing(int L)
{
										//losowanie pocz¹tkowego rozwi¹zania 'sol'
	vector<int> v;						
	vector<int> sol;					//wektor rozwi¹zania z numerami kolejnych wierzcho³ków
	for (int i = 0; i != sz; i++)
		v.push_back(i);

	srand(time(NULL));
	for (int i = 0; i != sz; i++)
	{
		int x = rand() % v.size();
		sol.push_back(v[x]);
		v.erase(v.begin() + x);
	}
	sol.push_back(sol[0]);				//wylosowane rozwi¹zanie pocz¹tkowe
	vector<int> bestSol = sol;


	////////////// algorytm wy¿arzania
	for (int i = 0; i != L; i++)
	{

	}
	//cout << (rand() % 100) / 100.0 << " " << (rand() % 100) / 100.0 << " " << endl;	//losowanie z zakresu<0, 1)

	return bestSol;
}

