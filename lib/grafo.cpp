/*
 * Asignatura: Optimización 2013 - Grado en Ingeniería Informática
 * Actividad: Almacenamiento en la clase GRAFO (Práctica grafos 1)
 * Autor: Fernando González López - Peñalver (alu0100256543)
 * 
 * Descripción:
 * El objetivo de esta actividad es escribir un programa que gestione
 * la carga de los datos de un grafo a partir de las estructuras de
 * sucesores o predecesores, en el caso de los grafos dirigidos, y con
 * las adyacencias, en el caso de los grafos no dirigidos. Usaremos la 
 * clase GRAFO que, desde esta primera actividad, estará dotado de lo
 * esencial para poder codificar los grafos y trabajar con ellos bajo
 * distintos algoritmos. El programa de prueba tendrá forma de menú, que
 * interactúa con el usuario para ejecutar las distintas opciones
 * posibles. Se hace uso del Recorrido en Profundidad para calcular las
 * componentes conexas de los digrafos.
 */ 
 
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
    dirigido == 0 ? cout << "Grafo NO DIRIGIDO" : cout << "Grafo DIRIGIDO";
    cout << endl << "Número de nodos = " << n << endl;
    cout << "Número de ";
    dirigido == 0 ? cout << "aristas = " : cout << "arcos = ";
    cout << m << endl;
}

// Mostrar_Listas
void Grafo::Mostrar_Listas(int l){
    string symbol = (dirigido == 0) ? "Γ" : "Γ+";
    switch (l){
        case 0:  // Sucesores / Adyacencia
            MostrarLista(symbol, LS);
            break;
        case 1:  // Predecesores
            MostrarLista("Γ-", LP);
            break;
    }
}

// Comprueba si el vector de visitados está todo a "true".
// Si no lo está devuelve la posición del primer elemento "false"
// Si lo está devuelve -1
int TestVisitados(vector<bool> &visitados){
    for (unsigned i = 0; i < visitados.size(); i++){
        if (!visitados[i])
            return i;
    }
    return -1;
}

// ComponentesConexas
void Grafo::ComponentesConexas(){
    vector<bool> visitados(n, false);
    vector<unsigned> conexos;  // Nodos conexos
    unsigned nConexa = 1; // Numero de la componente conexa
    int nextNode; // Próximo nodo con el que iniciar el DFS

    // Mientras existan nodos sin visitar mostramos componentes conexas en pantalla
    // y llamamos al DFS para calcularlas
    while ((nextNode = TestVisitados(visitados)) >= 0){
        dfs(nextNode, visitados, conexos);
        cout << "Componente conexa " << nConexa << ": " << endl;
        for (unsigned i = 0; i < conexos.size(); i++){  // Mostramos el vector de nodos conexos
            cout << conexos[i] + 1;
            i < conexos.size() - 1 ? cout << ", " : cout << ".";
        }
        cout << endl;
        conexos.clear();
        nConexa++;
    }
}

// DFS
void Grafo::dfs(unsigned i, vector<bool> &visitado, vector<unsigned> &conexas){
    visitado[i] = true;
    conexas.push_back(i);
    for (uint16_t j = 0; j < LS[i].size(); j++)
        if (visitado[LS[i][j].j] == false)
            dfs(LS[i][j].j, visitado, conexas);
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
        for (uint8_t k = 0; k < m; k++){  // Leemos las 'm' aristas/arcos
            iss >> i >> j;
            dummy.j = j - 1;
            LS[i-1].push_back(dummy);
            // Adyacencia en no dirigidos, evitando duplicar información de ciclos
            if ((dirigido == 0) && (i != j)){
                dummy.j = i -1;
                LS[j-1].push_back(dummy);
            }
        }
        iss.close();
    }catch (ifstream::failure e){
        cerr << "Error abriendo el fichero " << nombrefichero << endl;
        return UERROR;
    }
    return NOERROR;
}

// MostrarLista
void Grafo::MostrarLista(string symbol, const vector<LA_nodo> &lista){
    for (uint16_t i = 0; i < lista.size(); i ++){
        cout << symbol << "[" << i + 1 <<  "] = ";
        if (lista[i].size() <= 0)
            cout << "Ø" << endl;
        else{
            cout << "{";
            for (uint16_t j = 0; j < lista[i].size(); j++){
                cout << lista[i][j].j+1;
                j < lista[i].size() - 1 ? cout << "," : cout << "}" << endl;
            }
        }
    }
}
