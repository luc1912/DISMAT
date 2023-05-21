#include<iostream>
#include<cmath>
using namespace std;

double vrati(int broj, double zadnji, double predzadnji, double lam1, double lam2){
    // zadnji = aₙ₋₁
    // predzadnji = aₙ₋₂
    if(broj == 1) return predzadnji;
    if(broj == 2) return zadnji;
    return lam1 * vrati((broj - 1), zadnji, predzadnji, lam1, lam2) + lam2 * vrati((broj - 2), zadnji, predzadnji, lam1, lam2);
}

int main(void){

    //KORISNIK UNOSI PODATKE

    int broj;
    cout << "Unesite nenegativan cijeli broj: ";
    cin >> broj;
    cout << endl;

    double b[3];
    for(int i = 0; i < 3; i++){
        cout << "Unesite vrijednost broja b_" << i << ": ";
        cin >> b[i];
        cout << endl;
    }

    double c[3];
    for (int i = 0; i < 3; i++){
        cout << "Unesite vrijednost broja c_" << i << ": ";
        cin >> c[i];
        cout << endl;
    }

    float y = (float)b[0] / (float)c[0];
    float z = (float)b[1] / (float)c[1];
    float w = (float)b[2] / (float)c[2];

    if(y == z && z == w && y == w){
        cout << "lambda1 i lambda2 se ne mogu jednoznacno odrediti" << endl; //λ₁,λ₂∈ℝ
    }

    else{   
        // RAČUNJANJE λ₁,λ₂
        double lam1, lam2;

        lam1 = (c[2] * b[0] - b[2] * c[0]) / (c[1] * b[0] - b[1] * c[0]);
        lam2 = (b[1] * c[2] - c[1] * b[2]) / (b[1] * c[0] - b[0] * c[1]);

        // RAČUNJANJE bn
        double bn = vrati(broj, b[2], b[1], lam1, lam2);
        cout << "Vrijednost broja b_n:" << " " << bn << endl;
    }


    return 0;
}