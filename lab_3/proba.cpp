#include<iostream>
#include<vector>
using namespace std;


// funkcija za sumiranje jednog retka matrice (koristimo za Pruferov kod)
int sum_retka(int n, int *stablo, int redak){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += *(stablo + n*redak + i);
    }
    return sum;
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

int main(void){

    int *A = new int[9*9];

    
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            cin >> *(A + 9*i + j);
        }
        cout << endl;
    }


    vector<int> prufer2 = prufer(9, A);
    for(int i : prufer2)
        cout << i << " ";
    cout << endl;



    return 0;
}