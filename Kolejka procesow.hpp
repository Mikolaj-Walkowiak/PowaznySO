#pragma once
#include "ZarzadzanieProcesami.h"

struct Wezel
{
	PCB* proces;
	Wezel* nastepny;
	Wezel(PCB* proces);
	Wezel();
};

class KolejkaProcesow
{
public:
	std::string nazwa;
	Wezel *glowa, *ogon;	//glowa to ten aktywny process
	KolejkaProcesow(std::string);
	~KolejkaProcesow();

	//Zarz�dzanie procesami
	void dodajDoKolejki(PCB*);

	//Interpreter
	void uruchomEkspedytor(const bool&);	//sprawdza czy proces si� wykona�, je�li tak to usuwa go z kolejki i na jego miejsce wchodzi kolejny,
											//je�li nie to proces l�duje na ko�cu kolejki
	//Shell
	void usunProces(const short&);	//szuka proces po PID i usuwa go z kolejki
	void wyswietlKolejke();			//do zmiany - musi wy�wietla� �adniej procesy np z wykorzystaniem funkcji Zarz�dzaniaProcesami

	//INNE
	short rozmiarKolejki();			//zwraca liczb� proces�w w kolejce
	void sprawdzBezczynnosc();		//sprawdza czy w kolejce znajduje si� jaki� proces, je�li nie to ustawia proces bezczynno�ci
	void usunZPoczatku();
	void usunZKonca();
};
//DLA TYCH CO USYPIAJ� I BUDZ�
void zmienKolejke(PCB*);	//je�li proces jest na CZELE kolejki gotowych to wstawia go na koniec oczekuj�cych i odwrotnie
void zmienKolejke(Wezel*);
void uspijProces(PCB*);		//usuwa proces z DOWOLNEGO MIEJSCA kolejki gotowych je�li tam jest i wstawia go na koniec oczekuj�cych
void uspijProces(Wezel*);
void obudzProces(PCB*);		//usuwa proces z DOWOLNEGO MIEJSCA kolejki oczekuj�cych je�li tam jest i wstawia go na koniec gotowych
void obudzProces(Wezel*);

//tymczasowy proces bezczynnosci

//globalne kolejki procesow
extern KolejkaProcesow kolejkaGotowych;
extern KolejkaProcesow kolejkaOczekujacych;


