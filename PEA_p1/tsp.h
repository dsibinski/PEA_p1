#include "Header.h"
class tsp
{
	int sz;					//rozmiar
	int** A;				//macierz s�siedztwa

public:
	tsp();
	~tsp();
	void init(int);			//inicjalizacja przy wczytywaniu danych z pliku
	bool load(string);		//zaladowanie z pliku("�cie�ka do pliku .txt")

	int size();				//zwraca liczbe miast

	void print();			//wypisanie macierzy s�siedztwa
	void load();			//wczytanie z klawiatury	

	int cost(vector<int>&);	//zwraca koszt dla podanej w wektorze �cie�ki
	vector<int> annealing(int L);	//algorytm wy�azania,  L - liczba krok�w
};

