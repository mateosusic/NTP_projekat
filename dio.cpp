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

int main() {
    Korisnik korisnik = unosKorisnika();
    cout << "Dobrodosli, " << korisnik.ime << " " << korisnik.prezime << "!" << endl;
    cout << "Vas ID korisnika je: " << korisnik.id << endl;

    return 0;
}
//aaa///