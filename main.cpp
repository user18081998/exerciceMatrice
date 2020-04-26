#include "matrice.h"
#include "matrice.cpp"
#include <chrono>

using namespace std;
int main(){
    auto start = std::chrono::high_resolution_clock::now();
    MatriceDynamique<int> matrice(3,3,1);
    int k=1;
    for(int i=0;i<100000;i++){
        matrice=matrice+1;
    }auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    cout<<matrice<<endl;
    return 0;
}