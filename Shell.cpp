#include "Shell.h"

using namespace std;




Shell::Shell()
{
	clog << "Shell initialized" << endl;
	idle.ustawStatus(3);
	kolejkaGotowych.dodajDoKolejki(&idle);
}

void Shell::CP(std::string nazwa, std::string rodzic, std::string program)
{
	if (zarzadzanieProcesami.znajdzProces(nazwa) == nullptr) {
		zarzadzanieProcesami.dodajProces(nazwa, rodzic);

		if (program == "") {
			;
		}
		else
			interpreter.WpiszDoRam(zarzadzanieProcesami.znajdzProces(nazwa), program);
	}
	else std::clog << "Proces istnieje" << std::endl;
}

void Shell::DP(std::string nazwa)
{
	if (nazwa == "init") {
		clog << "Zakaz usuwania procesu init" << endl;
	}
	else if (zarzadzanieProcesami.znajdzProces(nazwa) == nullptr)
		clog << "Proces nie istnieje" << endl;
	else
		zarzadzanieProcesami.usunProces(nazwa);
}


void Shell::BC(std::string nazwa)
{
	if (zarzadzanieProcesami.znajdzProces(nazwa) != nullptr)
		zarzadzanieProcesami.wyswietlProces(nazwa);
	else
		clog << "Proces o danej nazwie nie istnieje" << endl;
}

void Shell::MP(std::string co, std::string dokad)
{
	if (zarzadzanieProcesami.znajdzProces(co) != nullptr && zarzadzanieProcesami.znajdzProces(dokad) != nullptr) {
		zarzadzanieProcesami.przeniesProces(co, dokad);
	}
	else
		clog << "Jeden z procesow lub oba nie istnieja" << endl;
}

void Shell::GO()
{
	if (zarzadzanieProcesami.iloscProcesow() != 1 && kolejkaGotowych.rozmiarKolejki()>0) {

		interpreter.PobierzRozkaz(kolejkaGotowych.glowa->proces);
		if (interpreter.Rozkaz != "") {
			std::cout << " ******************************" << std::endl;
			std::cout << " Proces aktywny: " << kolejkaGotowych.glowa->proces->dajNazwe() << std::endl;
			std::cout << " ROZKAZ: " << interpreter.Rozkaz << std::endl;
		}
		interpreter.WykonywanieProgramu();

	}
	else std::cout << "Nie ma zaladowanego programu" << std::endl;
	//interpreter.StanRejestrow();
}

void Shell::PP()
{
	zarzadzanieProcesami.wyswietlWszystkieProcesy();
}

void Shell::MC(int adres, int rozmiar)
{
	ram.showRange(adres, rozmiar);
}

void Shell::MS()
{
	ram.showRam();
}


void Shell::MF(std::string nazwa, std::string rozszerzenie, std::string nazwaFolderu)
{
	short wyjscie = dysk.utworzPlik(nazwa, rozszerzenie, nazwaFolderu);
	obsluzBledy(wyjscie);
}

void Shell::DF(std::string nazwa, std::string rozszerzenie, std::string nazwaFolderu)
{
	short wyjscie = dysk.usunPlik(nazwa, rozszerzenie, nazwaFolderu);
	obsluzBledy(wyjscie);
}

void Shell::RF(std::string nazwa, std::string rozszerzenie, std::string nowaNazwa, std::string nazwaFolderu)
{
	short wyjscie = dysk.zmienNazwePliku(nazwa, rozszerzenie, nowaNazwa, nazwaFolderu);
	obsluzBledy(wyjscie);
}

void Shell::SF(std::string nazwa, std::string rozszerzenie, std::string dane, PCB * proces, std::string nazwaFolderu)
{
	short wyjscie = dysk.zapiszDoPliku(nazwa, rozszerzenie, dane, proces, nazwaFolderu);
	obsluzBledy(wyjscie);
	dysk.zamknijPlik(nazwa, rozszerzenie, proces, nazwaFolderu);
}

void Shell::PF(std::string nazwa, std::string rozszerzenie, PCB * proces, std::string nazwaFolderu)
{
	pobieDane wyj;
	wyj = dysk.pobierzDane(nazwa, rozszerzenie, proces, nazwaFolderu);
	obsluzBledy(wyj.blad);
	cout << wyj.dane << endl;
	dysk.zamknijPlik(nazwa, rozszerzenie, proces, nazwaFolderu);
}

void Shell::XF(std::string nazwa, std::string rozszerzenie, PCB * proces, std::string nazwaFolderu)
{
	short wyjscie = dysk.otworzStratnie(nazwa, rozszerzenie, proces, nazwaFolderu);
	obsluzBledy(wyjscie);
	dysk.zamknijPlik(nazwa, rozszerzenie, proces, nazwaFolderu);
}

