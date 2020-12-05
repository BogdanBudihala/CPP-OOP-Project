#include "Autoturism.h"

Autoturism::Autoturism() {}

Autoturism::Autoturism(int capacitate, const string &vechime, const string &itp, const string &sofer, const string &marca,const string &nrMat, bool activ,
        bool taxi):Vehicul(capacitate, vechime, itp, sofer, marca,nrMat, activ) {
    this->taxi=taxi;
}

Autoturism::~Autoturism() {

}

ostream &operator<<(ostream &os, Autoturism &autoturism) {
    autoturism.afisare(os);
    return os;
}

ostream &Autoturism::afisare(ostream &os) {
    Vehicul::afisare(os);
    os<<"Regim taxi: "<<(this->taxi==1?"Da":"Nu")<<" ";
    return os;
}
