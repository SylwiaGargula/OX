#include <SFML/Network.hpp>
#include <iostream> 
#include <cstdlib>
#include <time.h>
#include <Windows.h>
#include <string>
#include <fstream> 


using namespace std;



char** planszaF()
{
	char **plansza = new char*[3];
	for (char a = 0; a < 3; a++)
		plansza[a] = new char[3];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{

			plansza[i][j] = '*';

		}

	}

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
			cout << plansza[i][j] << " | ";
		cout << endl;
		cout << "-----------" << endl;

	}



	return plansza;
}



void gra(char symbol, int pozycjaX, int pozycjaY, char **plansza)
{

	plansza[pozycjaX][pozycjaY] = symbol;

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
			cout << plansza[i][j] << " | ";
		cout << endl;
		cout << "-----------" << endl;

	}

}



int sprawdzanie(char** plansza, char symbol)
{

	if (plansza[0][0] == symbol && plansza[0][1] == symbol && plansza[0][2] == symbol)
		return 1;
	else
		if (plansza[1][0] == symbol && plansza[1][1] == symbol && plansza[1][2] == symbol)
			return 1;
		else
			if (plansza[2][0] == symbol && plansza[2][1] == symbol && plansza[2][2] == symbol)
				return 1;

			else
				if (plansza[0][0] == symbol && plansza[1][0] == symbol && plansza[2][0] == symbol)
					return 1;
				else
					if (plansza[0][1] == symbol && plansza[1][1] == symbol && plansza[2][1] == symbol)
						return 1;
					else
						if (plansza[0][2] == symbol && plansza[1][2] == symbol && plansza[2][2] == symbol)
							return 1;

						else
							if (plansza[0][0] == symbol && plansza[1][1] == symbol && plansza[2][2] == symbol)
								return 1;

							else
								if (plansza[2][2] == symbol && plansza[1][1] == symbol && plansza[0][0] == symbol)
									return 1;

}


int main()
{
	sf::TcpSocket socket;


	cout << "Kolko i krzyzyk" << endl;
	cout << "Gra polegajaca na uzyskaniu 3 swoich znakow w jednej lini lub po przekatnej" << endl;
	Sleep(3000);
	system("cls");
	int numer_wyboru = 0;
	while (1)
	{
		cout << "Co chcesz zrobic? Wybierz numer " << endl;
		cout << "1 Nowa gra" << endl;
		cout << "2 Wyniki " << endl;
		cout << "3 Wyjscie" << endl;
		cin >> numer_wyboru;
		system("cls");
		fstream plik;
		switch (numer_wyboru)
		{
		case 1:
		{


			char symbol;
			string imie1, imie2;
			cout << "Wybrano nowa gre" << endl;
			cout << "Gracz 1 podaj swoje imie " << endl;
			cin >> imie1;
			cout << "Gracz 2 podaj swoje imie " << endl;
			cin >> imie2;

			int pozycjaX, pozycjaY;


			int skok = 0;
			char**plansza = planszaF();
			while (1)
			{


				do
				{

					cout << imie1 << " wybierz miejsce " << endl;
					cin >> pozycjaX;
					cin >> pozycjaY;
					symbol = 'X';
				} while (plansza[pozycjaX - 1][pozycjaY - 1] == 'O' || plansza[pozycjaX - 1][pozycjaY - 1] == 'X');
				gra(symbol, pozycjaX - 1, pozycjaY - 1, plansza);
				skok++;

				if (sprawdzanie(plansza, symbol) == 1)
				{
					plik.open("Wyniki.txt", ios::app);
					cout << "Wygrana gracza o imieniu " << imie1 << endl;

					if (plik.good() == true)
					{
						plik << imie1 << " wygral z " << imie2 << endl;

					}
					else cout << "Blad" << endl;
					plik.close();

					system("pause");
					break;
				}
				if (skok == 5)
				{
					cout << "Remis " << endl;
					plik.open("Wyniki.txt", ios::app);
					if (plik.good() == true)
					{
						plik << imie1 << " remis " << imie2 << endl;

					}
					else cout << "Blad" << endl;
					plik.close();

					system("pause");
					break;
				}
				do
				{
					cout << imie2 << " wybierz miejsce " << endl;
					cin >> pozycjaX;
					cin >> pozycjaY;
					symbol = 'O';
				} while (plansza[pozycjaX - 1][pozycjaY - 1] == 'X' || plansza[pozycjaX - 1][pozycjaY - 1] == 'O');
				gra(symbol, pozycjaX - 1, pozycjaY - 1, plansza);
				if (sprawdzanie(plansza, symbol) == 1)
				{
					cout << "Wygrana gracza o imieniu " << imie2 << endl;
					plik.open("Wyniki.txt", ios::app);
					if (plik.good() == true)
					{
						plik << imie2 << " wygral z " << imie1 << endl;

					}
					else cout << "Blad" << endl;
					plik.close();



					system("pause");
					break;
				}



			}

			system("cls");




			break;
		}
		case 2:
		{
			cout << "Wybrano historie wynikow" << endl;
			plik.open("Wyniki.txt", ios::in);
			if (plik.good() == true)
			{
				string bufor;
				while (!plik.eof())
				{
					getline(plik, bufor);
					cout << bufor << endl;

				}

			}
			else cout << "Blad" << endl;
			plik.close();
			system("pause");
			system("cls");
			break;
		}

		case 3:
		{
			cout << "Wyjscie" << endl;

			return 0;
			break;
		}

		}

	}




	system("PAUSE");
	return 0;
}