// Proiectul consta in gestiunea alegerii zborurilor si camerelor de hotel in cadrul unei agentii de turism.
// Clasele folosite sunt:
// Turist(varsta,id,buget,nume,dest_pref,dest_act,nr_turisti(static))
// Hotel(pret,capacitate,destinatie,denumire)
// Zbor(pret,locuri_libere,destinatie,companie_aeriana)
// Prin acest proiect putem afisa obiectele fiecarei clase,putem face ca un turist sa rezerve o camera la hotelul sau
// favorit(actualizand bugetul acestuia,camera si capacitatea hotelului).
// Putem face ca un turist sa rezerve un zbor catre destinatia sa favorita(similar cu cerinta anterioara).
// Putem determina un turist sa achite o plata.
// Putem determina un turist sa rezerve o camera fortat.

#include <iostream>
#include "Turist.h"
#include "Hotel.h"
#include "Zbor.h"

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