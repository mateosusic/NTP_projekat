#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Strukture
struct Dionica {
    string puniNaziv;
    string skracenica;
    double vrijednost;
};


struct Korisnik {
    string ime;
    string prezime;
    int id;
    double kapital;
    string korisnickoIme;
    string lozinka;
    vector<Dionica> dionice;
};

// Funkcija za unos novog korisnika
Korisnik unosKorisnika() {
    Korisnik noviKorisnik;
    cout << "Unesite ime korisnika: ";
    cin >> noviKorisnik.ime;

    cout << "Unesite prezime korisnika: ";
    cin >> noviKorisnik.prezime;

    cout << "Unesite ID korisnika: ";
    cin >> noviKorisnik.id;

    cout << "Unesite pocetni kapital korisnika: ";
    cin >> noviKorisnik.kapital;

    cout << "Unesite korisnicko ime: ";
    cin >> noviKorisnik.korisnickoIme;

    cout << "Unesite lozinku: ";
    cin >> noviKorisnik.lozinka;

    // Dodaje korisnika u datoteku "korisnici.txt"
    ofstream datoteka("korisnici.txt", ios::app);
    if (datoteka.is_open()) {
        datoteka << noviKorisnik.korisnickoIme << " " << noviKorisnik.lozinka << endl;
        datoteka.close();
        cout << "Novi korisnik je uspjesno unesen." << endl;
    } else {
        cout << "Greska pri otvaranju datoteke." << endl;
    }

    return noviKorisnik;
}

// Funkcija za provjeru korisnika
bool provjeriKorisnika(const string& korisnickoIme, const string& lozinka) {
    ifstream datoteka("korisnici.txt");
    if (datoteka.is_open()) {
        string unesenoKorisnickoIme, unesenaLozinka;
        while (datoteka >> unesenoKorisnickoIme >> unesenaLozinka) {
            if (unesenoKorisnickoIme == korisnickoIme && unesenaLozinka == lozinka) {
                datoteka.close();
                return true;
            }
        }
        datoteka.close();
    }
    return false;
}
// Funkcija za dodavanje kapitala korisniku
void dodajKapital(Korisnik& korisnik) {
    double dodatniKapital;
    cout << "Unesite iznos kapitala za dodavanje: ";
    cin >> dodatniKapital;
    korisnik.kapital += dodatniKapital;

    // Ažurirajte korisnika u datoteci "korisnici.txt"
    ifstream datoteka("korisnici.txt");
    ofstream privremenaDatoteka("privremeno.txt");
    if (datoteka.is_open() && privremenaDatoteka.is_open()) {
        string korisnickoIme, lozinka, kapital;
        while (datoteka >> korisnickoIme >> lozinka >> kapital) {
            if (korisnickoIme == korisnik.korisnickoIme && lozinka == korisnik.lozinka) {
                privremenaDatoteka << korisnickoIme << " " << lozinka << " " << korisnik.kapital << endl;
            } else {
                privremenaDatoteka << korisnickoIme << " " << lozinka << " " << kapital << endl;
            }
        }
        datoteka.close();
        privremenaDatoteka.close();
        remove("korisnici.txt");
        rename("privremeno.txt", "korisnici.txt");
        cout << "Kapital je uspjesno dodan." << endl;
    } else {
        cout << "Greska pri otvaranju datoteke." << endl;
    }
}

// Funkcija za prodaju dionica
void prodajaDionica(Korisnik& korisnik) {
    if (korisnik.dionice.empty()) {
        cout << "Korisnik nema dionica za prodaju." << endl;
        return;
    }

    cout << "Dostupne dionice za prodaju:" << endl;
    for (int i = 0; i < korisnik.dionice.size(); i++) {
        cout << i + 1 << ". " << korisnik.dionice[i].puniNaziv << " (" << korisnik.dionice[i].skracenica << ")" << endl;
    }

    int index;
    cout << "Unesite redni broj dionice koju želite prodati: ";
    cin >> index;

    if (index >= 1 && index <= korisnik.dionice.size()) {
        Dionica prodanaDionica = korisnik.dionice[index - 1];
        korisnik.dionice.erase(korisnik.dionice.begin() + (index - 1));
        korisnik.kapital += prodanaDionica.vrijednost;

        // Ažurirajte korisnika u datoteci "korisnici.txt"
        ifstream datoteka("korisnici.txt");
        ofstream privremenaDatoteka("privremeno.txt");
        if (datoteka.is_open() && privremenaDatoteka.is_open()) {
            string korisnickoIme, lozinka, kapital;
            while (datoteka >> korisnickoIme >> lozinka >> kapital) {
                if (korisnickoIme == korisnik.korisnickoIme && lozinka == korisnik.lozinka) {
                    privremenaDatoteka << korisnickoIme << " " << lozinka << " " << korisnik.kapital << endl;
                } else {
                    privremenaDatoteka << korisnickoIme << " " << lozinka << " " << kapital << endl;
                }
            }
            datoteka.close();
            privremenaDatoteka.close();
            remove("korisnici.txt");
            rename("privremeno.txt", "korisnici.txt");
            cout << "Dionica je uspjesno prodana." << endl;
        } else {
            cout << "Greska pri otvaranju datoteke." << endl;
        }
    } else {
        cout << "Nevažeći redni broj dionice." << endl;
    }
}
// Funkcija za unos nove dionice
Dionica unosDionice() {
    Dionica novaDionica;
    cout << "Unesite puni naziv dionice: ";
    cin.ignore();
    getline(cin, novaDionica.puniNaziv);

    cout << "Unesite skracenicu dionice: ";
    cin >> novaDionica.skracenica;
    cout << "Unesite vrijednost dionice: ";
    cin >> novaDionica.vrijednost;

    return novaDionica;
}