void Shell::OF(std::string nazwa, std::string rozszerzenie, PCB * proces, std::string nazwaFolderu)
{
	pobieDane wyj;
	wyj = dysk.pobierzDane(nazwa, rozszerzenie, proces, nazwaFolderu);
	obsluzBledy(wyj.blad);
	cout << wyj.dane << endl;
}

void Shell::CF(std::string nazwa, std::string rozszerzenie, PCB * proces, std::string nazwaFolderu)
{
	dysk.zamknijPlik(nazwa, rozszerzenie, proces, nazwaFolderu);
}




void Shell::MD(std::string nazwa, std::string nazwaNadrzednego)
{
	short wyjscie = dysk.utworzFolder(nazwa, nazwaNadrzednego);
	obsluzBledy(wyjscie);
}

void Shell::AD(std::string nazwaDocelowego, std::string nazwaPliku, std::string rozszerzenie, std::string nazwaFolderuZPlikiem)
{
	short wyjscie = dysk.dodajPlikDoKatalogu(nazwaDocelowego, nazwaPliku, rozszerzenie, nazwaFolderuZPlikiem);
	obsluzBledy(wyjscie);
}

void Shell::DD(std::string nazwa)
{
	int pozycja = dysk.znajdzFolder(nazwa);
	if (pozycja == -1) {
		clog << "Folder nie istnieje" << endl;
	}
	else {
		short wyjscie = dysk.usunFolder(pozycja);
		obsluzBledy(wyjscie);
	}
}

void Shell::FD(std::string nazwa)
{
	dysk.znajdzFolder(nazwa);
}

void Shell::PT()
{
	dysk.wypiszDrzewo();
}

void Shell::PD()
{
	dysk.wypiszDysk();
}

void Shell::PV()
{
	dysk.wypiszWektorBitowy();
}

void Shell::PN()
{
	dysk.wypiszTabliceIwezelow();
}

void Shell::PX()
{
	dysk.wypiszTabliceWpisow();
}

void Shell::RQ()
{
	kolejkaGotowych.wyswietlKolejke();
}

void Shell::WQ()
{
	kolejkaOczekujacych.wyswietlKolejke();
}

void Shell::RB()
{
	ram.printBLOCKS();
}

void Shell::help()
{
	komendy.open("help.txt");
	if (!komendy.good()) {
		cout << "Brak pliku z komendami" << endl;
	}
	string linia;
	clog << "______________________SPIS KOMEND______________________" << endl << endl;
	while (getline(komendy, linia)) {
		clog << linia << endl;
	}

	komendy.close();
}


void Shell::exit() {
	cout << "wylaczanka";
	wlaczone = false;
}


