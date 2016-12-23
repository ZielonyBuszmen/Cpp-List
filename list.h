#ifndef List_H_
#define List_H_

// klasa naszej listy. Jest zbudowana na szablonach klas. Dlaczego tak? Poniewaz dzieki temu
// mozemy przechowywac w niej elementy typu, jakiego tylko chcemy.
// typ Item to typ danych, jaki przechowujemy w naszej liscie
template<class Item>
class List {
private:
    // tworzymy mini-struct, ktora bedzie przechowywala nasze dane
    // Node przechowuje nasz item i wskaznik na nastepny item

    struct Node {
        Item item;
        struct Node *next;
    };

    Node *front;       // poczatek listy (wskaznik na pierwszy element)
    Node *rear;        // koniec listy (wskaznik na ostatni element)
    int items;          // biezaca liczba itemkow w naszej liscie
    // nasza lista tylko zaiera elemtny. Dlatego tez musimy zablokowac
    // konstruktor kopiujacy i operator przypisania. Nie jest to dobre rozwiazanie,
    // ale w przeciwnym wypadku musielibysmy napisac kod, ktory kopiowalby kazdy item
    // naszej listy do drugiej listy. A taka operacja kopiowania bylaby bardzo nieefektywna.
    List(const List &q) { }

    List &operator=(const List &q) { return *this; }

    Node *randomNode(int numer) // zwraca wskaznik na wezel, funkcja prywatna tylko do wlasnego uzytku przez klase
    {
        Node *tempp = front; // przypisujemy sobie front
        if (numer == 0) return tempp; // jeśli przekazano numer 0 to wtedy usuwamy element zerowy
        for (int i = 1;
             i <= (numer); i++) { tempp = tempp->next; } // jesli nie, to przechodzimy do tego co chcemy usunac
        return tempp;   // zwracamy wskaznik node na wybrany element
    }

    bool isInRange(int id) { if (id >= items) return false; else return true; } // czy lezy w zakresie ten id?
public:
    List();         // domyslny konstruktor
    ~List();        // destruktor musi usuwac cala zawartosc listy, by nie bylo wyciekow pamieci
    bool isempty() const;  // zwraca, czy lista jest pusta
    int size() const;      // zwraca ilosc elementow
    bool append(const Item &item); // dodaje element na koniec listy
    bool delFirstElement(Item &item); // usuwa pierwszy element z listy i przypisuje go do zmiennej podanej w parametrze
    bool delFirstElement(); // usuwa pierwszy element z listy, ale go nie zwraca
    bool delElement(int i); // usuwa losowo wybrany element z tablicy
    Item &operator[](int numer); // zwraca losowy element listy
    Item &lastElement(); // zwraca ostatni element na liscie
    bool operator<<(const Item &item); // dodawanie na koniec za pomocą operatora <<

};


template<class Item>
List<Item>::List()          // domyslny konstruktor
{
    front = rear = NULL;      // albo nullptr
    items = 0;

}

template<class Item>
List<Item>::~List()         // destruktor
{
    Node *temp;
    while (front != NULL)     // do wyczerpania kolejki
    {
        temp = front;         // zachowanie adresu elementu biezacego
        front = front->next;  // przesuniecie wskaznika do elementu nastepnego
        delete temp;          // zwolnienie elementu spod zapamietanego adresu
    }
}

template<class Item>
bool List<Item>::isempty() const    // zwraca true, jesli lista jest pusta
{
    return items == 0;
}

template<class Item>
int List<Item>::size() const    // zwraca liczbe itemow w liscie
{
    return items;
}

// dodaje item do listy
template<class Item>
bool List<Item>::append(const Item &item) {

    Node *add = new Node;     // utworzenie wezla
    // w przypadku niepowodzenia przydzialu new zrzuci wyjatek std::bad_alloc -> mozna go uzyc w kodzie klienckim
    add->item = item;          // ustawienie wskazników wezlow
    add->next = NULL;          // albo nullptr;
    items++;
    if (front == NULL)         // jezli kolejka jest pusta,
        front = add;           // umiesc element na czele listy
    else
        rear->next = add;      // w przeciwnym przypadku dolacz do konca
    rear = add;                // rear wskazuje teraz nowy wezel
    return true;
}

