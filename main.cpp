#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Struktura dionice
struct Dionica {
    string puniNaziv;
    string skracenica;
    double vrijednost;
};

// Struktura korisnik
struct Korisnik {
    string ime;
    string prezime;
    int id;
    double kapital;
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

    return noviKorisnik;
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

int main() {
    Korisnik korisnik = unosKorisnika();
    cout << "Dobrodosli, " << korisnik.ime << " " << korisnik.prezime << "!" << endl;
    cout << "Vas pocetni kapital: " << korisnik.kapital << endl;

    int opcija;
    do {
        cout << endl;
        cout << "----- Meni -----" << endl;
        cout << "1. Unos nove dionice" << endl;
        cout << "2. Kupovina dionica" << endl;
        cout << "3. Ispis svih dionica" << endl;
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
                    cout << "----- Popis svih dionica -----" << endl;
                    while (getline(datoteka, linija)) {
                        cout << linija << endl;
                    }
                    datoteka.close();
                } else {
                    cout << "Greska pri otvaranju datoteke." << endl;
                }
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

