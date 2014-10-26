// Projektowanie Efektywnych Algorytmów, Z. Buchalski
// projekt 1
// Dawid Sibiñski, Bart³omiej Grzegorek
// semestr zimowy 2014/2015


#include "Header.h"
#include "tsp.h"

using namespace std;

// zmienne potrzebne do pomiaru czasu (metoda z PDFa Mierzwy ze SDiZO)
double PCFreq = 0.0;
__int64 CounterStart = 0;


// mozna zamienic w funkcji StartCounter odpowiednie czesci
// zeby uzyskac wynik zwracany przez getCounter() w innych jednostkach:
// sekundy:
// PCFreq = double(li.QuadPart)/1000.0;  --> PCFreq = double(li.QuadPart)/1000.0;
// mikrosekundy:
// PCFreq = double(li.QuadPart)/1000.0;  --> PCFreq = double(li.QuadPart)/1000000.0;
void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

// zwraca czas od ostatniego wywolania StartCounter() w milisekundach
double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}




int main()
{
	string dane = "dane.txt";
	tsp* t = new tsp();
	t->load("dane.txt");
	t->print();
	cout << endl;
	StartCounter();
	vector<int> wynik = t->annealing(100, 500);
	double time = GetCounter();

	cout << endl << endl << "Czas dzialania algorytmu: " << time << " [ms]. " << endl;

	cout << endl << "NAJMNIEJSZY KOSZT: " << t->cost(wynik) << endl;
	
	system("PAUSE");
}