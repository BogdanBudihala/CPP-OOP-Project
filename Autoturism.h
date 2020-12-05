#ifndef PROIECT_STARCFMI_P2_AUTOTURISM_H
#define PROIECT_STARCFMI_P2_AUTOTURISM_H
#include <iostream>
#include "Vehicul.h"
using namespace std;

class Autoturism: public Vehicul{
private:
    bool taxi;
public:
    Autoturism();

    Autoturism(int, const string &, const string &, const string &, const string &, const string &, bool, bool);

    virtual ~Autoturism();

    virtual ostream &afisare(ostream &);

    friend ostream &operator<<(ostream &, Autoturism &);

};


#endif //PROIECT_STARCFMI_P2_AUTOTURISM_H
