#include "Header.h"
class tsp
{
	int sz;					//rozmiar
	int** A;				//macierz s�siedztwa

	vector<int> adjacentSolution(vector<int>&);
	vector<int> randomSolution(int);

public:
	tsp();
	~tsp();
	void init(int);			//inicjalizacja przy wczytywaniu danych z pliku
	bool loadFromFile(string);		//zaladowanie z pliku("�cie�ka do pliku .txt")
	void loadRandom(int _n); // wypelnienie struktury losowymi wagami dla podanej liczby miast
	

	int size();				//zwraca liczbe miast

	void print();			//wypisanie macierzy s�siedztwa
	int cost(vector<int>&);	//zwraca koszt dla podanej w wektorze �cie�ki
	void load();			//wczytanie z klawiatury	


	// przyjmuje liczbe miast. Zwraca losow� permutacj� (ostatnia liczba = pierwszej)
	//np. randomSolution(4); zwr�ci vector<int> sol = { 2, 1, 0, 3, 2 };

	vector<int> annealing(int L, double t);		//algorytm wy�azania,  L - liczba krok�w, t - temperatura pocz�tkowa
};

