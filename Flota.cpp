#include "Flota.h"

Flota::Flota() {}

Flota::~Flota() {

}

void Flota::add(string &in) {
    int type, cap, activ;
    string vec, ITP, sofer, marca, nrmat;
    stringstream ss(in);
    ss>>type;
    ss.ignore();
    ss>>cap;
    ss.ignore();
    getline(ss, vec, ',');
    getline(ss, ITP, ',');
    getline(ss, sofer, ',');
    getline(ss, marca, ',');
    getline(ss, nrmat, ',');
    ss>>activ;
    ss.ignore();
    if(!this->unic(nrmat)) {
        throw "Vehiculul cu numarul de inmatriculare indicat exista deja";
    }
    if(type==1){
        int taxi;
        ss>>taxi;
        ss.ignore();
        this->masini.push_back(new Autoturism(cap, vec, ITP, sofer, marca, nrmat, activ, taxi));
    }
    else if(type==2){
        string rnrmat, rITP;
        getline(ss, rnrmat, ',');
        getline(ss, rITP, ',');
        if(!this->unic(rnrmat)) {
            throw "Vehiculul cu numarul de inmatriculare indicat exista deja";
        }
        this->masini.push_back(new Camion(cap, vec, ITP, sofer, marca, nrmat, activ, rnrmat, rITP));
    }
    else if(type==3){
        string ruta;
        getline(ss, ruta, ',');
        this->masini.push_back(new Autobuz(cap, vec, ITP, sofer, marca, nrmat, activ, ruta));
    }

}
void Flota::add(int cap, const string &vec, const string &ITP, const string &sofer, const string &marca,const string &nrmat, bool activ,
                bool taxi)
{
    if(!this->unic(nrmat)) {
        throw "Vehiculul cu numarul de inmatriculare indicat exista deja";
    }
    this->masini.push_back(new Autoturism(cap, vec, ITP, sofer, marca, nrmat, activ, taxi));
}
void Flota::add(int cap, const string &vec, const string &ITP, const string &sofer, const string &marca,const string &nrmat, bool activ,
                const string &rnrmat,const string &rITP)
{
    if(!this->unic(nrmat) || !this->unic(rnrmat)) {
        throw "Vehiculul cu numarul de inmatriculare indicat exista deja";
    }
    this->masini.push_back(new Camion(cap, vec, ITP, sofer, marca, nrmat, activ, rnrmat, rITP));
}
void Flota::add(int cap, const string &vec, const string &ITP, const string &sofer, const string &marca,const string &nrmat, bool activ,
                const string &ruta)
{
    if(!this->unic(nrmat)) {
        throw "Vehiculul cu numarul de inmatriculare indicat exista deja";
    }
    this->masini.push_back(new Autobuz(cap, vec, ITP, sofer, marca, nrmat, activ, ruta));
}

ostream &operator<<(ostream &os, const Flota &flota) {
    for(auto &it:flota.masini)
        os<<(*it)<<endl; //BUG AICI...De ce nu pot afisa "it" dereferentiat? Am supraincarcat operatorul << pentru toate clasele. Daca afisez
                        //fara *, atunci imi afiseaza adresa - !!!REPARAT!!!

    return os;
}

bool Flota::unic(const string &mat) {

    for(auto &it:this->masini){
        if(it->get_NrMat() == mat) //Se verifica doar cu numerele de inmatriculare ale vehiculelor, NU si ale remorcilor!!! NU se poate sterge un vehicul
            return false;           //introducand numarul de inmatriculare al remorcii
    }
    return true;
}

void Flota::load(string &file) {
    this->masini.clear();
    ifstream f(file);
    for(string buffer; getline( f, buffer); )
    {
        this->add(buffer);
    }
}

Vehicul *Flota::find(string &mat) {

    auto elem = find_if(this->masini.begin(),this->masini.end(), [mat](Vehicul *v){ return v->get_NrMat()==mat;});
    return elem!=this->masini.end() ? *elem : nullptr; //Find if returneaza container.end() daca elementul nu a fost gasit
}

void Flota::del(string &mat) {
    if(this->empty()==true)
        throw "Flota este goala. Nu se poate sterge"; //Previne stergerea flotei goale
    auto elem = remove_if(this->masini.begin(),this->masini.end(), [mat](Vehicul *v){ return v->get_NrMat()==mat;});
    // BUG AICI - Se blocheaza executia programului cand se sterge un obiect din flota goala
    if(elem == this->masini.end())
        throw "Vehiculul cu numarul de inmatriculare indicat nu exista";
    else
        this->masini.erase(elem); //remove if doar muta elementul care trebuie sters la final, dar erase il sterge de fapt
}

string Flota::get_date() {
    time_t t; // Timpul curent in secunde incepand din 1 Jan 1970
    struct tm * timp;
    char buffer[8];

    time (&t);
    timp = localtime(&t);

    strftime(buffer,8,"%m/%Y",timp); // Conversie la formatul folosit mm/yyyy
    string str(buffer);

    return str;
}
bool Flota::comp_date(const string &d1, const string &d2){
    stringstream ss_d1(d1), ss_d2(d2);
    string d_d1, m_d1, y_d1, d_d2, m_d2, y_d2;
    getline(ss_d1, d_d1, '/');
    getline(ss_d1, m_d1, '/');
    getline(ss_d1, y_d1);
    getline(ss_d2, d_d2, '/');
    getline(ss_d2, m_d2, '/');
    getline(ss_d2, y_d2);
    if(y_d1==y_d2){
        if(m_d1==m_d2){
            if(d_d1<d_d2) return true;
        }
        else if(m_d1<m_d2) return true;
    }
    else if(y_d1<y_d2) return true;

    return false;
}

string Flota::get_keyval(map<string, int>&m,bool mx){
    string key;
    int val;
    if(mx){
        val=INT_MIN;
        for(auto &it:m)
            if(it.second>val){
                val=it.second;
                key=it.first;
            }
    }
    else{
        val=INT_MAX;
        for(auto &it:m)
            if(it.second<val){
                val=it.second;
                key=it.first;
            }
    }

    string rez;
    ostringstream oss;
    oss << val;
    rez = oss.str();
    rez = key + " - " + rez;
    return rez;
}

vector<Vehicul *> Flota::get_expITP() {
    vector<Vehicul *> v;
    string data_crt = Flota::get_date();
    for(auto &it:this->masini) {
        string data_ITP = it->get_ITP();
        data_ITP = data_ITP.substr(3);
        if(data_crt==data_ITP)
            v.push_back(it);
    }
    return v;
}

bool Flota::empty(){
    return this->masini.size() == 0;
}

vector<Vehicul *> Flota::find_all(const string &brand){
    vector<Vehicul *> all;
    auto it=this->masini.begin();
    while(it!=this->masini.end()){
        if(it==this->masini.begin())
            it=find_if(it, this->masini.end(), [brand](Vehicul *v){return v->get_marca() == brand;});
        else{
            all.push_back(*it);
            it=find_if(it+1, this->masini.end(), [brand](Vehicul *v){return v->get_marca() == brand;});
        }
    }
    return all;
}



