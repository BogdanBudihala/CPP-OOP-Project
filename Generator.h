#ifndef TEST_2_GENERATOR_H
#define TEST_2_GENERATOR_H
#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

class Generator {
private:
    string get_mat();
    static string get_ITP();
    static string get_vechime();
    string get_nume();
    void load_nume();
    vector <string> mat;
    vector <string> jud;
    vector <string> mar;
    vector <string> nume;
    string generate();

public:
    Generator();
    string write_file(int);
};


#endif //TEST_2_GENERATOR_H
