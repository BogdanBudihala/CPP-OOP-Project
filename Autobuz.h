#ifndef PROIECT_STARCFMI_P2_AUTOBUZ_H
#define PROIECT_STARCFMI_P2_AUTOBUZ_H
#include <iostream>
#include <string>
#include "Vehicul.h"
using namespace std;


class Autobuz: public Vehicul {
private:
    string ruta;
public:
    Autobuz();

    Autobuz(int, const string &, const string &, const string &, const string &, const string &, bool, const string &);

    virtual ~Autobuz();

    virtual ostream &afisare(ostream &);

    friend ostream &operator<<(ostream &, Autobuz &);
};


#endif //PROIECT_STARCFMI_P2_AUTOBUZ_H
