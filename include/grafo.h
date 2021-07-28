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

int max(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}




vector<int> copyOfVector(vector<int> vetor){
    int i = 0;
    vector<int> copia;
    for(i = 0; i < vetor.size(); i++){
        copia.push_back(vetor[i]);
    }
    return copia;
}

void clearStack(stack<int> pilha){
    while(!pilha.empty()){
        pilha.pop();
    }
}


bool vectorContainsElement(vector<int> vetor, int element){
    return count(vetor.begin(), vetor.end(), element);
}


bool matrixContainsElement(vector<vector<int>> matriz, int element){
    int i = 0;
    for(i = 0; i < matriz.size(); i++){
        if(vectorContainsElement(matriz[i], element)){
            return true;
        }
    }
    return false;
}




class Grafo{

    public:
        Grafo(int _numVertices);

        int contemAresta(int origem, int destino);
        
        void construirAresta(int origem, int destino);
        
        vector<int> dfs(int verticeAtual, vector<int> &verticesVisitados, stack<int> &verticesParaKosaraju);

        vector<vector<int>> algoritmoDeKosaraju();
        
        void construirGrafoDeSCCs();
        
        int arestasFaltando();

    private:
        vector<vector<int>> matrizDeAdjacencia;
        int numVertices;
        Grafo* grafoDeComponentesConectados;
        void grafoTransposto(Grafo grafoOriginal);
        int numVerticesSemSaida();
        int numVerticesSemChegada();
        int numSCCs;
};



Grafo::Grafo(int _numVertices){
    numVertices = _numVertices;
    grafoDeComponentesConectados = nullptr;
    int i = 0;
    // int j = 0;
    for(i = 0; i < numVertices; i++){
        matrizDeAdjacencia.push_back(vector<int>(numVertices, 0));
    }
}



void Grafo::construirAresta(int origem, int destino){
    matrizDeAdjacencia[origem - 1][destino - 1] = 1;
}

int Grafo::contemAresta(int origem, int destino){
    return matrizDeAdjacencia[origem][destino];
}



vector<int> Grafo::dfs(int verticeAtual, vector<int> &verticesVisitados, stack<int> &verticesParaKosaraju){
    verticesVisitados.push_back(verticeAtual);
    int i = 0;
    for(i = 0; i < numVertices; i++){
        if(matrizDeAdjacencia[verticeAtual][i] == 1 && !vectorContainsElement(verticesVisitados, i)){
            dfs(i, verticesVisitados, verticesParaKosaraju);
        }
    }
    verticesParaKosaraju.push(verticeAtual);
    return copyOfVector(verticesVisitados);
}

void Grafo::grafoTransposto(Grafo grafoOriginal){
    int i = 0, j = 0;
    for(i = 0; i < numVertices; i++){
        for(j = 0; j < numVertices; j++){
            if(grafoOriginal.contemAresta(i, j))
                construirAresta(j + 1, i + 1);
        }
    }
}





vector<vector<int>> Grafo::algoritmoDeKosaraju(){

    vector<vector<int>> componentesConectados;

    vector<int> verticesVisitados;

    stack<int> verticesEmOrdemDecrescente;

    int i = 0;

    Grafo grafoTransposto = Grafo(numVertices);

    grafoTransposto.grafoTransposto(*this);

    for(i = 0; i < numVertices; i++){
        if(!vectorContainsElement(verticesVisitados, i)){
            dfs(i, verticesVisitados, verticesEmOrdemDecrescente);
        }
    }

    int currentElement;
    vector<int> auxiliaryVector;
    stack<int> auxiliaryStack;

    while(!verticesEmOrdemDecrescente.empty()){
        currentElement = verticesEmOrdemDecrescente.top();
        if(!matrixContainsElement(componentesConectados, currentElement)){
            componentesConectados.push_back(grafoTransposto.dfs(currentElement, auxiliaryVector, auxiliaryStack));
        }
        verticesEmOrdemDecrescente.pop();
        auxiliaryVector.clear();
        clearStack(auxiliaryStack);
    }
    numSCCs = componentesConectados.size();
    return componentesConectados;    
}


void Grafo::construirGrafoDeSCCs(){
     vector<vector<int>> componentesConectados = algoritmoDeKosaraju();
     grafoDeComponentesConectados = new Grafo(componentesConectados.size());
     int i = 0, j = 0, k = 0, t = 0;
     for(i = 0; i < componentesConectados.size(); i++){
         for(j = 0; j < componentesConectados[i].size(); j++){
             for(k = 0; k < componentesConectados.size(); k++){
                 for(t = 0; t < componentesConectados[k].size(); t++){
                     if(k != i && contemAresta(componentesConectados[i][j], componentesConectados[k][t])){
                         grafoDeComponentesConectados->construirAresta(i, k);
                     }
                }
            }
        }
    }
}


int Grafo::numVerticesSemSaida(){
    int resultado = 0;
    int i = 0;
    for(i = 0; i< numVertices; i++){
        if(!vectorContainsElement(matrizDeAdjacencia[i], 1))
            resultado++;
    }
    return resultado;
}

int Grafo::numVerticesSemChegada(){
    int i = 0, j = 0;
    int resultado = 0;

    for(i = 0; i < numVertices; i++){
        for(j = 0; j < numVertices; j++){
            if(matrizDeAdjacencia[j][i] == 1){
                resultado++;
                break;
            }
        }
    }
    return resultado;
}

int Grafo::arestasFaltando(){
    if(grafoDeComponentesConectados == nullptr)
        construirGrafoDeSCCs();
    if(numVertices == numSCCs){
        return max(numVerticesSemChegada(), numVerticesSemSaida());
    } else {
        return grafoDeComponentesConectados->arestasFaltando();
    }
}






#endif