// Funkcija za kupovinu dionica
void kupiDionicu(Korisnik& korisnik, const Dionica& dionica) {
    if (dionica.vrijednost <= korisnik.kapital) {
        korisnik.dionice.push_back(dionica);
        korisnik.kapital -= dionica.vrijednost;
        cout << "Kupljena je dionica " << dionica.puniNaziv << "." << endl;
    } else {
        cout << "Nemate dovoljno sredstava za kupnju dionice." << endl;
    }
}
void ispisDionica(const Korisnik& korisnik) {
    cout << "----- Ispis dionica -----" << endl;
    if (korisnik.dionice.empty()) {
        cout << "Korisnik nema dionica." << endl;
        return;
    }
    cout << setw(15) << left << "Puni naziv" << setw(10) << left << "Skracenica" << setw(10) << right << "Vrijednost" << endl;

    for (const Dionica& dionica : korisnik.dionice) {
        cout << setw(15) << left << dionica.puniNaziv << setw(10) << left << dionica.skracenica << setw(10) << right << fixed << setprecision(2) << dionica.vrijednost << endl;
    }
}


int main() {

    Korisnik korisnik ;
    string korisnickoIme;
    string lozinka;
    cout << "Unesite korisnicko ime: ";
    cin >> korisnickoIme;
    cout << "Unesite lozinku: ";
    cin >> lozinka;

//    // Funkcija za dodavanje kapitala korisniku
//    void dodajKapital(Korisnik& korisnik){
//        double dodatniKapital;
//        cout << "Unesite iznos kapitala za dodavanje: ";
//        cin >> dodatniKapital;
//        korisnik.kapital += dodatniKapital;
//
//        // Ažurirajte korisnika u datoteci "korisnici.txt"
//        ifstream datoteka("korisnici.txt");
//        ofstream privremenaDatoteka("privremeno.txt");
//        if (datoteka.is_open() && privremenaDatoteka.is_open()) {
//            string korisnickoIme, lozinka, kapital;
//            while (datoteka >> korisnickoIme >> lozinka >> kapital) {
//                if (korisnickoIme == korisnik.korisnickoIme && lozinka == korisnik.lozinka) {
//                    privremenaDatoteka << korisnickoIme << " " << lozinka << " " << korisnik.kapital << endl;
//                } else {
//                    privremenaDatoteka << korisnickoIme << " " << lozinka << " " << kapital << endl;
//                }
//            }
//            datoteka.close();
//            privremenaDatoteka.close();
//            remove("korisnici.txt");
//            rename("privremeno.txt", "korisnici.txt");
//            cout << "Kapital je uspjesno dodan." << endl;
//        } else {
//            cout << "Greska pri otvaranju datoteke." << endl;
//        }
//    }
//
//// Funkcija za prodaju dionica
//    void prodajaDionica(Korisnik& korisnik){
//        if (korisnik.dionice.empty()) {
//            cout << "Korisnik nema dionica za prodaju." << endl;
//            return;
//        }
//
//        cout << "Dostupne dionice za prodaju:" << endl;
//        for (int i = 0; i < korisnik.dionice.size(); i++) {
//            cout << i + 1 << ". " << korisnik.dionice[i].puniNaziv << " (" << korisnik.dionice[i].skracenica << ")" << endl;
//        }
//
//        int index;
//        cout << "Unesite redni broj dionice koju želite prodati: ";
//        cin >> index;
//
//        if (index >= 1 && index <= korisnik.dionice.size()) {
//            Dionica prodanaDionica = korisnik.dionice[index - 1];
//            korisnik.dionice.erase(korisnik.dionice.begin() + (index - 1));
//            korisnik.kapital += prodanaDionica.vrijednost;
//
//            // Ažurirajte korisnika u datoteci "korisnici.txt"
//            ifstream datoteka("korisnici.txt");
//            ofstream privremenaDatoteka("privremeno.txt");
//            if (datoteka.is_open() && privremenaDatoteka.is_open()) {
//                string korisnickoIme, lozinka, kapital;
//                while (datoteka >> korisnickoIme >> lozinka >> kapital) {
//                    if (korisnickoIme == korisnik.korisnickoIme && lozinka == korisnik.lozinka) {
//                        privremenaDatoteka << korisnickoIme << " " << lozinka << " " << korisnik.kapital << endl;
//                    } else {
//                        privremenaDatoteka << korisnickoIme << " " << lozinka << " " << kapital << endl;
//                    }
//                }
//                datoteka.close();
//                privremenaDatoteka.close();
//                remove("korisnici.txt");
//                rename("privremeno.txt", "korisnici.txt");
//                cout << "Dionica je uspjesno prodana." << endl;
//            } else {
//                cout << "Greska pri otvaranju datoteke." << endl;
//            }
//        } else {
//            cout << "Nevažeći redni broj dionice." << endl;
//        }
//    }


    cout << "Dobrodosli, " << korisnik.ime << " " << korisnik.prezime << "!" << endl;
    cout << "Vas pocetni kapital: " << korisnik.kapital << endl;

    int opcija;
    do {
        cout << endl;
        cout << "----- Meni -----" << endl;
        cout << "1. Unos nove dionice" << endl;
        cout << "2. Kupovina dionica" << endl;
        cout << "3. Ispis svih dionica" << endl;
        cout << "4. Dodaj kapital" << endl;
        cout << "0. Izlaz iz programa" << endl;
        cout << "----------------" << endl;
        cout << "Unesite broj opcije: ";
        cin >> opcija;

        switch (opcija) {
            case 1: {
                Dionica novaDionica = unosDionice();
                ofstream datoteka("dionice.txt", ios::app);
                if (datoteka.is_open()) {
                    datoteka << "Puni naziv: " << novaDionica.puniNaziv << endl;
                    datoteka << "Skracenica: " << novaDionica.skracenica << endl;
                    datoteka << "Vrijednost: " << novaDionica.vrijednost << endl;
                    datoteka << endl;
                    datoteka.close();
                    cout << "Nova dionica je uspjesno unesena." << endl;
                } else {
                    cout << "Greska pri otvaranju datoteke." << endl;
                }
                break;
            }
            case 2: {
                if (korisnik.kapital <= 0) {
                    cout << "Nemate vise sredstava za kupnju dionica." << endl;
                    break;
                }

                ifstream datoteka("dionice.txt");
                if (datoteka.is_open()) {
                    string linija;
                    vector<Dionica> dostupneDionice;
                    while (getline(datoteka, linija)) {
                        if (linija.find("Puni naziv: ") != string::npos) {
                            Dionica dionica;
                            dionica.puniNaziv = linija.substr(12);
                            getline(datoteka, linija); // Preskoci liniju "Skracenica: "
                            getline(datoteka, linija); // Vrijednost: "
                            dionica.vrijednost = stod(linija.substr(12));
                            dostupneDionice.push_back(dionica);
                        }
                    }
                    datoteka.close();

                    if (dostupneDionice.empty()) {
                        cout << "Nema dostupnih dionica za kupnju." << endl;
                        break;
                    }

                    cout << "Dostupne dionice za kupnju:" << endl;
                    for (int i = 0; i < dostupneDionice.size(); i++) {
                        cout << i + 1 << ". " << dostupneDionice[i].puniNaziv << " - Vrijednost: " << dostupneDionice[i].vrijednost << endl;
                    }

                    int odabir;
                    cout << "Odaberite broj dionice koju zelite kupiti (0 za odustajanje): ";
                    cin >> odabir;

                    if (odabir >= 1 && odabir <= dostupneDionice.size()) {
                        kupiDionicu(korisnik, dostupneDionice[odabir - 1]);
                    } else if (odabir != 0) {
                        cout << "Nepoznat broj dionice." << endl;
                    }
                } else {
                    cout << "Greska pri otvaranju datoteke." << endl;
                }
                break;
            }
            case 3: {
                ifstream datoteka("dionice.txt");
                if (datoteka.is_open()) {
                    string linija;
                    ispisDionica(korisnik);
                } else {
                    cout << "Greska pri otvaranju datoteke." << endl;
                }
                break;
            }
            case 4: {
                dodajKapital(korisnik);
                break;
            }
            case 0:
                cout << "Izlaz iz programa." << endl;
                break;
            default:
                cout << "Nepoznata opcija. Molimo odaberite ponovno." << endl;
                break;
        }
    } while (opcija != 0);
    return 0;
}