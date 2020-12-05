#include "Vehicul.h"

Vehicul::Vehicul() {
}

Vehicul::~Vehicul() {

}

Vehicul::Vehicul(int capacitate, const string &vechime, const string &itp, const string &sofer, const string &marca,const string &nrMat, bool activ){
    this->capacitate=capacitate;
    this->vechime=vechime;
    this->ITP=itp;
    this->sofer=sofer;
    this->marca=marca;
    this->nr_mat=nrMat;
    this->activ=activ;

}
ostream &Vehicul::afisare(ostream &os) {
    os<<"\t\tCapacitate: "<<this->capacitate<<"\t\tVechime: "<<this->vechime<<"\t\tData ITP: "<<this->ITP<<"\n\t\tSofer: "
    <<this->sofer<<"\t\tMarca: "<<this->marca<<"\t\tInmatriculare: "<<this->nr_mat<<"\n\t\tActiv: "<<(this->activ==1?"Da":"Nu")<<"\t\t";
    return os;
}

ostream &operator<<(ostream &os, Vehicul &vehicul) {
    vehicul.afisare(os);
    return os;
}

string Vehicul::get_NrMat() const {
    return this->nr_mat;
}

string Vehicul::get_ITP() const {
    return this->ITP;
}

string Vehicul::get_vechime() const {
    return this->vechime;
}

string Vehicul::get_marca() const {
    return this->marca;
}


bool Vehicul::is_active() const {
    return this->activ;
}
