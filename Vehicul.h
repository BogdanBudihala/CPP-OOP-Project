#ifndef PROIECT_STARCFMI_P2_VEHICUL_H
#define PROIECT_STARCFMI_P2_VEHICUL_H
#include <string>
#include <iostream>
using namespace std;

class Vehicul {
protected:
    int capacitate;
    string vechime, ITP, sofer, marca, nr_mat;
    bool activ;

public:
    Vehicul();

    Vehicul(int, const string &, const string &, const string &, const string &, const string &, bool);

    virtual ~Vehicul();

    virtual ostream &afisare(ostream &)=0;

    friend ostream &operator<<(ostream &os, Vehicul &vehicul);

    string get_NrMat() const;

    string get_ITP() const;

    string get_vechime() const;

    string get_marca() const;

    bool is_active() const;
};


#endif //PROIECT_STARCFMI_P2_VEHICUL_H