void Shell::czytajWejscie(std::string wejscie)
{
	istringstream buffer(wejscie);
	istream_iterator<string> beg(buffer), end;
	vector<string>args(beg, end);
	if (wejscie.size() == 0) {
		return;
	}
	string komenda = args[0];
	//cout << args[0] << endl << args[1] << endl;

	if (komenda == "CP") {
		if (args.size() < 2)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			//ustalamy rodzica
			if (args.size() != 3) {
				args.push_back("init");
			}
			//program ""
			if (args.size() != 4)
				args.push_back("");
			CP(args[1], args[2], args[3]);
		}
	}
	else if (komenda == "DP") {
		if (args.size() != 2)
			cout << "niepoprawne uzycie komendy" << endl;
		else
			DP(args[1]);
	}

	else if (komenda == "BC") {
		if (args.size() != 2)
			cout << "niepoprawne uzycie komendy" << endl;
		else
			BC(args[1]);
	}
	else if (komenda == "PP") {
		PP();
	}
	else if (komenda == "MF") {
		if (args.size() <3)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			if (args.size() != 4)
				args.push_back("Dysk");
			MF(args[1], args[2], args[3]);
		}
	}
	else if (komenda == "DF") {
		if (args.size() <3)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			if (args.size() != 4)
				args.push_back("Dysk");
			if (dysk.znajdzPlik(args[1], args[2]) == -1) {
				clog << "Nie znaleziono pliku." << endl;
				return;
			}
			else
				DF(args[1], args[2], args[3]);
		}
	}
	else if (komenda == "RF") {
		if (args.size() < 4)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			if (args.size() != 5)
				args.push_back("Dysk");
			if (dysk.znajdzPlik(args[1], args[2]) == -1) {
				clog << "Nie znaleziono pliku." << endl;
				return;
			}
			else
				RF(args[1], args[2], args[3], args[4]);
		}
	}

	else if (komenda == "MD") {
		if (args.size() <2)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			if (args.size() != 3)
				args.push_back("Dysk");
			MD(args[1], args[2]);
		}
	}
	else if (komenda == "AD") {
		if (args.size() <4)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			if (args.size() != 5)
				args.push_back("Dysk");
			AD(args[1], args[2], args[3], args[4]);
		}
	}
	else if (komenda == "DD") {
		if (args.size() != 2)
			cout << "niepoprawne uzycie komendy" << endl;
		else if (args[1] == "Dysk") {
			clog << "Nie mozna usunac katalogu glownego" << endl;
		}
		else
			DD(args[1]);
	}
	else if (komenda == "FD") {
		if (args.size() != 2)
			cout << "niepoprawne uzycie komendy" << endl;
		else
			FD(args[1]);
	}
	else if (komenda == "PT") {
		PT();
	}
	else if (komenda == "PD") {
		PD();
	}
	else if (komenda == "PV") {
		PV();
	}
	else if (komenda == "PN") {
		PN();
	}
	else if (komenda == "PX") {
		PX();
	}
	else if (komenda == "MS") {
		MS();
	}
	else if (komenda == "MC") {
		if (args.size() != 3)
			cout << "niepoprawne uzycie komendy" << endl;
		else
			MC(stoi(args[1]), stoi(args[2]));
	}

	else if (komenda == "LS") {
		if (args.size() != 2)
			cout << "niepoprawne uzycie komendy" << endl;
		else
			ladujSkrypt(args[1]);
	}
	else if (komenda == "exit") {
		exit();
	}
	else if (komenda == "SF") {
		if (args.size() < 4)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			if (args.size() != 5)
				args.push_back("Dysk");
			if (dysk.znajdzPlik(args[1], args[2]) == -1) {
				clog << "Nie znaleziono pliku." << endl;
				return;
			}
			else {
				CP("plikcostam", "init", "");
				SF(args[1], args[2], args[3], zarzadzanieProcesami.znajdzProces("plikcostam"), args[4]);
				if (zarzadzanieProcesami.znajdzProces("plikcostam")->dajBlad() == 1) {
					clog << "Brak dostepu do pliku" << endl;
				}
				DP("plikcostam");
			}

		}
	}
	else if (komenda == "PF") {
		if (args.size() < 3)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			if (args.size() != 4)
				args.push_back("Dysk");
			if (dysk.znajdzPlik(args[1], args[2]) == -1) {
				clog << "Nie znaleziono pliku." << endl;
				return;
			}
			else {
				CP("plikcostam", "init", "");
				PF(args[1], args[2], zarzadzanieProcesami.znajdzProces("plikcostam"), args[3]);
				if (zarzadzanieProcesami.znajdzProces("plikcostam")->dajBlad() == 1) {
					clog << "Brak dostepu do pliku" << endl;
				}
				DP("plikcostam");
			}
		}
	}

	else if (komenda == "XF") {
		if (args.size() < 3)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			if (args.size() != 4)
				args.push_back("Dysk");
			if (dysk.znajdzPlik(args[1], args[2]) == -1) {
				clog << "Nie znaleziono pliku." << endl;
				return;
			}
			else {
				CP("plikcostam", "init", "");
				XF(args[1], args[2], zarzadzanieProcesami.znajdzProces("plikcostam"), args[3]);
				if (zarzadzanieProcesami.znajdzProces("plikcostam")->dajBlad() == 1) {
					clog << "Brak dostepu do pliku" << endl;
				}
				DP("plikcostam");
			}
		}
	}
	else if (komenda == "OF") {
		if (args.size() < 3)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			if (args.size() != 4)
				args.push_back("Dysk");
			if (dysk.znajdzPlik(args[1], args[2]) == -1) {
				clog << "Nie znaleziono pliku." << endl;
				return;
			}
			else {

				bool nazwaZajeta = true;
				std::string temp = random_string(8);
				PlikProces temp2 = { temp, args[1], args[2] };
				while (nazwaZajeta) {
					for (auto a : PlikiProcesy) {
						if (a.nazwaProcesu == temp) {
							temp = random_string(8);
						}
					}
					nazwaZajeta = false;
				}
				temp2.nazwaProcesu = temp;
				PlikiProcesy.push_back(temp2);

				CP(temp, "init", "");

				OF(args[1], args[2], zarzadzanieProcesami.znajdzProces(temp), args[3]);
				if (zarzadzanieProcesami.znajdzProces("plikcostam")->dajBlad() == 1) {
					clog << "Brak dostepu do pliku" << endl;
				}
			}
		}
	}

	else if (komenda == "CF") {
		if (args.size() < 3)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			if (args.size() != 4)
				args.push_back("Dysk");
			if (dysk.znajdzPlik(args[1], args[2]) == -1) {
				clog << "Nie znaleziono pliku." << endl;
				return;
			}
			else {
				std::string temp = "";

				vector<string> bledy = dysk.bledy();

				for (auto e : bledy) {
					std::clog << e << std::endl;
				}
				for (auto e : PlikiProcesy) {
					if (e.nazwaPliku == args[1] && e.rozszerzeniePliku == args[2]) {
						temp = e.nazwaProcesu;
						break;
					}
				}
				if (zarzadzanieProcesami.znajdzProces(temp) == nullptr) {
					clog << "Plik nie jest otwarty" << endl;
					return;
				}
				if (zarzadzanieProcesami.znajdzProces(temp)->dajBlad() == 0) {
					CF(args[1], args[2], zarzadzanieProcesami.znajdzProces(temp), args[3]);
					DP(temp);
					short x = -1;
					//	this->numeryIwezlow.erase(std::find(this->numeryIwezlow.begin(), this->numeryIwezlow.end(), numer) + 0);
					for (auto e : PlikiProcesy) {
						x++;
						if (e.nazwaProcesu == temp)
							break;
					}
					PlikiProcesy.erase(PlikiProcesy.begin() + x);
				}
				else
					std::clog << "Blad procesu: " << temp << " = " << zarzadzanieProcesami.znajdzProces(temp)->dajBlad() << std::endl;



			}
		}
	}
	else if (komenda == "GO") {
		GO();
	}
	else if (komenda == "RQ") {
		RQ();
	}
	else if (komenda == "WQ") {
		WQ();
	}
	else if (komenda == "RB") {
		RB();
	}
	else if (komenda == "MP") {
		if (args.size() != 3)
			cout << "niepoprawne uzycie komendy" << endl;
		else
			MP(args[1], args[2]);
	}
	else if (komenda == "help") {
		help();
	}
	else if (komenda == "test") {
		if (args.size() != 2)
			cout << "niepoprawne uzycie komendy" << endl;
		else
			zarzadzanieProcesami.usunProces(stoi(args[1]));
	}
	else {
		clog << "Niepoprawna komenda. Sprawdz 'help'" << endl;
	}
	args.clear();

}

