#include <stdint.h>
#include <iostream>
#include <fstream>
#include "grafo.h"

// Constructor
Grafo::Grafo(char nombrefichero[], int &errorapertura){
    errorapertura = ParseFile(nombrefichero);
}

// Actualizar
void Grafo::Actualizar(char nombrefichero[], int &errorapertura){
    Clear();
    errorapertura = ParseFile(nombrefichero);
}

// Info_Grafo
void Grafo::Info_Grafo(){
    dirigido == 0 ? cout << "Grafo NO DIRIGIDO" << endl : cout << "Grafo DIRIGIDO" << endl;
    cout << "Número de nodos = " << n << endl;
    cout << "Número de ";
    dirigido == 0 ? cout << "aristas = " : cout << "arcos = ";
    cout << m << endl;
}

// Mostrar_Listas
// TODO: Preguntar lo que debe hacer ...
void Grafo::Mostrar_Listas(int l){
    MostrarLista(LS);
    cout << "################" << endl;
    MostrarLista(LP);
}

// DFS
void Grafo::dfs(unsigned i, vector<bool> &visitado){
    visitado[i] = true;
    cout << i + 1 << ", ";
    for (uint16_t j = 0; j < LS[i].size(); j++)
        if (visitado[LS[i][j].j] == false)
            dfs(LS[i][j].j, visitado);
}

// ListaPredecesores
void Grafo::ListaPredecesores(){
    if (dirigido == 1){
        ElementoLista dummy;

        LP.clear();
        LP.resize(n);
        for (uint16_t i = 0; i < LS.size(); i++)
            for (uint16_t j = 0; j < LS[i].size(); j++){
                dummy.j = i;
                LP[LS[i][j].j].push_back(dummy);
            }
        
    }
}

// Clear
void Grafo::Clear(){
    n = m = dirigido = 0;
    LS.clear();
    LP.clear();
}

// ParseFile
int Grafo::ParseFile(char nombrefichero[]){
    ElementoLista dummy;
    unsigned i, j;
    ifstream iss;
    
    iss.exceptions (ifstream::failbit | ifstream::badbit);
    try{
        iss.open(nombrefichero);
        iss >> n >> m >> dirigido;  // Leemos la primera línea
        LS.resize(n);
        for (uint8_t k = 0; k < m; k++){
            iss >> i >> j;
            dummy.j = j - 1;
            LS[i-1].push_back(dummy);
        }
        iss.close();
    }catch (ifstream::failure e){
        cerr << "Error abriendo el fichero " << nombrefichero << endl;
        return UERROR;  // TODO: ¿Es este error?
    }
    return NOERROR;
}

// MostrarLista
void Grafo::MostrarLista(const vector<LA_nodo> &lista){
    for (uint16_t i = 0; i < lista.size(); i ++){
        cout << "Γ[" << i + 1 <<  "] = ";
        if (lista[i].size() <= 0)
            cout << "Ø" << endl;
        else{
            cout << "{";
            for (uint16_t j = 0; j < lista[i].size(); j++)
                j < lista[i].size() - 1 ? cout << lista[i][j].j+1 << "," : cout << lista[i][j].j+1 << "}" << endl;
        }
    }
}
