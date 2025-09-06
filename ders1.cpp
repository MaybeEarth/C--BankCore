#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


void kayıt() {
	int sıra = 0;
	ifstream d("kayıt.txt");
	string sır;
	if (d.is_open()) {
		while (getline(d, sır)) {
			sıra++;
		}
	}
	string ad;
	string tc;
	cout << "Lütfen ilk önce adını griin:\n" << endl;
	cin >> ad;
	cout << "Tc numaranızı girin:\t" << endl;
	cin >> tc;
	while (tc.length() != 2) {
		cout << "Tc geçersiz yeniden girin :\t" << endl;
		cin >> tc;
	}
	ofstream x("kayıt.txt", ios::app);
	if (x.is_open()) {
		x << "\n" << sıra << ad << tc;
	}

	x.close();
	ofstream y("money.txt", ios::app);
	if (y.is_open()) {
		y << "\n" << sıra << ":" << "0" << "TL";
	}
	y.close();
}
void gos() {
	ifstream p("kayıt.txt");
	string de;
	if (p.is_open()) {
		while (getline(p, de)) {
			cout << de << endl;
		}
	}
}
bool regıs() {
	string kullan, password,tccc;
	cout << "-----------------------------------------"<<endl;
	cout << "Maybe Yapının Özel Banka Uygulamasına Hoş Geldiniz"<<endl;
	cout << "Lütfen Kayıt etmek istediğiniz kullanıcı adını girin" << endl;
	cin >> kullan;
	cout << "Lütfen Kayıt etmek istediğiniz şifreyi girin" << endl;
	cin >> password;
	cout << "Lütfen Kayıt etmek istediğiniz tc girin" << endl;
	cin >> tccc;
	while (2 != tccc.length()) {
		cout << "lütfen tc 2 haneli olacakşekilde yapın" << endl;
		cin >> tccc;
	}
	int sıra = 0;
	ifstream d("kayıt.txt");
	string sır;
	while (getline(d, sır)) {
		sıra++;
	}
	d.close();
	ofstream x("kayıt.txt", ios::app);
	if (x.is_open()) {
		x << sıra << kullan << tccc << "\n";
	}
	x.close();
	ofstream ı("money.txt", ios::app);
	if (ı.is_open()) {
		ı << sıra << ":0TL" << "\n";
	}
	ı.close();
	ofstream o("log.txt", ios::app);
	if (o.is_open()) {
		o << sıra << "." << kullan <<":" << password << "\n";
		}
	o.close();
	return true;

}
void money() {
	int ıd;
	int sıra = 0;
	int kayıt = 0;
	cout << "Görmek istediğinz id girin \t";
	cin >> ıd;
	ifstream r("kayıt.txt");
	string sıraa;
	if (r.is_open()) {
		while (getline(r, sıraa)) {
			kayıt++;
		}
	}
	while (ıd >= kayıt) {
		cout << "hatalı griiş ıd doğru griin";
		cin >> ıd;
	}
	ifstream d("money.txt");
	string sır;
	if (d.is_open()) {
		while (getline(d, sır)) {
			if (sıra == ıd) {
				cout << sır;
				break;
			}
			else
			{
				sıra++;
			}

		}

	}
}
void para() {
	int id;
	int toplamKullanici = 0;
	cout << "Lütfen ID girin: ";
	cin >> id;

	ifstream kayit("kayıt.txt");
	string satir;
	while (getline(kayit, satir)) {
		toplamKullanici++;
	}
	kayit.close();

	while (id >= toplamKullanici) {
		cout << "Geçersiz ID! Yeniden girin: ";
		cin >> id;
	}

	ifstream paraDosya("money.txt");
	vector<string> tumSatirlar;
	while (getline(paraDosya, satir)) {
		tumSatirlar.push_back(satir);
	}
	paraDosya.close();

	string paraSatiri = tumSatirlar[id];

	size_t ikiNokta = paraSatiri.find(':');
	string bakiyeStr = paraSatiri.substr(ikiNokta + 1);
	size_t tlPoz = bakiyeStr.find("TL");
	if (tlPoz != string::npos) {
		bakiyeStr = bakiyeStr.substr(0, tlPoz);
	}
	float bakiye = stof(bakiyeStr);

	int secim;
	float miktar;
	cout << "Mevcut bakiye: " << bakiye << " TL\n";
	cout << "1 - Para Yatır\n2 - Para Çek\nSeçiminiz: ";
	cin >> secim;

	cout << "Miktar: ";
	cin >> miktar;

	if (secim == 1) {
		bakiye += miktar;
	}
	else if (secim == 2) {
		while (miktar > bakiye) {
			cout << "Yetersiz bakiye!.Yeniden girin" << endl;
			cin >> miktar;
		}
		bakiye -= miktar;
	}
	else {
		cout << "Geçersiz işlem seçimi!" << endl;
		return;
	}

	tumSatirlar[id] = to_string(id) + ":" + to_string((int)bakiye) + "TL";

	ofstream yaz("money.txt", ios::trunc);
	for (const auto& s : tumSatirlar) {
		yaz << s << "\n";
	}
	yaz.close();

	cout << "Yeni bakiye: " << bakiye << " TL" << endl;
}

