#include "Shell.h"

using namespace std;




Shell::Shell()
{
	clog << "Shell initialized" << endl;

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
	zarzadzanieProcesami.usunProces(nazwa);
}


void Shell::BC(std::string nazwa)
{
	zarzadzanieProcesami.wyswietlProces(nazwa);
}

void Shell::GO()
{
	interpreter.PobierzRozkaz(kolejkaGotowych.glowa->proces);
	std::cout << " ROZKAZ: " << interpreter.Rozkaz << std::endl;
	interpreter.WykonywanieProgramu();
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
	dysk.utworzPlik(nazwa, rozszerzenie, nazwaFolderu);
}

void Shell::DF(std::string nazwa, std::string rozszerzenie, std::string nazwaFolderu)
{
	dysk.usunPlik(nazwa, rozszerzenie, nazwaFolderu);
}

void Shell::RF(std::string nazwa, std::string rozszerzenie, std::string nowaNazwa, std::string nazwaFolderu)
{
	dysk.zmienNazwePliku(nazwa, rozszerzenie, nowaNazwa, nazwaFolderu);
}

void Shell::SF(std::string nazwa, std::string rozszerzenie, std::string dane, PCB * proces, std::string nazwaFolderu)
{
	dysk.zapiszDoPliku(nazwa, rozszerzenie, dane, proces, nazwaFolderu);
	dysk.zamknijPlik(nazwa, rozszerzenie, proces, nazwaFolderu);
}

void Shell::PF(std::string nazwa, std::string rozszerzenie, PCB * proces, std::string nazwaFolderu)
{

	string wyjscie = dysk.pobierzDane(nazwa, rozszerzenie, proces, nazwaFolderu);
	cout << wyjscie << endl;
	dysk.zamknijPlik(nazwa, rozszerzenie, proces, nazwaFolderu);
}

void Shell::XF(std::string nazwa, std::string rozszerzenie, PCB * proces, std::string nazwaFolderu)
{
	dysk.otworzStratnie(nazwa, rozszerzenie, proces, nazwaFolderu);
	dysk.zamknijPlik(nazwa, rozszerzenie, proces, nazwaFolderu);
}

void Shell::OF(std::string nazwa, std::string rozszerzenie, PCB * proces, std::string nazwaFolderu)
{
	string wyjscie = dysk.pobierzDane(nazwa, rozszerzenie, proces, nazwaFolderu);

	cout << wyjscie << endl;
}

void Shell::CF(std::string nazwa, std::string rozszerzenie, PCB * proces, std::string nazwaFolderu)
{
	dysk.zamknijPlik(nazwa, rozszerzenie, proces, nazwaFolderu);
}




void Shell::MD(std::string nazwa, std::string nazwaNadrzednego)
{
	dysk.utworzFolder(nazwa, nazwaNadrzednego);
}

void Shell::AD(std::string nazwaDocelowego, std::string nazwaPliku, std::string rozszerzenie, std::string nazwaFolderuZPlikiem)
{
	dysk.dodajPlikDoKatalogu(nazwaDocelowego, nazwaPliku, rozszerzenie, nazwaFolderuZPlikiem);
}

void Shell::DD(std::string nazwa)
{
	int pozycja = dysk.znajdzFolder(nazwa);
	dysk.usunFolder(pozycja);
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


void Shell::exit() {
	cout << "wylaczanka";
	wlaczone = false;
}


void Shell::czytajWejscie(std::string wejscie)
{
	istringstream buffer(wejscie);
	istream_iterator<string> beg(buffer), end;
	vector<string>args(beg, end);

	string komenda = args[0];
	//cout << args[0] << endl << args[1] << endl;
	if (komenda == "CP") {
		if (args.size() < 3)
			cout << "niepoprawne uzycie komendy" << endl;
		else
			if (args.size() != 4)
				args.push_back("");
			CP(args[1], args[2], args[3]);
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
			DF(args[1], args[2], args[3]);
		}
	}
	else if (komenda == "RF") {
		if (args.size() < 4)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			if (args.size() != 5)
				args.push_back("Dysk");
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

	else if (komenda == "open") {
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
			CP("plikcostam", "init", "");
			SF(args[1], args[2], args[3], zarzadzanieProcesami.znajdzProces("plikcostam"), args[4]);
			DP("plikcostam");

		}
	}
	else if (komenda == "PF") {
		if (args.size() < 3)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			if (args.size() != 4)
				args.push_back("Dysk");
			CP("plikcostam", "init", "");
			PF(args[1], args[2], zarzadzanieProcesami.znajdzProces("plikcostam"), args[3]);
			DP("plikcostam");

		}
	}

	else if (komenda == "XF") {
		if (args.size() < 3)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			if (args.size() != 4)
				args.push_back("Dysk");
			CP("plikcostam", "init", "");
			XF(args[1], args[2], zarzadzanieProcesami.znajdzProces("plikcostam"), args[3]);
			DP("plikcostam");
		}
	}
	else if (komenda == "OF") {
		if (args.size() < 3)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			if (args.size() != 4)
				args.push_back("Dysk");
			

			std::string temp = random_string(8);
			CP(temp, "init", "");
			PlikProces temp2 = { temp, args[1], args[2] };
			PlikiProcesy.push_back(temp2);
			OF(args[1], args[2], zarzadzanieProcesami.znajdzProces(temp), args[3]);

		}
	}

	else if (komenda == "CF") {
		if (args.size() < 3)
			cout << "niepoprawne uzycie komendy" << endl;
		else {
			if (args.size() != 4)
				args.push_back("Dysk");

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
							std::clog << "Blad procesu: " <<temp<<" = "<< zarzadzanieProcesami.znajdzProces(temp)->dajBlad() << std::endl;

					
								
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
