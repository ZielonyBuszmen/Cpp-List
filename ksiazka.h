// prosta klasa do testu naszej listy - "dynamicznej tablicy"

#include <string>

using namespace std;

// ta klasa to ta klasa co przechowuje ksiazke
class Ksiazka {
private:
    string autor;
    string tytul;
    string etykieta;
    // jeœli musimy przechowywaæ wiêcej etykiet ni¿ jedna, to trzeba nad tym pomyœleæ
public:
    Ksiazka(string aut = "", string tyt = "", string etyk = "") : autor(aut), tytul(tyt),
                                                                  etykieta(etyk) { } // w konstruktorze ustawiamy dane
    // do wyswietlania danych
    string get_autor() { return autor; }

    string get_tytul() { return tytul; }

    string get_etykieta() { return etykieta; }

    // ustawianie danych
    void set_autor(string aut) { autor = aut; }

    void set_tytul(string tyt) { tytul = tyt; }

    void set_etykieta(string ety) { etykieta = ety; }

    string &set_autor() { return autor; }

    string &set_tytul() { return tytul; }

    string &set_etykieta() { return etykieta; }

};
