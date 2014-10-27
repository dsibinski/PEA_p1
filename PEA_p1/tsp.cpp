#include "tsp.h"
#include <ctime>
using namespace std;


// konstruktor
tsp::tsp() : sz{ 0 }, A{ nullptr }
{
}

// destruktur
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

// iniciuje macierz sasiedztwa o zadanym rozmiarze
void tsp::init(int size)
{
	if (A != nullptr)
		this->~tsp();
	sz = size;
	A = new int*[sz];
	for (int i = 0; i != sz; i++)
		A[i] = new int[sz];
}


// laduje dane do macierzy z pliku o zadanej nazwie
bool tsp::loadFromFile(string name)
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


// laduje losowe dane (wagi) do macierzy dla podanej liczby miast
void tsp::loadRandom(int _n)
{
	int n = _n;
	int wartosc;
	init(n);

	for (int i = 0; i != sz; i++)
	for (int j = 0; j != sz; j++)
	{
		if (i == j)
			A[i][j] = 0; // brak petli
		else
			A[i][j] = ((rand() %50) + 1); // wartosci losowe od 1 do 50
	}


}

// zwraca rozmiar
int tsp::size() { return sz; }


// funkcja wyswietlajaca na ekranie zawartosc macierzy sasiedztwa
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
// zwraca koszt drogi dla zadanego wektora rozwiazania
int tsp::cost(vector<int>& sol)
{
	int cost = 0;
	for (int i = 0; i != sol.size() - 1; i++)
		cost += A[sol[i]][sol[i + 1]];
	return cost;
}

// generuje losowe rozwiazanie dla zadanej liczby miast
vector<int> tsp::randomSolution(int number)
{
	//losowanie pocz¹tkowego rozwi¹zania 'sol'
	vector<int> v;
	vector<int> sol;					//wektor rozwi¹zania z numerami kolejnych wierzcho³ków
	for (int i = 0; i != number; i++)
		v.push_back(i);

	srand(time(NULL));
	for (int i = 0; i != number; i++)
	{
		int x = rand() % v.size();
		sol.push_back(v[x]);
		v.erase(v.begin() + x);			// erase() przyjmuje w parametrze iterator, a nie 'int'. begin() to iterator wskazuj¹cy na pierwszy element
	}
	sol.push_back(sol[0]);				//ostatnim wierzcho³ek musi byæ równy pierwszemu (komiwoja¿er wraca do pocz¹tkowego miasta)

	return sol;
}

// zwraca rozwiazanie sasiednie dla zadanego wektora rozwiazania obecnego
vector<int> tsp::adjacentSolution(vector<int>& sol)
{
	vector<int> _sol = sol;

	//wyznaczenie losowego rozwi¹zania s¹siedniego "_sol" poprzez zamianê dwóch losowych wierzcho³ków
	//Przyk³ad: sol = {2, 1, 3, 0, 2}; // sol.size() = 5;  ale zawsze v[0] = v[4] (pierwsze miasto jest ostatnim miastem)
	//dlatego ostatniego indeksu nie rozwa¿am do losowania - jego wartoœæ zawsze bêdzie równa v[0]
	int x1, x2, tmp;					//zamienie wierzcholek x1 z wierzcholkiem x2
	x1 = rand() % (_sol.size() - 1);
	x2 = rand() % (_sol.size() - 1);
	if (x2 == x1)					//aby nie wylosowaæ 2x tego samego wierzcholka
	{
		if (x2 == _sol.size() - 2)	// gdy s¹ takie same i s¹ ostatnim miaste, to zamieniamy ostatnie z przedostatnim
			x2--;
		else
			x2++;					//jeœli takie same, ale nie s¹ ostatnim miastem to zamieniamy wylosowany z kolejnym
	}

	//zamiana wylosowanych wierzcholkow
	tmp = _sol[x1];
	_sol[x1] = _sol[x2];
	_sol[x2] = tmp;
	_sol[_sol.size() - 1] = _sol[0];

	return _sol;
}



// algorytm wyzarzania dla zadanej liczby ietracji i temperatury poczatkowej; zwraca najlepsze znalezione rozwiazanie (wektor)
vector<int> tsp::annealing(int L, double t)
{

	cout << "ROZWIAZANIE POCZATKOWE" << endl;
	vector<int> sol = randomSolution(sz);
	for (int& x : sol)
		cout << x << " ";
	cout << endl << "KOSZT: " << cost(sol) << endl;

	vector<int> bestSol = sol;			// wylosowane rozwi¹zanie jest automatycznie najlepszym, poniewa¿ jest to jedyne rozwi¹zanie
	vector<int> _sol = sol;				//_sol - rozwi¹zanie s¹siednie

	int costSol, cost_Sol, costBestSol;		//
	costSol = cost(sol);
	costBestSol = costSol;

	////////////// algorytm wy¿arzania
	//double temp = costSol;
	double temp = t;
	for (int i = 0; i != L; i++)
	{
		_sol = adjacentSolution(sol);		// rozwi¹zanie s¹siednie
		cost_Sol = cost(_sol);


	/////////////////////////////////////////////  WYPISANIE NOWEJ ŒCIE¯KI I KOSZTÓW	////////////////
		cout << endl << "--------------------------------------------------------------" << endl;
		for (int& x : _sol)
			cout << x << " ";
		cout << endl << "KOSZT: " << cost_Sol;
	///////////////////////////////////////////////////////////////////////////////////////////////////
		
		//  sprawdzenie czy nowe rozwi¹zanie jest lepsze od najlepszego
		if (cost_Sol < costBestSol)
		{
			bestSol = _sol;
			costBestSol = cost_Sol;
		}
		double delta = cost_Sol - costSol;
		if (delta < 0)
		{
			sol = _sol;
			costSol = cost_Sol;
			cout << "rozwiazanie lepsze, AKCEPTUJE" << endl;
		}
		else
		{
			double x = (rand() % 10000) / 10000.0;				// losowa liczba z zakresu <0, 1)
			cout << "rozwiazanie gorsze..." << endl;
			cout << "losowy x = " << x << endl;
			cout << "delta    =" << delta << endl;
			cout << "temp     =" << temp << endl;
			cout << "prawdopodobienstwo = " << exp((-delta) / temp) << endl;
			cout << x - (delta / temp) << endl;
			if (x < (exp((-delta) / temp)))
			{
				cout << "AKCEPTUJE" << endl;
				sol = _sol;
				costSol = cost_Sol;
			}
			else
				cout << "ODRZUCAM" << endl;

			temp *= 0.85;
		}
		cout << endl << "--------------------------------------------------------------" << endl;
			
			
	}
	//cout << (rand() % 100) / 100.0 << " " << (rand() % 100) / 100.0 << " " << endl;	//losowanie z zakresu<0, 1)

	return bestSol;
}