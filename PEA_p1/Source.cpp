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
	fstream plik;
	plik.open(nazwa_pliku, ios::out | ios::app);
	for (int i = 0; i<rozmiar; i++){
		plik << tab[i] << "\n";
	}
	plik << endl;
	plik.close();
}

void zapiszWyniki(double tab[], int rozmiar, string nazwa_pliku, int miasta, double wspolczynnik)
{
	fstream plik;
	plik.open(nazwa_pliku, ios::app | ios::out);
	plik << miasta << "\t" << "miast" << endl;
	for (int i = 0; i != rozmiar; i++)
	{
		plik << tab[i] << "\n";
	}
	plik << "\n\n";
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
	double p;
	if (choice == 'f')
	{
		t->loadFromFile("dane.txt");
		n = t->size();
		cout << "\nPodaj wspolczynnik wyzarzania: ";
		cin >> p;
	}

	else
	{
		cout << "\nPodaj liczbe miast: ";
		cin >> n;
		t->loadRandom(n);
		cout << "\nPodaj wspolczynnik wyzarzania: ";
		cin >> p;
	}

	//	t->print();
	cout << endl;
	StartCounter();
	vector<int> wynik = t->annealing(100000, n, 500, p);
	double time = GetCounter();

	cout << endl << endl << "Czas dzialania algorytmu: " << time << " [ms]. " << endl;

	cout << endl << "NAJMNIEJSZY KOSZT: " << t->cost(wynik) << endl;
}


// pomiar czasu (miasta, liczba pomiarow, wspolczynnik)
void measurement(int n_, int m, double p)
{
	double * results = new double[m + 1];		// tablica, ktora bedzie przechowywac wyniki pomiarow
	double mean_results[5];					// tablica przechowuj¹ca uœrednione wyniki dla ka¿dego z piêciu wspó³czynników: 0,85  0,9  0,95  0,99  0,999
	double mean = 0;
	srand(time(NULL));
	int n = n_; // liczba miast
	tsp* t = new tsp();
	t->loadRandom(n);




	for (int j = 0; j < 5; j++)
	{
		p += 0.05;
		// m pomiarow
		for (int i = 0; i < m; i++)
		{

			//t->loadRandom(n);
			switch (j)
			{
			case 0:
				p = 0.85;
				break;
			case 1:
				p = 0.9;
				break;
			case 2:
				p = 0.95;
				break;
			case 3:
				p = 0.99;
				break;
			case 4:
				p = 0.999;
				break;
			}
			cout << endl;
			StartCounter();
			vector<int> wynik = t->annealing(0, n, 500, p);
			results[i] = GetCounter(); // wyniki pomiarow zapisujemy w tablicy
			mean += results[i];
			cout << endl << endl << "Czas dzialania algorytmu: " << results[i] << " [ms]. " << endl;

			cout << endl << "NAJMNIEJSZY KOSZT: " << t->cost(wynik) << endl;

		}
		results[m] = mean / m;			// œrednia pomiarów
		mean_results[j] = results[m];
	}


	cout << "Mean: " << mean << endl;
	zapisz(results, m + 1, "pomiar.xls");
	zapiszWyniki(mean_results, 5, "srednie.xls", n_, p);



}

int main()
{

	int quit = -1;
	int choice = -1;

	cout << "PEA - projekt nr 1 - Algorytm Symulowanego Wyzarzania\n";
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
			for (int i = 0; i < 5; i++)
			{
				measurement(50 + i * 100, 100, 0.85);
			}
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