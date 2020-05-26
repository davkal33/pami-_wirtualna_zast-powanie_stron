#include "pch.h"
#include <iostream>
#include <iomanip>
#include <fstream> 
#include <string>

using namespace std;

//***************************************LRU*****************************************************
//funkcja print ramki
void pr_ram(ofstream &zapis, int ram[])
{
	for (int i = 0; i < 3; i++)
		zapis << setw(10) << ram[i] << "   ";
	zapis << endl;
	zapis << endl;
}



int main()
{
	///////////////////////////////
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
	int ram[3] = { -1,-1, -1 };


	int n = 3;	 //startowe odwolanie odw[n]
	int b = il_li; //obliczanie liczby odwolan
	int g = 0;    //flaga

	//Napisy
	zapis << "Numer ramki:      " << setw(10) << "|1|" << setw(13) << "|2|" << setw(13) << "|3|" << endl;
	zapis << endl;
	zapis << "Domyslnie:       " << setw(10) << "-1" << setw(13) << "-1" << setw(13) << "-1" << endl;
	zapis << endl;
	//EndOf_Napisy//

	//pierwsze 3 takty
	for (int i = 0; i < 3; i++)
	{
		ram[i] = odw[i];
		pr_ram(zapis,ram);
	}

//Glowny algorytm
poczatek:
	while (n < b)
	{
		//sprawdzanie czy odwolanie juz istnieje
		for (int i = 0; i < 3; i++)
		{
			if (odw[n] == ram[i])
			{
				pr_ram(zapis,ram);
				n++;
				goto poczatek; //istnieje -> print akt. ramka ->rusza kolejny takt
			}
		}
	
		int a = ram[0];
		int b = ram[1];
		int c = ram[2];
		int h = n;
		while (g != 3)
		{
			h--;
			if (odw[h] == a || odw[h] == b || odw[h] == c)
			{
				g++;
			}
		}
		for (int i = 0; i < 3; i++)
		{
			if (ram[i] == odw[h])
			{
				ram[i] = odw[n];
				pr_ram(zapis,ram);
				n++;
				g = 0;
				goto poczatek;
			}

		}
	}
	cout << "Sukces! Prosze o sprawdzenie pliku wyjsciowego";
	zapis.close();
}