// kopiuje element czolowy (pierwszy) listy do argumentu wywolania i usuwa go z kolejki
template<class Item>
bool List<Item>::delFirstElement(Item &item) {
    if (front == NULL)
        return false;
    item = front->item;    // skopiowanie do item pierwszego elementu z kolejki
    items--;
    Node *temp = front;   // zachowanie polozenia pierwszego elementu
    front = front->next;   // przestawienie wskaznika front na nastepny element
    delete temp;           // usuniecie dotychczasowego pierwszego elementu
    if (items == 0)
        rear = NULL;
    return true;
}

// usuwa element z listy. Id podane w argumencie
template<class Item>
bool List<Item>::delElement(int id) {
    // sprawdzamy, czy jest dobry zakres
    if (isInRange(id) == false) return false;

    int i_prev = id - 1; // ustawiamy numer poprzedniego elementu
    int i_next = id + 1; // ustawiamy numer nastpenego elementu
    if (id == 0) // okazuje sie, ze jest to pierwszy element. wystarczy uzyc delFirstElement i zwrocic true.
    {
        if (delFirstElement()) return true;
    }
    Node *prev = randomNode(i_prev);  // wskaznik na poprzedni element
    Node *that = randomNode(id);      // wskaznik na  biezacy element

    // jesli nastepny element nie jest w zakresie, to znaczy ze usuwamy ostatni element listy
    if (isInRange(i_next) == false) {
        // usuwanie ostatniego elementu
        prev->next = NULL; // poprzedni staje sie ostatnim, wiec wskazuje na null
        items--;    // zmniejszamy ilosc danych w liscie
        delete that;   // usuwamy ten element
        return true;
    }

    Node *next = randomNode(i_next);  // nastepny element (deklarujemy go potem, dla bezpieczenstwa)
    // przypisujemy wskaznik poprzedni na nastepny. Ten "srodkowy" omijamy.
    prev->next = next;
    items--;    // zmniejszamy ilosc danych w liscie
    // usuwamy nieuzywany element
    delete that; // usuwamy ten element
    return true;
}

// usuwa pierwszy element bez jego zwracania
template<class Item>
bool List<Item>::delFirstElement() {
    if (front == NULL)
        return false;
    Item &item = front->item;    // skopiowanie do item pierwszego elementu z kolejki
    items--;
    Node *temp = front;   // zachowanie polozenia pierwszego elementu
    front = front->next;   // przestawienie wskaznika front na nastepny element
    delete temp;           // usuniecie dotychczasowego pierwszego elementu
    //delete item;
    if (items == 0)
        rear = NULL;
    return true;
}

// przeciazany operator [] - daje dostep do losowego elementu listy
template<class Item>
Item &List<Item>::operator[](int numer) {
    if (isInRange(numer) ==
        false) { } // jesli element jest poza naszym zakresem (zostal podany za duzy zakres) to nic nie robimy
        // chociaz moglibysmy tutaj wyrzucic wyjtek do obslugi w kodzie klienckim
    else    // jesli jednak sie indeks zgadza
    {
        Node *tempp = front; // przypisujemy pierwszy element
        if (numer == 0) return tempp->item;     // jesli wybrano pierwszy element to go zwracamy
        for (int i = 1;
             i <= (numer); i++)    // w przeciwnym wypadku przechodzimy po liscie az nie na trafimy na ten co trzeba
        {
            tempp = tempp->next;
        }
        return tempp->item;     // zwracamy wybrany element. UWAGA - zwraca jest referencje do tego elementu, wiec mozna go dowolnie edytowac, itd
    }
}

// zwraca ostatni element z listy
template<class Item>
Item &List<Item>::lastElement() {
    int temp_indeks = items - 1;
    return operator[](temp_indeks);
}


// umozliwia dodawanie elementow za pomoca skladni lista << element;
template<class Item>
bool List<Item>::operator<<(const Item &item) {
    return append(item);
}

#endif
