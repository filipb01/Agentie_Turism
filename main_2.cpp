#include <iostream>
#include <cstring>
class Turist {
    int varsta, id;
    double buget;
    char *nume, *dest_pref, *camera = nullptr, *dest_actuala = nullptr;
    static int nr_turisti;

public:
    Turist(int varsta = 18, double buget = 0, const char* nume = "N/A", const char* dest_pref = "N/A");
    Turist(const Turist& turist);
    ~Turist();

    int getVarsta() const;
    int getId() const;
    double getBuget() const;
    const char* getDestPref() const;
    const char* getNume() const;

    void setCamera(const char* camera_noua);
    void setDestActuala(const char* dest_noua);

    void plateste(double suma);

    Turist& operator=(const Turist& turist);
    friend std::ostream& operator<<(std::ostream& os, const Turist& turist);
};

class Hotel {
    int pret, capacitate;
    char *destinatie, *denumire;
public:
    Hotel(int pret = 0, int capacitate = 0, const char* dest = "N/A", const char* nume = "N/A");
    Hotel(const Hotel& hotel);
    ~Hotel();

    Hotel& operator=(const Hotel& hotel);
    Hotel& operator--();
    Hotel operator--(int);

    friend std::ostream& operator<<(std::ostream& os, const Hotel& hotel);

    double pret_final(const Turist& turist) const;
    bool poate_rezerva(const Turist& turist) const;
    void rezerva_camera(Turist& turist);

    static int gaseste_hotel(const Hotel* hoteluri, int n, const Turist& turist);
    static void rezerva_camera_preferata(Hotel* hoteluri, int n, Turist& turist);
};

class Zbor {
    int pret, locuri_libere;
    char *destinatie, *companie_aeriana;
public:
    Zbor(int pret = 0, int locuri_libere = 0, const char* destinatie = "N/A", const char* companie_aeriana = "N/A");
    Zbor(const Zbor& zbor);
    ~Zbor();

    Zbor& operator=(const Zbor& zbor);
    Zbor& operator--();
    Zbor operator--(int);

    friend std::ostream& operator<<(std::ostream& os, const Zbor& zbor);

    bool poate_cumpara(const Turist& turist) const;
    void cumpara_zbor(Turist& turist);

    static int gaseste_zbor(const Zbor* zboruri, int n, const Turist& turist);
    static void rezerva_zbor_preferat(Zbor* zboruri, int n, Turist& turist);
};

int Turist::nr_turisti = 0;

Turist::Turist(int varsta, double buget, const char* nume, const char* dest_pref)
    : varsta(varsta), buget(buget) {
    this->nume = new char[strlen(nume) + 1];
    strcpy(this->nume, nume);
    this->dest_pref = new char[strlen(dest_pref) + 1];
    strcpy(this->dest_pref, dest_pref);
    nr_turisti++;
    id = nr_turisti;
}

Turist::Turist(const Turist& turist) : varsta(turist.varsta), buget(turist.buget) {
    this->nume = new char[strlen(turist.nume) + 1];
    strcpy(this->nume, turist.nume);

    this->dest_pref = new char[strlen(turist.dest_pref) + 1];
    strcpy(this->dest_pref, turist.dest_pref);

    if (turist.dest_actuala != nullptr) {
        this->dest_actuala = new char[strlen(turist.dest_actuala) + 1];
        strcpy(this->dest_actuala, turist.dest_actuala);
    } else {
        this->dest_actuala = nullptr;
    }

    if (turist.camera != nullptr) {
        this->camera = new char[strlen(turist.camera) + 1];
        strcpy(this->camera, turist.camera);
    } else {
        this->camera = nullptr;
    }
    nr_turisti++;
    id = nr_turisti;
}

Turist::~Turist() {
    delete[] this->nume;
    delete[] this->dest_pref;
    delete[] this->camera;
    delete[] this->dest_actuala;
    nr_turisti--;
}

