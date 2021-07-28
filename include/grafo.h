#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

class Grafo{

    public:
        Grafo(int numVertices);
        
        void construirAresta(int origem, int destino);
        
        vector<int> dfs(int verticeAtual, vector<int> &verticesVisitados, stack<int> &verticesParaKosaraju);

        vector<vector<int>> algoritmoDeKosaraju();
        
        void construirGrafoDeSCCs();
        
        int arestasFaltando();

    private:
        vector<vector<int>> matrizDeAdjacencia;
        int numVertices;
        Grafo* grafoDeComponentesConectados;
        Grafo grafoReverso();
        int numVerticesSemSaida();
        int numVerticesSemChegada();
};

Grafo::Grafo(int numVertices){
    int i = 0;
    int j = 0;
    for(i = 0; i < numVertices; i++){
        matrizDeAdjacencia.push_back(vector<int>(numVertices, 0));
    }
}

void Grafo::construirAresta(int origem, int destino){
    matrizDeAdjacencia[origem - 1][destino - 1] = 1;
}

vector<int> Grafo::dfs(int verticeAtual, vector<int> &verticesVisitados, stack<int> &verticesParaKosaraju){
    verticesVisitados.push_back(verticeAtual);
    int i = 0;
    for(i = 0; i < numVertices; i++){
        if(matrizDeAdjacencia[verticeAtual][i] == 1 && count(verticesVisitados.begin(), verticesVisitados.end(), i) == 0){
            dfs(i, verticesVisitados, verticesParaKosaraju);
        }
    }
    verticesParaKosaraju.push(verticeAtual);
    return verticesVisitados;
}








#endif