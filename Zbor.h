#ifndef ZBOR_H
#define ZBOR_H
#include <iostream>

class Turist;

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

#endif