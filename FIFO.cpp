

#include "pch.h"
#include <iostream>
#include <iomanip>
#include <fstream> 
#include <string>
using namespace std;

//funkcja print ramki
void pr_ram(ofstream &zapis,int ram[])
{
	for (int i= 0; i < 3; i++)
		zapis << setw(10) << ram[i] << "   ";
	zapis << endl;
	zapis << endl;
}

int main()
{

	ifstream czytanie("plik.txt");
	ofstream zapis("wyjscie.txt");
	
	
	int a;
	int il_li = 0; //ilosc linii

	//1//sprawdzenie ile jest odwolan w pliku wejsc.
	if (czytanie.is_open()) {

		while (czytanie >> a)
		{
			il_li++;
		}	
	}
	else
	{
		cout << "Problem z odczytem pliku wejsciowego :/";
	}
	czytanie.close();
	//EndOf_1//

	int *odw = new int[il_li]; //dyn. tab. przechowujaca nasze odwolania

	int x = 0; //zmienna pomocnicza

	//2//czytanie z pliku i zapisywanie do dynamicznej tablicy
	ifstream czytanie2("plik.txt");
	if (czytanie2.is_open()) {

		while (czytanie2 >> a)
		{
			odw[x] = a;
			x++;
		}
	}
	else
	{
		cout << "Problem z odczytem pliku wejsciowego :/";
	}
	czytanie2.close();
	//EndOf_2//
	
	

	//domyslne wartosci ramek
	int ram[3] = {-1, -1, -1 };

	int n = 2; 
	int b = il_li;
	
	//Napisy
	zapis <<"Numer ramki:      "<< setw(10) << "|1|" << setw(13) <<  "|2|" << setw(13) << "|3|" << endl;
	zapis << endl;
	zapis << "Domyslnie:       "<< setw(10) << "-1" << setw(13) << "-1" << setw(13) << "-1" << endl;
	zapis << endl;
	//EndOf_Napisy//

	//3 pierwsze takty//
	for (int i = 0; i < 3; i++)
	{
		
		ram[i] = odw[i];
		zapis << "Odwolanie:|" << odw[i] << "|    ";
		pr_ram(zapis,ram);
	}

	int *prio = &odw[0]; //szukany priorytet, domyslnie wartosc 1szego wywolania 
	int c = 0; //zmienna pomocnicza



//Glowny algorytm
poczatek:
	while (n < b) // "dopoki nie obsluzymy wszystkich odwolan"
	{
		//sprawdzamy czy wywolanie juz istnieje w ramce
		for (int i = 0; i < 3; i++)
		{
			if (odw[n] == ram[i]) //istnieje, a wiec rusza kolejny takt
			{
				zapis << "Odwolanie:|" << odw[n] << "|    ";
				pr_ram(zapis,ram);

				n++;
				goto poczatek;
			}
		}
		//wywolanie nie istnieje w ramkach, zamieniamy ramke na ktora wskazuje priorytet
		for (int i = 0; i < 3; i++)
		{
			if (ram[i] == prio[c])
			{
				ram[i] = odw[n];
				zapis << "Wywolanie:|" << odw[n] << "|    ";
				pr_ram(zapis,ram);
				c++; //przesuwamy priorytet
				n++; 
				goto poczatek; //kolejny takt
			}
		}
	}
	cout << "Sukces! Prosze o sprawdzenie pliku wyjsciowego :)";
	zapis.close();
}

