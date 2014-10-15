// Projektowanie Efektywnych Algorytmów, Z. Buchalski
// projekt 1
// Dawid Sibiñski, Bart³omiej Grzegorek
// semestr zimowy 2014/2015


#include "Header.h"
#include "tsp.h"

using namespace std;



int main()
{
	string dane = "dane.txt";
	tsp* t = new tsp();
	t->load("dane.txt");
	t->print();
	cout << endl;

	vector<int> wynik = t->annealing(5);
	for (int& i : wynik)
		cout << i << " ";

	cout << endl << "KOSZT: " << t->cost(wynik);
	
	system("PAUSE");
}