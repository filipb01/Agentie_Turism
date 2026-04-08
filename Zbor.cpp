#include "Zbor.h"
#include "Turist.h"
#include <iostream>
#include <cstring>

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
    int i = gaseste_zbor(zboruri, n, turist);

    if (i != -1) {
        zboruri[i].cumpara_zbor(turist);
    }
}