void Shell::ladujSkrypt(string nazwa)
{
	string komenda = "";
	skrypt.open(nazwa + ".txt");
	if (!skrypt.good()) {
		cout << "Brak pliku" << endl;
	}
	string linia;
	vector<vector<string>>polecenia;
	vector<string>polecenie;

	while (getline(skrypt, linia)) {
		istringstream buffer(linia);
		istream_iterator<string> beg(buffer), end;
		vector<string>polecenie(beg, end);
		polecenia.push_back(polecenie);
		polecenie.clear();

	}


	for (int i = 0; i < polecenia.size(); i++) {
		for (int j = 0; j < polecenia[i].size(); j++) {

			//cout << polecenia[i][j];
			if (j != polecenia[i].size())
				komenda = komenda + polecenia[i][j] + " ";
			else
				komenda = komenda + polecenia[i][j];
		}
		czytajWejscie(komenda);
		komenda = "";
		//cout << endl;
	}

	polecenia.clear();
	skrypt.close();
}

void Shell::obsluzBledy(short blad)
{
	//  1 : wszystko ok;
	// -1 : B�edna nazwa folderu
	//- 2 : Nie odnaleziono pliku.
	//- 3 : Semafor zablokowany, brak dostepu.
	//- 4 : Brak miejsca na dysku.
	//- 5 : W folderze nie mozna utworzyc nowych podfolderow.
	//- 6 : Nazwa nie jest jednoznaczna.
	if (blad == 1) {
		//...dobrze
	}
	else if (blad == -1) {
		clog << "Bledna nazwa folderu" << endl;
	}
	else if (blad == -2) {
		clog << "Nie odnaleziono pliku" << endl;
	}
	else if (blad == -3) {
		//...PCB
	}
	else if (blad == -4) {
		clog << "Brak miejsca na dysku" << endl;
	}
	else if (blad == -5) {
		clog << "W folderze nie mozna utworzyc nowych podfolderow" << endl;
	}
	else if (blad == -6) {
		clog << "Nazwa nie jest jednoznaczna" << endl;
	}
	else
	{
		clog << "Blad nie jest rozpatrywany" << endl;
	}
}

std::string Shell::random_string(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}