string lo() {

	vector<string> ve;
	string kull, pass;
	int sayma = 0;
	cout << "Giriş yapmak için kullanıcı adını girin:\t";
	cin >> kull;
	cout << "Giriş yapmak için şifreyi girin:\t";
	cin >> pass;
	ifstream ope("log.txt");
	string okuma;
	while (getline(ope, okuma)) {
		ve.push_back(okuma);
		sayma++;
	}
	ope.close();
	string verkull[100], verpass[100],verıd[100];
	for (int y = 0; sayma > y; y++) {
		string s = ve[y];
		verıd[y] = ve[y].substr(0, ve[y].find('.'));
		verkull[y] = ve[y].substr(ve[y].find('.')+1,ve[y].find(':')- ve[y].find('.')-1);
		verpass[y] = ve[y].substr(ve[y].find(':')+1);
	}
	bool bulundu = false;
	for (int i = 0; i < sayma; i++) {
		if (kull == verkull[i]) {
			while (pass != verpass[i]) {
				cout << "şifreniz yanlış yeniden gir:\t";
				cin >> pass;
			}
			bulundu = true;
			break;
		}
	}
	if (bulundu == true) {
		return "true";
	}
	else {
		return "false";
	}


}


int main() {
	setlocale(LC_ALL, "Turkish");
	int mai;
	cout << "----------------------------------"<<endl;
	cout << "Login için : 1" << endl;
	cout << "Kayıt için : 2" << endl;
	cin >> mai;
	switch (mai) {
	case 1: {
		if (lo() == "true") {
			int secim;

			do {
				cout << "\n--- Menü ---\n";
				cout << "1 - Yeni Kayıt\n";
				cout << "2 - Kayıtları Göster\n";
				cout << "3 - Bakiye Görüntüle (ID ile)\n";
				cout << "4 - Para Yatır / Çek\n";
				cout << "0 - Çıkış\n";
				cout << "Seçiminiz: ";
				cin >> secim;

				switch (secim) {
				case 1: kayıt(); break;
				case 2: gos(); break;
				case 3: money(); break;
				case 4: para(); break;
				case 0: cout << "Programdan çıkılıyor...\n"; break;
				default: cout << "Geçersiz seçim! Lütfen tekrar deneyin.\n";
				}

			} while (secim != 0);
		}
		else {
			cout << "kullanıcı adı şifre yanlış";
		}
		break;
	}
	case 2: {
		if (regıs() == true) {
			if (lo() == "true") {
				int secim;

				do {
					cout << "\n--- Menü ---\n";
					cout << "1 - Yeni Kayıt\n";
					cout << "2 - Kayıtları Göster\n";
					cout << "3 - Bakiye Görüntüle (ID ile)\n";
					cout << "4 - Para Yatır / Çek\n";
					cout << "0 - Çıkış\n";
					cout << "Seçiminiz: ";
					cin >> secim;

					switch (secim) {
					case 1: kayıt(); break;
					case 2: gos(); break;
					case 3: money(); break;
					case 4: para(); break;
					case 0: cout << "Programdan çıkılıyor...\n"; break;
					default: cout << "Geçersiz seçim! Lütfen tekrar deneyin.\n";
					}

				} while (secim != 0);
			}
			else {
				cout << "Kullanıcı adı şifre yanlış/Lütfen Yeniden Deneyin";
			}
		}
		
	}
		  break;
	}
	return 0;
}
