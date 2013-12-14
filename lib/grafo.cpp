/*
 * Asignatura: Optimización 2013 - Grado en Ingeniería Informática
 * Actividad: Almacenamiento en la clase GRAFO (Práctica grafos 2)
 * Autor: Fernando González López - Peñalver (alu0100256543)
 * 
 * Descripción:
 *  Basandose en la clase implementada en la práctica anterior, implementar
 *  los algoritmos de Dijkstra y Bellman-Ford-Moore para encontrar los
 *  caminos mínimos en un digrafo.
 */ 
 
#include <stdint.h>
#include <iostream>
#include <fstream>
#include "grafo.h"
#include "aux.cpp"

// Constructor
Grafo::Grafo(const char nombrefichero[], int &errorapertura){
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
int Grafo::ParseFile(const char nombrefichero[]){
    ElementoLista dummy;
    unsigned i, j;
    int c;
    ifstream iss;
    
    iss.exceptions (ifstream::failbit | ifstream::badbit);
    try{
        iss.open(nombrefichero);
        iss >> n >> m >> dirigido;  // Leemos la primera línea
        LS.resize(n);
        for (uint8_t k = 0; k < m; k++){  // Leemos las 'm' aristas/arcos
            iss >> i >> j >> c;
            dummy.j = j - 1;
            dummy.c = c;
            LS[i-1].push_back(dummy);
            // Adyacencia en no dirigidos, evitando duplicar información de ciclos
            if ((dirigido == 0) && (i != j)){
                dummy.j = i -1;
                dummy.c = c;
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
                cout << lista[i][j].j+1 << "(" << lista[i][j].c << ")";
                j < lista[i].size() - 1 ? cout << "," : cout << "}" << endl;
            }
        }
    }
}
/**********************************************************************/
/************************* CAMINOS MÍNIMOS ****************************/
/**********************************************************************/

void Grafo::Dijkstra() {
    vector<bool> permLabel;  // Permanentemente etiquetados
    vector<int> d;
    vector<unsigned> pred;
    int min;
    unsigned s, candidato;

    permLabel.resize(n,false);
    d.resize(n,MAXINT);
    pred.resize(n,UERROR);

    cout << "Caminos minimos: Dijkstra" << endl;
    cout << "Nodo de partida? [1.."<< n << "]: ";
    cin >> (unsigned &) s;
    d[--s]=0; pred[s]=s;

    while ((!AllSetTo(permLabel, true)) && (GetminPos(d, permLabel) >= 0)){  // TODO: Evitar llamar dos veces a GetminPos. ¿Poner un do ... while?
        int i = GetminPos(d, permLabel); // Obtenemos el nodo (sin marcar) con menor valor d
        permLabel[i] = true;  // Lo marcamos
        for (unsigned j = 0; j < LS[i].size(); j++){
            if ((d[LS[i][j].j] > d[i] + LS[i][j].c) && (!permLabel[LS[i][j].j])){
                d[LS[i][j].j] = d[i] + LS[i][j].c;
                pred[LS[i][j].j] = i;
            }
        }
    }
    #ifdef DEBUG
        PrintVector(d);         // DEBUG
        PrintVector(pred);      // DEBUG
        PrintVector(permLabel); // DEBUG
    #endif
    CaminosMinimos(s, d, pred);
}

// Devuelve el valor del costo del arco/arista más negativo
int Grafo::GetSmallerCost(){
    int result = MAXINT;
    
    for (unsigned i = 0; i < LS.size(); i++){
        for (unsigned j = 0; j < LS[i].size(); j++){
            if (LS[i][j].c < result)
                result = LS[i][j].c;
        }
    }
    return result;
}

void Grafo::BellmanFordMoore(){  
    vector<int> d;
    vector<unsigned> pred;
    unsigned s;
    bool mejora;
    int sc = GetSmallerCost();

    d.resize(n,MAXINT);
    pred.resize(n,UERROR);

    cout << "Caminos minimos: Bellman – Ford - Moore" << endl;
    cout << "Nodo de partida? [1-"<< n << "]: ";
    cin >> (unsigned &) s;
    d[--s]=0; pred[s]=s;
    
    do {
        mejora = false;
        for (unsigned i = 0; i < LS.size(); i++){
            for (unsigned j = 0; j < LS[i].size(); j++){
                if (d[i] < MAXINT){  // No hay camino mayor que infinito + LS[i][j].c (nextline)
                    if (d[LS[i][j].j] > d[i] + LS[i][j].c){
                        d[LS[i][j].j] = d[i] + LS[i][j].c;
                        if (sc < 0) {
                            if (d[LS[i][j].j] <= (int)n*sc){
                                cout << "Detectado ciclo negativo => No hay solución" << endl;
                                return;
                            }
                        }
                        pred[LS[i][j].j] = i;
                        mejora = true;
                    }
                }
            }
        }
    } while(mejora);

    #ifdef DEBUG
        PrintVector(d);         // DEBUG
        PrintVector(pred);      // DEBUG
    #endif
    CaminosMinimos(s, d, pred);
    
}
