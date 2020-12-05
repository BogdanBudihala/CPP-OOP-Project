#include "Generator.h"
string Generator::get_ITP(){
    int m=rand()%12+1, y=rand()%10+2020, d;
    if(m==2)
        d=rand()%28+1;
    else if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)
        d=rand()%31+1;
    else
        d=rand()%30+1;

    string rez;
    if(d<10){
        if(m<10){
            ostringstream oss;
            oss<<'0'<<d<<'/'<<'0'<<m<<'/'<<y;
            rez = oss.str();
        }
        else{
            ostringstream oss;
            oss<<'0'<<d<<'/'<<m<<'/'<<y;
            rez = oss.str();
        }
    }
    else{
        if(m<10){
            ostringstream oss;
            oss<<d<<'/'<<'0'<<m<<'/'<<y;
            rez = oss.str();
        }
        else{
            ostringstream oss;
            oss<<d<<'/'<<m<<'/'<<y;
            rez = oss.str();
        }
    }

    return rez;
}
string Generator::get_vechime(){
    int m=rand()%12+1, y=rand()%21+1990, d;
    if(m==2)
        d=rand()%28+1;
    else if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)
        d=rand()%31+1;
    else
        d=rand()%30+1;

    string rez;
    if(d<10){
        if(m<10){
            ostringstream oss;
            oss<<'0'<<d<<'/'<<'0'<<m<<'/'<<y;
            rez = oss.str();
        }
        else{
            ostringstream oss;
            oss<<'0'<<d<<'/'<<m<<'/'<<y;
            rez = oss.str();
        }
    }
    else{
        if(m<10){
            ostringstream oss;
            oss<<d<<'/'<<'0'<<m<<'/'<<y;
            rez = oss.str();
        }
        else{
            ostringstream oss;
            oss<<d<<'/'<<m<<'/'<<y;
            rez = oss.str();
        }
    }

    return rez;
}
string Generator::get_mat(){
    string rez;
    int indx = rand()%jud.size(), nr, lit;
    rez=jud[indx];
    if(jud[indx]=="B")
        nr=rand()%1000;
    else
        nr=rand()%100;
    ostringstream oss;
    oss<<nr;
    rez = rez+" "+oss.str()+" ";
    for(int i=0;i<3;i++){
        lit=rand()%26+65;
        rez+=(char)lit;
    }
    if(find(mat.begin(), mat.end(), rez)!=mat.end())
        return get_mat();
    return rez;
}

Generator::Generator() {
    this->jud={"AB", "AR", "AG", "BC", "BH", "BN", "BT", "BR", "BV", "BZ", "CL", "CS", "CJ", "CT", "CV", "DB", "DJ", "GL", "GR", "GJ",
               "HR", "HD", "IL", "IS", "IF", "MM", "MH", "MS", "NT", "OT", "PH", "SJ", "SM", "SB", "SV", "TR", "TM", "TL", "VL", "VS",
               "VN", "B"};
    this->mar={"Volkswagen", "Toyota", "Daimler", "Ford", "GM", "Audi", "Honda", "Jeep", "Chrysler", "Chevrolet", "Hyunday", "Dodge",
               "Mazda", "Nissan", "Buick", "Lexus", "Kia", "Mercedes Benz", "Volvo", "GMC", "Infiniti", "Peugeot", "Pontiac", "Suzuki",
               "Citroen", "Fiat"};
    load_nume();
    srand(time(NULL));
}

string Generator::generate() {
    string rez;
    int tip=rand()%3+1, cap;
    string ITP = get_ITP(), plc=get_mat(), vec=get_vechime();
    int activ=rand()%2, indx=rand()%mar.size();
    string marca = mar[indx], num;
    if(activ==1)
        num=get_nume();
    else num="None";
    if(tip==1){
        int taxi=rand()%2;
        if(taxi==0)
            cap=rand()%2+3;
        else
            cap=4;
        ostringstream oss;
        oss<<tip<<','<<cap<<','<<vec<<','<<ITP<<','<<num<<','<<marca<<','<<plc<<','<<activ<<','<<taxi;
        rez=oss.str();
    }
    else if(tip==2){
        string r_plc = get_mat(), r_ITP=get_ITP();
        cap=rand()%70+50;
        cap=cap-cap%5;
        ostringstream oss;
        oss<<tip<<','<<cap<<','<<vec<<','<<ITP<<','<<num<<','<<marca<<','<<plc<<','<<activ<<','<<r_plc<<','<<r_ITP;
        rez=oss.str();
    }
    else if(tip==3){
        string ruta="E";
        cap=rand()%150+50;
        int nr=rand()%8+1;
        char concat = nr+'0';
        ruta = ruta + concat;
        ostringstream oss;
        oss<<tip<<','<<cap<<','<<vec<<','<<ITP<<','<<num<<','<<marca<<','<<plc<<','<<activ<<','<<ruta;
        rez=oss.str();
    }
    return rez;
}

void Generator::load_nume() {
    ifstream f("People.txt");
    string buffer;
    int i=5000;
    while(f>>buffer && i-- >= 0){
      nume.push_back(buffer);
    }
}

string Generator::get_nume() {
    int indx_1 = rand()%nume.size(), indx_2=rand()%nume.size();
    string rez = nume[indx_1]+" "+nume[indx_2];
    return rez;
}

string Generator::write_file(int qty) {
    string filename;
    ostringstream oss;
    oss<<"Input_"<<qty<<".csv";
    filename = oss.str();
    ofstream g(filename);
    for(int i=0;i<qty;i++){
        g<<generate()<<endl;
    }
    return filename;
}
