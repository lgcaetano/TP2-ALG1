#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "grafo.h"

using namespace std;

int main(){

    int numAeroportos, numRotas;

    cin >> numAeroportos;       

    Grafo linhaAerea(numAeroportos);

    cin >> numRotas;

    int i = 0;

    int origem, destino;          

    for(i = 0; i < numRotas; i++){
        cin >> origem;
        cin >> destino;
        linhaAerea.construirAresta(origem, destino);
    }

    cout << linhaAerea.arestasFaltando() << endl;

    return 1;            
}       