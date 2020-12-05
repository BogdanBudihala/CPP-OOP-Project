#ifndef PROIECT_STARCFMI_P2_CAMION_H
#define PROIECT_STARCFMI_P2_CAMION_H
#include <iostream>
#include <string>
#include "Vehicul.h"
using namespace std;

class Camion: public Vehicul{
private:
    string rnr_mat, rITP;
public:
    Camion();

    Camion(int, const string &, const string &, const string &, const string &, const string &, bool, const string &, const string &);

    virtual ~Camion();

    virtual ostream &afisare(ostream &);

    friend ostream &operator<<(ostream &, Camion &);
};


#endif //PROIECT_STARCFMI_P2_CAMION_H
