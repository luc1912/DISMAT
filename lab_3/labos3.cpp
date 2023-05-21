#include <cmath>
#include <iostream>
#include <vector>
#include<climits>
using namespace std;

// sumira jedinice u polju posjetio (koristimo za povezanost)
int sum_polja(int n, int *posjetio) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += posjetio[i];
    }
    return sum;
}



// funkcija za sumiranje jednog retka matrice (koristimo za Pruferov kod)
int sum_retka(int n, int *stablo, int redak){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += *(stablo + n*redak + i);
    }
    return sum;
}



// funkcija koja provjerava povezanost grafa
void povezan(int n, int trenutni, int *posjetio, int *mat_sus) {
    for (int i = 0; i < n; i++) {
        if (*(mat_sus + n * trenutni + i) == 0 || *(posjetio + i) != 0) {
            continue;
        } else {
            int novi_trenutni = i;
            posjetio[novi_trenutni] = 1;
            povezan(n, novi_trenutni, posjetio, mat_sus);
        }
    }
}



// funkcija koja provjerava nalazi li se neki element u polju vektora
bool contains(vector<int> vrhovi, int index){
    for(int i = 0; i < vrhovi.size(); i++){
        if(vrhovi.at(i) == index) return true;
    }
    return false;
}


// funkcija koja nalazi minimalno razapinjuće stablo
void mrs(int n, int *mat_pov, int *stablo, vector<int> vrhovi){
    while(vrhovi.size() != n){
        int min = INT_MAX;
        int indeksi[2] = {0, 0}; // vrhovi za koje smo našli novi najmanji brid
        for(int i = 0; i < n; i++){
            bool index_i = contains(vrhovi, i);
            if(index_i){ // želimo naći vrh koji je već dodan u stablo
                for(int j = 0; j < n; j++){
                    bool index_j = contains(vrhovi, j);
                    if(!index_j){ //želimo naći j koji još nije dodan u stablo da ne zatvorimo ciklus
                        if(*(mat_pov + n*i + j) < min && *(mat_pov + n*i + j) != 0){
                             min = *(mat_pov + n*i + j);
                             indeksi[0] = i;
                             indeksi[1] = j;
                        }
                    }
                }
            }
        }
        vrhovi.push_back(indeksi[1]);
        *(stablo + n*indeksi[0] + indeksi[1]) = *(stablo + n*indeksi[1] + indeksi[0]) = 1;         
    }
}



// funkcija za računanje Pruferovog koda
vector<int> prufer(int n, int *stablo){
    vector<int> prf;
    for(int a = 0; a < n; a++){
        if(prf.size() == (n-2)) break;
        for(int i = 0; i < n; i++){
            if(sum_retka(n, stablo, i) == 1){
                for(int j = 0; j < n; j++){
                    if(*(stablo + n*i + j) == 1){
                        prf.push_back(j+1);
                        *(stablo + n*i + j) = *(stablo + n*j + i) = 0;
                    }
                }
                break;
            }
        } 
    }
    return prf;    
}



int main(void) {

    // unos podataka
    int n;
    cout << "Unesite prirodan broj n: ";
    cin >> n;
    
    
        
    char slova[] = {'a', 'b', 'c'};
    int abc[3];
    for (int i = 0; i < 3; i++) {
        cout << "Unesite prirodan broj " << slova[i] << ": ";
        cin >> abc[i];
    }
    cout << endl;
    
    
    
    // matrica povezanosti
    int *mat_pov = new int[n*n];
    int minimal = INT_MAX;  // najmanja težina
    vector<int> vrhovi;
    vrhovi.push_back(-1);
    vrhovi.push_back(-1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int pom;
            if(i < j){
                pom = ((abs(abc[0]*i - abc[1]*j)) / abc[2]);
            }
            else if(j < i){
                pom = ((abs(abc[1]*i - abc[0]*j)) / abc[2]);
            }
            if(pom != 0 && (i != j)){
                *(mat_pov + n*(i-1) + (j-1)) = pom;
            }
            else{
                *(mat_pov + n*(i-1) + (j-1)) = 0;
            }
              if(pom < minimal && pom > 0){
                minimal = pom;
                vrhovi[0] = i-1;
                vrhovi[1] = j-1;                          
            }
        }
    }
    
    
    
    // matrica susjedstva
       int *mat_sus = new int[n*n];
     for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int pom;
            if(i < j){
                pom = ((abs(abc[0]*i - abc[1]*j)) / abc[2]);
            }
            else{
                pom = ((abs(abc[1]*i - abc[0]*j)) / abc[2]);
            }
            if(pom != 0 && (i != j)){
                *(mat_sus + n*(i-1) + (j-1)) = 1;
            }
            else{
                *(mat_sus + n*(i-1) + (j-1)) = 0;
            }
        }
    }
    
    
    
    // polje koje ćemo slati u funkciju za povezanost kojim ćemo provjeravati jesmo posjetili neki vrh
    int *posjetio = new int[n];
    for (int i = 0; i < n; i++) {
        posjetio[i] = 0;
    }
    
        
    
    // poziv funkcije za povezanost
    povezan(n, 0, posjetio, mat_sus);

    

    // matrica koja će biti matrica susjedstva minimalnog stabla
    int *stablo = new int[n*n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            *(stablo + n*i + j) = 0;
        }
    }
    *(stablo + n*vrhovi[0] + vrhovi[1]) = *(stablo + n*vrhovi[1] + vrhovi[0]) = 1;

    
        
    
    // provjeravamo jesu svi indeksi polja posjetio = 1 -> znači da smo posjetili sve vrhove i da je graf povezan
    int sum = sum_polja(n, posjetio);
    if (sum == n || n == 1) {
        cout << "Graf je povezan" << endl;
        if(n != 1){
            mrs(n, mat_pov, stablo, vrhovi);
            vector<int> pfk = prufer(n, stablo);
            cout << "Pruferov kod : ";
            for(int i : pfk)
                cout << i << " ";
            cout << endl;
        }

    } else {
        cout << "Graf nije povezan" << endl;
    }
    cout << endl;

    return 0;
}