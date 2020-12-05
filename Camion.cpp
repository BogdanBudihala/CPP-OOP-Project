#include "Camion.h"

Camion::Camion() {

}

Camion::Camion(int capacitate, const string &vechime, const string &itp, const string &sofer, const string &marca,const string &nrMat, bool activ,
        const string &rnrMat,const string &ritp):Vehicul(capacitate, vechime, itp, sofer, marca,nrMat, activ) {
    this->rnr_mat=rnrMat;
    this->rITP=ritp;
}

Camion::~Camion() {

}

ostream &operator<<(ostream &os, Camion &camion) {
    camion.afisare(os);
    return os;
}

ostream &Camion::afisare(ostream &os) {
    Vehicul::afisare(os);
    os<<"Inmatriculare remorca: "<<this->rnr_mat<<"\t\tITP remorca: "<<this->rITP;
    return os;
}
