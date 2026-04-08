#include "Hotel.h"
#include "Turist.h"
#include <cstring>

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
    int i =  gaseste_hotel(hoteluri, n, turist);//gaseste pozitia camerei ideale
    if (i != -1) {//daca o poate rezerva o face
        hoteluri[i].rezerva_camera(turist);
    }
}