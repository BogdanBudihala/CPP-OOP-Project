#include <iostream>
#include "Flota.h"
#include "Generator.h"
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
using namespace std;

int lung=120, lat=5;
void header(){
    system("cls");
    for(int i=0;i<lat;i++){
        for(int j=0;j<lung;j++){
            if(i==2 && j==51){
                cout<<"Interfata Consolei";
                j+=17;
            }
            else{
                if(i==0 || i==lat-1)
                    cout<<"*";
                else if(j==0 || j==lung-1)
                    cout<<"*";
                else cout<<" ";
            }
        }
        cout<<endl;
    }
}
string encrypt(string input){
    for(int i=0;i<input.length();i++){
        if(i%2==0)
            input[i]-=i;
        else
            input[i]+=i;
    }
    return input;
}
string read_password(){
    char s[15]={};
    for (int i = 0; i < 15;i++) {
        s[i] = _getch();
        if (s[i] == 13) {
            s[i]='\0';
            break;
        }
        _putch('*');
    };
    string k = s;
    return k;
}
void to_half(int sz){
    for(int i=0;i<lung/2-sz/2;i++)
        cout<<" ";
}
bool is_unique(string &input){
    ifstream f("Accounts.txt");
    string line, user, encrypted_input=encrypt(input);
    while(getline(f, line) && !line.empty()){
        stringstream ss(line);
        getline(ss, user, ' ');
        if(user==encrypted_input) return false;
    }
    f.close();
    return true;
}
bool valid(string &input){
    if(input.length()<6 || input.length()>15) return false;
    for(int i=0;i<input.size();i++){
        bool cif = input[i]>=48 && input[i]<=57, lit_mare = input[i]>=65 && input[i]<=90, lit_mica = input[i]>=97 && input[i]<=122;
        if(!cif && !lit_mare && !lit_mica) return false;
    }
    return true;
}
bool log_attempt(string &user, string &pass){
    ifstream f("Accounts.txt");
    string line, fetch_user, fetch_pass, encrypted_user=encrypt(user), encrypted_pass=encrypt(pass);
    while(getline(f, line) && !line.empty()){
        stringstream ss(line);
        getline(ss, fetch_user, ' ');
        getline(ss, fetch_pass);
        if(fetch_user==encrypted_user && fetch_pass==encrypted_pass) return true;
    }
    f.close();
    return false;
}
void add_account(string &user, string &pass){
    string encrypted_user=encrypt(user), encrypted_pass=encrypt(pass);
    ofstream g("Accounts.txt", ios_base::app);
    g<<encrypted_user<<' '<<encrypted_pass<<endl;
    g.close();
}
void start_interface(){
    Flota f;
    string buffer, command, error="Comanda nerecunoscuta. Incercati din nou.";
    int stage=0;
    header();
    while(true){
        if(stage==0){
            command="Introduceti 1 pentru Sign in, 2 pentru Sign up sau Quit pentru a iesi";
            to_half(command.size());
            cout<<command<<endl<<">";
            cin>>buffer;
            if(buffer=="1"){
                stage=1;
                header();
            }
            else if(buffer=="2"){
                stage=2;
                header();
            }
            else if(buffer=="Quit")
                break;
            else{
                header();
                to_half(error.size());
                cout<<error<<endl;
                continue;
            }
        }
        if(stage==1){
            string user="", pass="",fail="User sau parola invalide. Incercati din nou";
            command="Introduceti nume si parola (doar siruri de caractere alfanumerice de lungime intre 6 si 15)";
            to_half(command.size());
            cout<<command<<endl<<"User:\n"<<">";
            cin>>user;
            cout<<"Parola:\n"<<">";
            pass=read_password();
            if(!log_attempt(user, pass)){
                header();
                to_half(fail.size());
                cout<<fail<<endl;
                continue;
            }
            else{
                header();
                stage=3;
                continue;
            }
        }
        if(stage==2){
            string user="", pass="", succes="Contul a fost creat cu succes. Va puteti loga acum";
            string fail="User sau parola invalide. Incercati din nou", exista="User deja existent. Incercati din nou";
            command="Introduceti nume si parola (doar siruri de caractere alfanumerice de lungime intre 6 si 15)";
            to_half(command.size());
            cout<<command<<endl<<"User:\n"<<">";
            cin>>buffer;
            if(valid(buffer))
                user=buffer;
            cout<<"Parola:\n"<<">";
            buffer=read_password();
            if(valid(buffer))
                pass=buffer;
            if(user!="" && pass!=""){
                if(!is_unique(user)){
                    header();
                    to_half(exista.size());
                    cout<<exista<<endl;
                    continue;
                }
                else{
                    header();
                    to_half(succes.size());
                    cout<<succes<<endl;
                    stage=0;
                    add_account(user, pass);
                    continue;
                }
            }
            else{
                header();
                to_half(fail.size());
                cout<<fail<<endl;
                continue;
            }
        }
        if(stage==3){
            command="Introduceti 1 pentru a incarca date din fisier, 2 pentru a adauga o noua intrare";
            to_half(command.size());
            cout<<command<<endl;
            command="3 pentru a sterge o intrare, 4 pentru a cauta o intrare, 5 pentru statistici, sau Quit pentru iesire";
            to_half(command.size());
            cout<<command<<endl<<">";
            cin>>buffer;
            if(buffer=="1" || buffer=="2" || buffer=="3" || buffer=="4" || buffer=="5"){
                header();
                int val;
                stringstream ss(buffer);
                ss>>val;
                ss.ignore();
                stage=3+val;
                continue;
            }
            else if(buffer=="Quit"){
                break;
            }
            else{
                header();
                to_half(error.size());
                cout<<error<<endl;
                continue;
            }
        }
        if(stage==4){
            command="Introduceti cifra corespunzatoare unuia dintre urmatoarele fisiere csv sau Cancel pentru a iesi:";
            to_half(command.size());
            cout<<command<<endl;
            command="1 - Input_500.csv \t 2 - Input_10000.csv \t 3 - Input_250000.csv \t 4 - Generare custom";
            to_half(command.size());
            cout<<command<<endl<<">";
            cin>>buffer;
            if(buffer=="1"){
                header();
                string file="Input_500.csv";
                f.load(file);
                command="S-a incarcat fisierul Input_500.csv";
                to_half(command.size());
                cout<<command<<endl;
                stage=3;
                continue;
            }
            else if(buffer=="2"){
                header();
                string file="Input_10000.csv";
                f.load(file);
                command="S-a incarcat fisierul Input_10000.csv";
                to_half(command.size());
                cout<<command<<endl;
                stage=3;
                continue;
            }
            else if(buffer=="3"){
                header();
                string file="Input_250000.csv";
                f.load(file);
                command="S-a incarcat fisierul Input_250000.csv";
                to_half(command.size());
                cout<<command<<endl;
                stage=3;
                continue;
            }
            else if(buffer=="4"){
                int sz=0;
                header();
                command="Introduceti numarul de elemente ale fisierului [integer]";
                to_half(command.size());
                cout<<command<<endl<<endl<<">";
                cin>>buffer;
                header();
                stringstream size_ss(buffer);
                size_ss>>sz;
                Generator g;
                string file = g.write_file(sz);
                f.load(file);
                command="S-a incarcat fisierul "+file;
                to_half(command.size());
                cout<<command<<endl;
                stage=3;
                continue;
            }
            else if(buffer=="Cancel"){
                header();
                stage=3;
                continue;
            }
            else{
                header();
                to_half(error.size());
                cout<<error<<endl;
                continue;
            }
        }
        if(stage==5){
            int tip, cap;
            string vechi, ITP, sofer, marca, nrmat, succes="Vehiculul a fost introdus in flota.";
            string fail="Numarul de inmatriculare introdus exista deja. Incercati din nou", notip="Nu exista tipul mentionat. Incercati din nou";
            bool activ;
            command="Introduceti orice caracter pentru a continua, sau Cancel pentru a iesi";
            to_half(command.size());
            cout<<command<<endl<<">";
            cin>>buffer;
            if(buffer=="Cancel"){
                header();
                stage=3;
                continue;
            }
            else{
                header();
                command="Introduceti datele necesare conform indicatiilor";
                to_half(command.size());
                cout<<command<<endl;
            }
            cout<<endl<<"Tip vehicul [integer] (1 - Autoturism, 2 - Camion, 3 - Autobuz)"<<endl<<">";
            cin>>tip;
            cin.ignore();
            cout<<"Capacitate [integer]"<<endl<<">";
            cin>>cap;
            cin.ignore();
            cout<<"Vechime [string] (Format zz/ll/aaaa)"<<endl<<">";
            cin>>vechi;
            cout<<"Data ITP [string] (Format zz/ll/aaaa)"<<endl<<">";
            cin>>ITP;
            cout<<"Vehicul activ [bool] (0 - Inactiv, 1 - Activ)"<<endl<<">";
            cin>>activ;
            cin.ignore();
            cout<<"Sofer [string] (Format Nume Prenume sau None daca vehiculul este inactiv)"<<endl<<">";
            getline(cin, sofer, '\n');
            cout<<"Marca [string]"<<endl<<">";
            getline(cin, marca, '\n');
            cout<<"Numar inmatriculare [string] (Format JJ CC LLL, J=Judet, C=cifre, L=litere)"<<endl<<">";
            getline(cin, nrmat, '\n');
            if(tip==1){
                bool taxi;
                cout<<"Regim taxi [bool] (0 - Nu, 1 - Da)"<<endl<<">";
                cin>>taxi;
                cin.ignore();
                try{
                    f.add(cap, vechi, ITP, sofer, marca, nrmat, activ, taxi);
                }catch(...){
                    header();
                    to_half(fail.size());
                    cout<<fail<<endl;
                    continue;
                }
            }
            else if(tip==2){
                string rITP, rnrmat;
                cout<<"Numar inmatriculare remorca [string] (Format JJ CC LLL, J=Judet, C=cifre, L=litere)"<<endl<<">";
                getline(cin, rnrmat, '\n');
                cout<<"Data ITP remorca [string] (Format zz/ll/aaaa)"<<endl<<">";
                cin>>rITP;
                try{
                    f.add(cap, vechi, ITP, sofer, marca, nrmat, activ, rnrmat, rITP);
                }catch(...){
                    header();
                    to_half(fail.size());
                    cout<<fail<<endl;
                    continue;
                }
            }
            else if(tip==3){
                string ruta;
                cout<<"Ruta [string] (Format EN, N=Numar intreg"<<endl<<">";
                cin>>ruta;
                try{
                    f.add(cap, vechi, ITP, sofer, marca, nrmat, activ, ruta);
                }catch(...){
                    header();
                    to_half(fail.size());
                    cout<<fail<<endl;
                    continue;
                }
            }
            else{
                header();
                to_half(notip.size());
                cout<<notip<<endl;
                continue;
            }
            header();
            to_half(succes.size());
            cout<<succes<<endl;
            stage=3;
            continue;
        }
        if(stage==6){
            string succes="Vehiculul cu numarul de inmatriculare indicat a fost sters";
            string fail="Vehiculul cu numarul de inmatriculare indicat nu exista in flota";
            command="Introduceti orice caracter pentru a continua sau Cancel pentru a iesi";
            to_half(command.size());
            cout<<command<<endl<<">";
            cin>>buffer;
            if(buffer=="Cancel"){
                header();
                stage=3;
                continue;
            }
            header();
            command="Introduceti un numar de inmatriculare existent pentru a sterge vehiculul";
            to_half(command.size());
            cout<<command<<endl<<">";
            cin.ignore();
            getline(cin, buffer, '\n');
            try{
                f.del(buffer);
            }catch(...){
                header();
                to_half(fail.size());
                cout<<fail<<endl;
                continue;
            }
            header();
            to_half(succes.size());
            cout<<succes<<endl;
            stage=3;
            continue;
        }
        if(stage==7){
            string fail;
            command="Introduceti 1 pentru cautare dupa marca, 2 pentru cautare dupa numar inmatriculare, sau Cancel pentru a iesi";
            to_half(command.size());
            cout<<command<<endl<<">";
            cin>>buffer;
            if(buffer=="Cancel"){
                header();
                stage=3;
                continue;
            }
            else if(buffer=="1"){
                header();
                fail="Nu exista vehicule de marca introdusa. Incercati din nou";
                command="Introduceti o marca de vehicul";
                to_half(command.size());
                cout<<command<<endl<<">";
                cin.ignore();
                getline(cin, buffer, '\n');
                auto lista = f.find_all(buffer);
                if(lista.size()==0){
                    header();
                    to_half(fail.size());
                    cout<<fail<<endl;
                    continue;
                }
                header();
                command="Introduceti orice caracter pentru restart sau Cancel pentru a iesi";
                to_half(command.size());
                cout<<command<<endl;
                cout<<endl<<"\tS-au gasit "<<lista.size()<<" vehicule de marca indicata:"<<endl;

                for(auto &it:lista)
                    cout<<*it<<endl<<endl;


                cout<<endl<<">";
                cin>>buffer;
                if(buffer=="Cancel"){
                    header();
                    stage=3;
                    continue;
                }
                else{
                    header();
                    continue;
                }
            }
            else if(buffer=="2"){
                header();
                fail="Vehiculul cu numarul de inmatriculare indicat nu exista in flota";
                command="Introduceti un numar de inmatriculare existent pentru a afisa informatii despre vehicul";
                to_half(command.size());
                cout<<command<<endl<<">";
                cin.ignore();
                getline(cin, buffer, '\n');
                auto rez = f.find(buffer);
                if(rez==nullptr){
                    header();
                    to_half(fail.size());
                    cout<<fail<<endl;
                    continue;
                }
                else{
                    header();
                    command="Vehiculul a fost gasit. Introduceti orice caracter pentru restart sau Cancel pentru a iesi";
                    to_half(command.size());
                    cout<<command<<endl;
                    cout<<endl<<*rez<<endl<<">";
                    cin>>buffer;
                    if(buffer=="Cancel"){
                        header();
                        stage=3;
                        continue;
                    }
                    else{
                        header();
                        continue;
                    }
                }
            }
            else{
                header();
                to_half(error.size());
                cout<<error<<endl;
                continue;
            }
        }
        if(stage==8){
            command="Introduceti 1 pentru statistici ITP, 2 pentru statistici Inmatriculare";
            to_half(command.size());
            cout<<command<<endl;
            command="3 pentru statistici vechime, 4 pentru activitate sau Cancel pentru a iesi";
            to_half(command.size());
            cout<<command<<endl<<">";
            cin>>buffer;
            if(buffer=="1" || buffer=="2" || buffer=="3" || buffer=="4"){
                header();
                int val;
                stringstream ss(buffer);
                ss>>val;
                ss.ignore();
                stage=8+val;
                continue;
            }
            else if(buffer=="Cancel"){
                header();
                stage=3;
                continue;
            }
            else{
                header();
                to_half(error.size());
                cout<<error<<endl;
                continue;
            }
        }
        if(stage==9){
            command="Introduceti Cancel pentru a iesi";
            to_half(command.size());
            cout<<command<<endl<<endl;
            auto lista = f.get_expITP();
            cout<<"\tNumarul de vehicule al caror ITP expira in luna curenta: "<<lista.size()<<endl<<endl;
            if(lista.size()!=0)
                cout<<"\tVehiculele al caror ITP expira in luna curenta sunt: "<<endl;
            for(auto &it:lista){
                cout<<*it<<endl<<endl;
            }
            cout<<endl<<">";
            cin>>buffer;
            if(buffer=="Cancel"){
                header();
                stage=8;
                continue;
            }
            else{
                header();
                to_half(error.size());
                cout<<error<<endl;
                continue;
            }

        }
        if(stage==10){
            command="Introduceti 1 pentru Autoturisme, 2 pentru Camioane, 3 pentru Autobuze, sau Cancel pentru a iesi";
            string fail;
            to_half(command.size());
            cout<<command<<endl<<">";
            cin>>buffer;
            header();
            command="Introduceti orice caracter pentru restart, sau Cancel pentru a iesi";
            if(buffer=="1"){
                to_half(command.size());
                cout<<command<<endl;
                if(f.nr_inst<Autoturism*>()==0){
                    header();
                    fail="Nu exista autoturisme in flota";
                    to_half(fail.size());
                    cout<<fail<<endl;
                    continue;
                }
                auto lista = f.get_stat2<Autoturism*>();
                int c=0;
                cout<<endl<<"\tNumarul de autoturisme inmatriculate in functie de judet:"<<endl;
                for(auto &it:lista){
                    if(c!=0 && c%4==0)
                        cout<<endl;
                    cout<<"\t\t"<<it<<"\t";
                    c++;
                }
                cout<<endl<<">";
                cin>>buffer;
                if(buffer=="Cancel"){
                    header();
                    stage=8;
                    continue;
                }
                else{
                    header();
                    continue;
                }

            }
            else if(buffer=="2"){
                to_half(command.size());
                cout<<command<<endl;
                if(f.nr_inst<Camion*>()==0){
                    header();
                    fail="Nu exista camioane in flota";
                    to_half(fail.size());
                    cout<<fail<<endl;
                    continue;
                }
                auto lista = f.get_stat2<Camion*>();
                int c=0;
                cout<<endl<<"\tNumarul de camioane inmatriculate in functie de judet:"<<endl;
                for(auto &it:lista){
                    if(c!=0 && c%4==0)
                        cout<<endl;
                    cout<<"\t\t"<<it<<"\t";
                    c++;
                }
                cout<<endl<<">";
                cin>>buffer;
                if(buffer=="Cancel"){
                    header();
                    stage=8;
                    continue;
                }
                else{
                    header();
                    continue;
                }
            }
            else if(buffer=="3"){
                to_half(command.size());
                cout<<command<<endl;
                if(f.nr_inst<Autobuz*>()==0){
                    header();
                    fail="Nu exista autobuze in flota";
                    to_half(fail.size());
                    cout<<fail<<endl;
                    continue;
                }
                auto lista = f.get_stat2<Autobuz*>();
                int c=0;
                cout<<endl<<"\tNumarul de autobuze inmatriculate in functie de judet:"<<endl;
                for(auto &it:lista){
                    if(c!=0 && c%4==0)
                        cout<<endl;
                    cout<<"\t\t"<<it<<"\t";
                    c++;
                }
                cout<<endl<<">";
                cin>>buffer;
                if(buffer=="Cancel"){
                    header();
                    stage=8;
                    continue;
                }
                else{
                    header();
                    continue;
                }
            }
            else if(buffer=="Cancel"){
                stage=8;
                continue;
            }
            else{
                to_half(error.size());
                cout<<error<<endl;
                continue;
            }

        }
        if(stage==11){
            command="Introduceti 1 pentru Autoturisme, 2 pentru Camioane, 3 pentru Autobuze, sau Cancel pentru a iesi";
            string fail;
            to_half(command.size());
            cout<<command<<endl<<">";
            cin>>buffer;
            header();
            command="Introduceti orice caracter pentru restart, sau Cancel pentru a iesi";
            if(buffer=="1"){
                if(f.nr_inst<Autoturism*>()==0){
                    header();
                    fail="Nu exista autoturisme in flota";
                    to_half(fail.size());
                    cout<<fail<<endl;
                    continue;
                }
                auto output = f.get_stat1<Autoturism*>();

                to_half(command.size());
                cout<<command<<endl<<endl;
                cout<<"\tCel mai vechi autoturism din flota:"<<endl<<*get<Autoturism*>(output[0])<<endl;
                cout<<endl<<"\tCel mai nou autoturism din flota:"<<endl<<*get<Autoturism*>(output[1])<<endl;
                cout<<endl<<"\tCele mai multe autoturisme sunt din "<<get<string>(output[2])<<endl;
                cout<<endl<<"\tCele mai putine autoturisme sunt din "<<get<string>(output[3])<<endl<<">";
                cin.ignore();
                cin>>buffer;
                if(buffer=="Cancel"){
                    header();
                    stage=8;
                    continue;
                }
                else{
                    header();
                    continue;
                }
            }
            else if(buffer=="2"){
                if(f.nr_inst<Camion*>()==0){
                    header();
                    fail="Nu exista camioane in flota";
                    to_half(fail.size());
                    cout<<fail<<endl;
                    continue;
                }
                auto output = f.get_stat1<Camion*>();

                to_half(command.size());
                cout<<command<<endl<<endl;
                cout<<"\tCel mai vechi camion din flota:"<<endl<<*get<Camion*>(output[0])<<endl;
                cout<<endl<<"\tCel mai nou camion din flota:"<<endl<<*get<Camion*>(output[1])<<endl;
                cout<<endl<<"\tCele mai multe camioane sunt din "<<get<string>(output[2])<<endl;
                cout<<endl<<"\tCele mai putine camioane sunt din "<<get<string>(output[3])<<endl<<">";
                cin>>buffer;
                if(buffer=="Cancel"){
                    header();
                    stage=8;
                    continue;
                }
                else{
                    header();
                    continue;
                }
            }
            else if(buffer=="3"){
                if(f.nr_inst<Autobuz*>()==0){
                    header();
                    fail="Nu exista autobuze in flota";
                    to_half(fail.size());
                    cout<<fail<<endl;
                    continue;
                }
                auto output = f.get_stat1<Autobuz*>();

                to_half(command.size());
                cout<<command<<endl<<endl;
                cout<<"\tCel mai vechi autobuz din flota:"<<endl<<*get<Autobuz*>(output[0])<<endl;
                cout<<endl<<"\tCel mai nou autobuz din flota:"<<endl<<*get<Autobuz*>(output[1])<<endl;
                cout<<endl<<"\tCele mai multe autobuze sunt din "<<get<string>(output[2])<<endl;
                cout<<endl<<"\tCele mai putine autobuze sunt din "<<get<string>(output[3])<<endl<<">";
                cin>>buffer;
                if(buffer=="Cancel"){
                    header();
                    stage=8;
                    continue;
                }
                else{
                    header();
                    continue;
                }
            }
            else if(buffer=="Cancel"){
                stage=8;
                continue;
            }
            else{
                to_half(error.size());
                cout<<error<<endl;
                continue;
            }
        }
        if(stage==12){
            command="Introduceti Cancel pentru a iesi";
            to_half(command.size());
            cout<<command<<endl<<endl;
            cout<<"\tNumarul de vehicule inactive din flota: "<<f.get_inactive<Vehicul*>()<<endl<<endl<<"\tDintre care:"<<endl;
            cout<<"\t\tAutoturisme - "<<f.get_inactive<Autoturism*>()<<endl<<endl;
            cout<<"\t\tCamioane - "<<f.get_inactive<Camion*>()<<endl<<endl;
            cout<<"\t\tAutobuze - "<<f.get_inactive<Autobuz*>()<<endl<<endl;

            cout<<endl<<">";
            cin>>buffer;
            if(buffer=="Cancel"){
                header();
                stage=8;
                continue;
            }
            else{
                header();
                to_half(error.size());
                cout<<error<<endl;
                continue;
            }
        }
    }



}

int main()
{

    start_interface();
    return 0;
}
