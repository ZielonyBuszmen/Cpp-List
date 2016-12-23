#include <iostream>
#include "list.h"
#include "ksiazka.h"
using namespace std;

int main() {
    // test kolejki
    // tworzymy nasza kolejke - czyli ta cala strkture gdzie przechowywujemy dane
    // ta kolejka to jest taka wypas kolejka, prawie jak do spowiedzi ;)
    List<Ksiazka> kolejka;
    // tworzymy se dwie ksiazki. dzieki typedef w linii 2 uzywamy slowa Item zamiast ksiaza, ale to i tak (chyba) jeden pies.
    Ksiazka ksiazka1("Tomus Wieczorek", "Jak tomus lubi zupke", "zupka");
    Ksiazka ksiazka2("Murzyn Janusz", "Ciezki los niewolnika", "niewolnictwo");

    // dodajemy ksiazke do kolejki (czyli tego stwora, co je przechowuje, tak to nazwalem - "kolejka")
    kolejka.append(
            ksiazka1); // to sie nazywa profesjonalizm - do dodawania mozna uzywac funkcji append(). Prawie jak w STL!!!
    kolejka <<
    ksiazka2; // no nie tutaj to juz czyste szalensto. Uzywamy operatora << do dodawania ksiazki. No normalnie proffesiona full morda :D
    kolejka.append(Ksiazka("Parszywy Zyd", "Zyd parszywy co zre pokrzywy",
                           "problemy spoleczne")); // a co tam, tak mozna nawet dodac
    kolejka.append(
            Ksiazka("asfasfasf", "Zyd ffff co zre pokrzywy", "problemy spoleczne")); // a co tam, tak mozna nawet dodac
    // pobieranie czegos z tej super struktury
    // kolejka[2] - pobieramy jak z tablicy nasza ksiazke
    // .get_autor() - pobieramy dane autora z ksiazki.
    string a = kolejka[2].get_autor();
    string b = kolejka[2].get_tytul();

    cout << a << " - " << b;
    cout << "\n--------\n";
    cout << kolejka[1].get_tytul();

    // teraz mozemy se zmienic wartosc funkcja set_
    kolejka[1].set_tytul("Bleee, zygam, zygam jak na to pacze");

    cout << " ->" << kolejka[1].get_tytul();

    cout << "\n--------\n";
    cout << kolejka[0].get_tytul();

    // mozna tez zmienic to drugim sposobem
    kolejka[0].set_tytul() = "Tomus nie lubi zupki";

    cout << " ->" << kolejka[0].get_tytul();
    // usuwamy element nr 1 (czyli Murzyn Janusz)
    kolejka.delElement(1);

    // teraz pod element 1 kryje sie ksiazka Parszywy Zyd
    cout << "\n--------\n";
    cout << " -" << kolejka.lastElement().get_autor();


    cout << "\n--------\n";
    return 0;
}
