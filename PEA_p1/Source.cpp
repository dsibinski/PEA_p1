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


// zapis do pliku:

// zapisywanie zawartosci tablicy do pliku xls
void zapisz(double tab[], int rozmiar, string nazwa_pliku)
{
	ofstream plik(nazwa_pliku);

	for (int i = 0; i<rozmiar; i++){
		plik << tab[i] << "\n";
	}
	plik.close();
}



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


void startAlgorithm(char choice)
{
	srand(time(NULL));
	int n; // liczba miast
	string dane = "dane.txt";
	tsp* t = new tsp();
	if (choice == 'f')
	{
		t->loadFromFile("dane.txt");
	}

	else
	{
		cout << "\nPodaj liczbe miast: ";
		
		cin >> n;
		t->loadRandom(n);
	}
	
	t->print();
	cout << endl;
	StartCounter();
	vector<int> wynik = t->annealing(100000, n, 500, 0.85);
	double time = GetCounter();

	cout << endl << endl << "Czas dzialania algorytmu: " << time << " [ms]. " << endl;

	cout << endl << "NAJMNIEJSZY KOSZT: " << t->cost(wynik) << endl;
}


// pomiar czasu (miasta, liczba pomiarow, wspolczynnik)
void measurement(int n_, int m, double p)
{
	double * results = new double[m]; // tablica, ktora bedzie przechowywac wyniki pomiarow
	srand(time(NULL));
	int n = n_; // liczba miast
	tsp* t = new tsp();
	t->loadRandom(n);

	// m pomiarow
	for (int i = 0; i < m; i++)
	{

		//t->loadRandom(n);
		cout << endl;
		StartCounter();
		vector<int> wynik = t->annealing(100000, n, 500, p);
		results[i] = GetCounter(); // wyniki pomiarow zapisujemy w tablicy

		cout << endl << endl << "Czas dzialania algorytmu: " << results[i] << " [ms]. " << endl;

		cout << endl << "NAJMNIEJSZY KOSZT: " << t->cost(wynik) << endl;
		
	}
	
	zapisz(results, m, "pomiar.xls");




}

int main()
{

	int quit = -1;
	int choice = -1;

	cout << "PEA - projekt nr 1 - Algorytm Symulowanego Wyzarzania";
	cout << "Dawid Sibinski, Bartlomiej Grzegorek\n\n";

	do
	{

		cout << endl << "Podaj wybor: " << endl;
		cout << "1 - Algorytm Wyzarzania - laduj z pliku dane.txt\n";
		cout << "2 - Algorytm Wyzarzania - generuj losowe wagi dla wybranej liczby miast\n";
		cout << "3 - pomiar\n";
		cout << "0 - wyjscie z programu.\n";
		cout << "Wybor: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			startAlgorithm('f'); // rozpoczecie algorytmu w trybie czytania z pliku
			break;

		case 2:
			startAlgorithm('r'); // rozpoczecie algorytmu w trybie losowania wag dla wybraje liczby miast
			break;
		case 3:
			measurement(17, 100, 0.999);
			break;
		case 0:
			quit = 0;
			break;

		default:
			
			break;
		}

	} while (quit != 0);



	
	// zamiast system("pause"):
	cout << "\nNacisnij dowolny klawisz, aby zakonczyc....\n";
	cin.get();
	cin.get();
}