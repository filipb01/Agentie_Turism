#ifndef TURIST_H
#define TURIST_H
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

#endif