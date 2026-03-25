#include "Turist.h"

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