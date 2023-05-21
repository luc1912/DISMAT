//provjerava jel graf povezan i hamiltonovski
#include<iostream>
#include<cmath>
using namespace std;

//sumira jedinice u polju posjetio
int sum_polja(int n, int *posjetio){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += posjetio[i];
    }
    return sum;
}

//funkcija koja provjerava jel graf povezan
void povezan(int n, int trenutni, int *posjetio, int *mat_sus){
    for(int i = 0; i < n; i++){
        if(*(mat_sus + n*trenutni + i) == 0 || *(posjetio + i) != 0){ 
            continue;
        }else{
            int novi_trenutni = i;
            posjetio[novi_trenutni] = 1;
            povezan(n, novi_trenutni, posjetio, mat_sus);
        }
    }
}

//funkcija provjerava jel graf hamiltonovski
bool hamiltonovski(int n, int trenutni, int *posjetio, int *mat_sus){

    posjetio[trenutni] = 1;

    if (sum_polja(n, posjetio) == n && *(mat_sus + n * trenutni) != 0){
        return true;
    }

    for (int i = 0; i < n; i++){
        if (*(mat_sus + n * trenutni + i) == 0 || *(posjetio + i) != 0){
            continue;
        }
        else{
            int novi_trenutni = i;
            int *novopolje = new int[n];
            for (int i = 0; i < n; i++){
                novopolje[i] = posjetio[i];
            }
            bool hamilton = hamiltonovski(n, novi_trenutni, novopolje, mat_sus);
            delete[] novopolje;
            if (hamilton)
                return hamilton;
            else
                continue;
        }
    }
    return false;
}

int main(void){

    int n;
    cout << "Unesite prirodan broj n: ";
    cin >> n;
    cout << endl;

    int k[4];
    for(int i = 0; i < 4; i++){
        cout << "Unesite vrijednost prirodnog broja k_" << i+1 << ": ";
        cin >> k[i];
        cout << endl;
    }

    //matrica susjedstva
    int *mat_sus = new int[n*n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (abs(i-j) == k[0] || abs(i-j) == k[1] || abs(i-j) == k[2] || abs(i-j) == k[3]){
                *(mat_sus + n*i + j) = 1;
            }else{
                *(mat_sus + n * i + j) = 0;
            }
        }
    }

    //ispisivanje matrice susjedstva (samo za provjeru)
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << *(mat_sus + n * i + j) << " ";
        }
        cout << endl;
    }
    cout << endl;

    //polje koje ćemo slati u funkciju za povezanost kojim ćemo provjeravati jesmo posjetili neki vrh
    int *posjetio = new int[n];
    for(int i = 0; i < n; i++){
        posjetio[i] = 0;
    }

    // polje koje ćemo slati u funkciju za hamil kojim čemo provjeravati jesmo posjetili neki vrh
    int *posjetio2 = new int[n];
    for (int i = 0; i < n; i++){
        posjetio2[i] = 0;
    }

    //poziv funkcije za povezanost
    povezan(n, 0, posjetio, mat_sus);

    //provjeravamo jesu svi indeksi polja posjetio = 1 -> znači da smo posjetili sve vrhove i da je graf povezan
    int sum = sum_polja(n, posjetio);
    if(sum == n || n == 1){
        cout << "Graf je povezan" << endl;
        bool hamil = hamiltonovski(n, 0, posjetio2, mat_sus);
        if(hamil == true && n > 2){
            cout << "Graf je hamiltnosvki";
        }else{
            cout << "Graf nije hamiltonovski";
        }
    }else{
        cout << "Graf nije povezan" << endl;
        cout << "Graf nije hamiltonovski" << endl;
    }
    
    return 0;
}