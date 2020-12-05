#include "Autobuz.h"

Autobuz::Autobuz(int capacitate, const string &vechime, const string &itp, const string &sofer, const string &marca,const string &nrMat, bool activ,
                 const string &ruta) :Vehicul(capacitate, vechime, itp, sofer, marca, nrMat, activ){
    this->ruta=ruta;

}

Autobuz::Autobuz() {

}

Autobuz::~Autobuz() {

}

ostream &operator<<(ostream &os, Autobuz &autobuz) {
    autobuz.afisare(os);
    return os;
}

ostream &Autobuz::afisare(ostream &os) {
    Vehicul::afisare(os);
    os<<"Ruta: "<<this->ruta;
    return os;
}
