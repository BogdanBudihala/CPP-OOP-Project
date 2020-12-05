#ifndef PROIECT_STARCFMI_P2_FLOTA_H
#define PROIECT_STARCFMI_P2_FLOTA_H
#include <iostream>
#include <string>
#include <vector>
#include "Vehicul.h"
#include "Autoturism.h"
#include "Camion.h"
#include "Autobuz.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <map>
#include <variant>
#include <climits>
using namespace std;

class Flota {
private:
    vector <Vehicul*> masini;

    bool unic(const string&);

    static string get_date();

    static bool comp_date(const string&, const string&);

    static string get_keyval(map<string, int>&,bool=true);
public:
    Flota();

    virtual ~Flota();

    void add(string &);

    void add(int, const string &, const string &, const string &, const string &, const string &, bool, bool);

    void add(int, const string &, const string &, const string &, const string &, const string &, bool, const string &, const string &);

    void add(int, const string &, const string &, const string &, const string &, const string &, bool, const string &);

    void load(string &);

    void del(string &);

    Vehicul* find(string &);

    vector<Vehicul *> find_all(const string &);

    friend ostream &operator<<(ostream &, const Flota &);

    vector <Vehicul *> get_expITP();

    template <class T>
    vector<variant<T, string>> get_stat1();

    template <class T>
    vector<string> get_stat2();

    template <class T>
    int get_inactive();

    bool empty();

    template <class T>
    int nr_inst();

};

template <class T> // T Trebuie neaparat sa fie un pointer spre un obiect de tipul subclaselor Autoturism/Camion/Autobuz
vector<variant<T, string>> Flota::get_stat1() {
    using variante = variant<T, string>;
    vector<variante> v;   // Un container cu obiecte de mai multe tipuri, tipul T dar si string
    T vechi=nullptr, nou=nullptr;
    map<string, int> cant; // Frecventa vechimii vehiculelor in functie de an
    // Cel mai vechi si cel mai nou vehicul de tipul T introdus
    for(auto &it:this->masini){
        if(dynamic_cast<T>(it)){
            if(cant.find(it->get_vechime().substr(6))!=cant.end())
                cant[it->get_vechime().substr(6)]++;
            else
                cant[it->get_vechime().substr(6)]=1;

            if(vechi==nullptr && nou==nullptr){
                vechi=dynamic_cast<T>(it);
                nou=dynamic_cast<T>(it);
                continue;
            }

            if(Flota::comp_date(it->get_vechime(), vechi->get_vechime()))  // Verifica daca elementul curent este mai vechi decat cel retinut anterior
                vechi=dynamic_cast<T>(it);
            if(Flota::comp_date(nou->get_vechime(), it->get_vechime())) // Verifica daca elementul retinut anterior este mai vechi decat cel curent
                nou=dynamic_cast<T>(it);
        }
    }
    v.push_back(vechi);
    v.push_back(nou);

    v.push_back(Flota::get_keyval(cant));     //Se adauga perechea key-val formatata in string cu valoarea cea mai mare respectiv cea mai mica
    v.push_back(Flota::get_keyval(cant,false));

    return v;
}

template <class T>
vector<string> Flota::get_stat2(){
    vector<string> ret_val;
    string rez;
    map<string, int> cant;
    for(auto &it:this->masini){
        if(dynamic_cast<T>(it)){
            if(cant.find(it->get_NrMat().substr(0, 2))!=cant.end())
                cant[it->get_NrMat().substr(0, 2)]++;
            else
                cant[it->get_NrMat().substr(0, 2)]=1;
        }
    }
    for(auto &it:cant){
        ostringstream oss;
        oss << it.second;
        rez = oss.str();
        rez = it.first + " - " + rez;
        ret_val.push_back(rez);
    }
    return ret_val;
}


template <class T>
int Flota::nr_inst(){
    if(this->empty()) return 0;
    else return count_if(this->masini.begin(), this->masini.end(), [](Vehicul *v){return dynamic_cast<T>(v)!=nullptr;});
}

template <class T>
int Flota::get_inactive() {
    return count_if(this->masini.begin(), this->masini.end(),[](Vehicul *v){return v->is_active()==0 && dynamic_cast<T>(v)!=nullptr;});
}
#endif //PROIECT_STARCFMI_P2_FLOTA_H