int Turist::getVarsta() const { return this->varsta; }
int Turist::getId() const { return this->id; }
double Turist::getBuget() const { return this->buget; }
const char* Turist::getDestPref() const { return this->dest_pref; }
const char *Turist::getNume() const {return this->nume;}

void Turist::setCamera(const char* camera_noua) {
    delete[] this->camera;//free
    this->camera = new char[strlen(camera_noua) + 1];//alloc
    strcpy(this->camera, camera_noua);//copy
}//seteaza camera daca achizitionez hotel
void Turist::setDestActuala(const char* dest_noua) {
    delete[] this->dest_actuala;
    this->dest_actuala = new char[strlen(dest_noua) + 1];
    strcpy(this->dest_actuala, dest_noua);
}//seteaza destinatia daca achizitionez zbor

void Turist::plateste(double suma) {
    if (this->buget >= suma)
        this->buget-=suma;
}//scade din buget o suma,ca sa nu fac setter

Turist& Turist::operator=(const Turist& turist) {
    if (this == &turist)
        return *this;

    delete[] this->nume;
    delete[] this->dest_pref;
    delete[] this->camera;
    delete[] this->dest_actuala;

    this->varsta = turist.varsta;
    this->buget = turist.buget;

    this->nume = new char[strlen(turist.nume) + 1];
    strcpy(this->nume, turist.nume);

    this->dest_pref = new char[strlen(turist.dest_pref) + 1];
    strcpy(this->dest_pref, turist.dest_pref);

    if (turist.dest_actuala != nullptr) {
        this->dest_actuala = new char[strlen(turist.dest_actuala) + 1];
        strcpy(this->dest_actuala, turist.dest_actuala);
    } else {
        this->dest_actuala = nullptr;
    }

    if (turist.camera != nullptr) {
        this->camera = new char[strlen(turist.camera) + 1];
        strcpy(this->camera, turist.camera);
    } else {
        this->camera = nullptr;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Turist& turist) {
    os << '[' << turist.id << " | " << turist.nume << " | v=" << turist.varsta
       << " | b=" << turist.buget << " | Pref: " << turist.dest_pref
       << " | Act: " << (turist.dest_actuala != nullptr ? turist.dest_actuala : "N/A")
       << " | Cam: " << (turist.camera != nullptr ? turist.camera : "N/A") << "]\n";
    return os;
}

Hotel::Hotel(int pret, int capacitate, const char* dest, const char* nume) :
    pret(pret), capacitate(capacitate) {
    this->destinatie = new char[strlen(dest) + 1];
    strcpy(this->destinatie, dest);
    this->denumire = new char[strlen(nume) + 1];
    strcpy(this->denumire, nume);
}

Hotel::Hotel(const Hotel& hotel) :
    pret(hotel.pret), capacitate(hotel.capacitate) {
    this->destinatie = new char[strlen(hotel.destinatie) + 1];
    strcpy(this->destinatie, hotel.destinatie);
    this->denumire = new char[strlen(hotel.denumire) + 1];
    strcpy(this->denumire, hotel.denumire);
}

Hotel::~Hotel() {
    delete[] this->destinatie;
    delete[] this->denumire;
}

Hotel& Hotel::operator=(const Hotel& hotel) {
    if (this == &hotel)
        return (*this);

    this->pret = hotel.pret;
    this->capacitate = hotel.capacitate;

    delete[] this->denumire;
    this->denumire = new char[strlen(hotel.denumire) + 1];
    strcpy(this->denumire, hotel.denumire);

    delete[] this->destinatie;
    this->destinatie = new char[strlen(hotel.destinatie) + 1];
    strcpy(this->destinatie, hotel.destinatie);

    return (*this);
}

Hotel& Hotel::operator--() {
    if (this->capacitate > 0)
        --this->capacitate;
    return *this;
}

Hotel Hotel::operator--(int) {
    Hotel copie(*this);
    --(*this);
    return copie;
}

std::ostream& operator<<(std::ostream& os, const Hotel& hotel) {
    os << '[' << hotel.denumire << " | " << hotel.destinatie << " | p=" << hotel.pret
       << " | c=" << hotel.capacitate << "]\n";
    return os;
}

double Hotel::pret_final(const Turist& turist) const {
    int pret_baza = this->pret;
    double reducere = 0;

    if (turist.getVarsta() <= 15) reducere += 0.10; //10% pt copii
    else if (turist.getVarsta() >= 65) reducere += 0.15; //15% pt seniori
    if (strcmp(turist.getDestPref(), this->destinatie) == 0) reducere -= 0.05;//5% scumpire pt destinatie de vis
    if (!(turist.getId() % 100)) reducere += 0.05;//5% pentru turistul cu id = multiplu de 100
    return pret_baza - pret_baza * reducere;
}//functie prin care se calculeaza pretul final dupa aplicarea unor reduceri/scumpiri

bool Hotel::poate_rezerva(const Turist& turist) const {
    return this->pret_final(turist) <= turist.getBuget() && this->capacitate >= 1;
}

int Hotel::gaseste_hotel(const Hotel* hoteluri, int n, const Turist& turist) {
    int index1 = -1, index2 = -1, max1 = -1, max2 = -1;//max1,max2 sunt criteriile de comp iar i1,i2 optiunile
    for (int i = 0; i < n; i++) {
        if (strcmp(turist.getDestPref(), hoteluri[i].destinatie) == 0) {//daca destinatia este cea preferata
            if (hoteluri[i].pret >= max1 && hoteluri[i].poate_rezerva(turist)) {//daca si-o permite
                max1 = hoteluri[i].pret;//salvam criteriul de comp
                index1 = i;//salvam poz in vect
            }
        }
        else if (hoteluri[i].pret >= max2 && hoteluri[i].poate_rezerva(turist)) {//daca nu e destinatia preferata
            max2 = hoteluri[i].pret;//tinem minte al doilea criteriu
            index2 = i;//valoare de rezerva
        }
    }
    if (index1 != -1) return index1;
    return index2;
}//returneaza indexul din vector

void Hotel::rezerva_camera(Turist& turist) {
    if (this->poate_rezerva(turist)) {//verifica daca poate sa rezerve
        turist.plateste(this->pret_final(turist));//ii scade bugetul
        --(*this);//operator supraincarcat cu scopul de a scadea capacitatea
        turist.setCamera(this->denumire);//seteaza camera pt obiectul turist
    }
}//seteaza

void Hotel::rezerva_camera_preferata(Hotel* hoteluri, int n, Turist& turist) {
    int i = Hotel::gaseste_hotel(hoteluri, n, turist);//gaseste pozitia camerei ideale
    if (i != -1) {//daca o poate rezerva o face
        hoteluri[i].rezerva_camera(turist);
    }
}

Zbor::Zbor(int pret, int locuri_libere, const char* destinatie, const char* companie_aeriana)
    : pret(pret), locuri_libere(locuri_libere) {

    this->destinatie = new char[strlen(destinatie) + 1];
    strcpy(this->destinatie, destinatie);

    this->companie_aeriana = new char[strlen(companie_aeriana) + 1];
    strcpy(this->companie_aeriana, companie_aeriana);
}

Zbor::Zbor(const Zbor& zbor) {
    this->pret = zbor.pret;
    this->locuri_libere = zbor.locuri_libere;

    this->destinatie = new char[strlen(zbor.destinatie) + 1];
    strcpy(this->destinatie, zbor.destinatie);

    this->companie_aeriana = new char[strlen(zbor.companie_aeriana) + 1];
    strcpy(this->companie_aeriana, zbor.companie_aeriana);
}

Zbor::~Zbor() {
    delete[] this->destinatie;
    delete[] this->companie_aeriana;
}

Zbor& Zbor::operator=(const Zbor& zbor) {
    if (this == &zbor)
        return *this;

    this->pret = zbor.pret;
    this->locuri_libere = zbor.locuri_libere;

    delete[] this->destinatie;
    delete[] this->companie_aeriana;

    this->destinatie = new char[strlen(zbor.destinatie) + 1];
    strcpy(this->destinatie, zbor.destinatie);

    this->companie_aeriana = new char[strlen(zbor.companie_aeriana) + 1];
    strcpy(this->companie_aeriana, zbor.companie_aeriana);

    return *this;
}

Zbor& Zbor::operator--() {
    if (this->locuri_libere > 0)
        --this->locuri_libere;
    return *this;
}

Zbor Zbor::operator--(int) {
    Zbor copie(*this);
    --(*this);
    return copie;
}

std::ostream& operator<<(std::ostream& os, const Zbor& zbor) {
    os << '[' << zbor.companie_aeriana << " | " << zbor.destinatie
       << " | p=" << zbor.pret << " | l=" << zbor.locuri_libere << "]\n";
    return os;
}

bool Zbor::poate_cumpara(const Turist& turist) const {
    return this->pret <= turist.getBuget() && this->locuri_libere >= 1;
}

void Zbor::cumpara_zbor(Turist& turist) {
    if (this->poate_cumpara(turist)) {
        turist.plateste(this->pret);

        --(*this);

        turist.setDestActuala(this->destinatie);
    }
}

int Zbor::gaseste_zbor(const Zbor* zboruri, int n, const Turist& turist) {
    int index1 = -1, index2 = -1, min1 = -1, min2 = -1;

    for (int i = 0; i < n; i++) {
        if (strcmp(turist.getDestPref(), zboruri[i].destinatie) == 0) {
            if ((min1 == -1 || zboruri[i].pret <= min1 )&& zboruri[i].poate_cumpara(turist)) {
                min1 = zboruri[i].pret;
                index1 = i;
            }
        }
        else if ((min2 == -1 || zboruri[i].pret <= min2) && zboruri[i].poate_cumpara(turist)) {
            min2 = zboruri[i].pret;
            index2 = i;
        }
    }

    if (index1 != -1) return index1;
    return index2;
}

void Zbor::rezerva_zbor_preferat(Zbor* zboruri, int n, Turist& turist) {
    int i = Zbor::gaseste_zbor(zboruri, n, turist);

    if (i != -1) {
        zboruri[i].cumpara_zbor(turist);
    }
}

void afiseaza_meniu() {
    std::cout << "\n========================================\n";
    std::cout << "      AGENTIA DE TURISM - TESTARE       \n";
    std::cout << "========================================\n";
    std::cout << "1. Afiseaza toti Turistii\n";
    std::cout << "2. Afiseaza toate Hotelurile\n";
    std::cout << "3. Afiseaza toate Zborurile\n";
    std::cout << "----------------------------------------\n";
    std::cout << "4. Turistul rezerva Hotelul preferat automat\n";
    std::cout << "5. Turistul rezerva Zborul preferat automat\n";
    std::cout << "6. Turistul face o plata manuala (scade bugetul)\n";
    std::cout << "7. Rezerva o camera manual (fortat)\n";
    std::cout << "0. Iesire din program\n";
    std::cout << "========================================\n";
    std::cout << "Alege o optiune: ";
}

int main() {
    Turist turisti[5] = {
        Turist(21, 5000, "Alex", "Roma"),      // Student normal
        Turist(14, 2000, "Maria", "Paris"),    // Copil (trebuie sa primeasca reducere 10%)
        Turist(68, 8000, "Ion", "Maldive"),    // Senior (trebuie sa primeasca reducere 15%)
        Turist(25, 100, "Elena", "Dubai"),     // Buget foarte mic (sa vedem daca este respinsa)
        Turist(30, 4000, "Mihai", "Londra")    // Turist standard
    };
    int nr_turisti = 5;

    Hotel hoteluri[6] = {
        Hotel(500, 3, "Roma", "Hostel Colosseum"),
        Hotel(2000, 3, "Roma", "Hostel Potrivit"),
        Hotel(1200, 5, "Paris", "Hotel Eiffel"),
        Hotel(4000, 2, "Maldive", "Luxury Resort"),
        Hotel(3500, 0, "Dubai", "Burj Al Arab"), // SOLD OUT! Capacitate 0.
        Hotel(800, 10, "Londra", "London Inn")
    };
    int nr_hoteluri = 5;

    Zbor zboruri[6] = {
        Zbor(150, 50, "Roma", "WizzAir"),
        Zbor(100, 50, "Roma", "WizzAir"),
        Zbor(300, 20, "Paris", "Air France"),
        Zbor(1500, 5, "Maldive", "Qatar Airways"),
        Zbor(800, 2, "Dubai", "Emirates"),
        Zbor(250, 100, "Londra", "British Airways")
    };
    int nr_zboruri = 5;

    int optiune;
    do {
        afiseaza_meniu();
        std::cin >> optiune;

        switch (optiune) {
            case 1:
                std::cout << "\n--- LISTA TURISTI ---\n";
                for (int i = 0; i < nr_turisti; i++) std::cout << i << ". " << turisti[i];
                break;

            case 2:
                std::cout << "\n--- LISTA HOTELURI ---\n";
                for (int i = 0; i < nr_hoteluri; i++) std::cout << i << ". " << hoteluri[i];
                break;

            case 3:
                std::cout << "\n--- LISTA ZBORURI ---\n";
                for (int i = 0; i < nr_zboruri; i++) std::cout << i << ". " << zboruri[i];
                break;

            case 4: {
                int id_t;
                std::cout << "Introdu indexul turistului (0-4): ";
                std::cin >> id_t;
                if (id_t >= 0 && id_t < nr_turisti) {
                    std::cout << "Incercam sa rezervam hotel pt " << turisti[id_t].getNume() << "...\n";
                    Hotel::rezerva_camera_preferata(hoteluri, nr_hoteluri, turisti[id_t]);
                    std::cout << "Operatiune incheiata.\n"<<turisti[id_t];
                } else std::cout << "Index invalid!\n";
                break;
            }

            case 5: {
                int id_t;
                std::cout << "Introdu indexul turistului (0-4): ";
                std::cin >> id_t;
                if (id_t >= 0 && id_t < nr_turisti) {
                    std::cout << "Incercam sa rezervam zbor pt " << turisti[id_t].getNume() << "...\n";
                    Zbor::rezerva_zbor_preferat(zboruri, nr_zboruri, turisti[id_t]);
                    std::cout << "Operatiune incheiata.\n"<<turisti[id_t];
                } else std::cout << "Index invalid!\n";
                break;
            }

            case 6: {
                int id_t;
                double suma;
                std::cout << "Introdu indexul turistului (0-4): ";
                std::cin >> id_t;
                if (id_t >= 0 && id_t < nr_turisti) {
                    std::cout << "Ce suma doresti sa plateasca (ex: pentru o inghetata)? ";
                    std::cin >> suma;
                    turisti[id_t].plateste(suma);
                    std::cout << "Plata efectuata (daca a avut suficienti bani).\n";
                } else std::cout << "Index invalid!\n";
                break;
            }

            case 7: {
                int id_t, id_h;
                std::cout << "Introdu index turist (0-4): ";
                std::cin >> id_t;
                std::cout << "Introdu index hotel (0-4): ";
                std::cin >> id_h;
                if (id_t >= 0 && id_t < nr_turisti && id_h >= 0 && id_h < nr_hoteluri) {
                    hoteluri[id_h].rezerva_camera(turisti[id_t]);
                    std::cout << "Incercare de rezervare manuala incheiata.\n"<<turisti[id_t];
                } else std::cout << "Index invalid!\n";
                break;
            }

            case 0:
                std::cout << "\nInchidere sistem agentie\n";
                break;

            default:
                std::cout << "\nOptiune invalida! Te rog sa incerci din nou.\n";
        }
    } while (optiune != 0);

    return 0;
}