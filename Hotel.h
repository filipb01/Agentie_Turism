#ifndef HOTEL_H
#define HOTEL_H
#include <iostream>

class Turist;

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

#endif