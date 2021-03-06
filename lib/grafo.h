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
 
#include <vector>

using namespace std;

#ifndef GRAFO_H
#define GRAFO_H

const unsigned NOERROR = 0;
const unsigned UERROR = 65000;
const int MAXINT = 1000000;

typedef struct{
    unsigned j;  // nodo
    int      c;  // costo
} ElementoLista;

typedef vector<ElementoLista> LA_nodo;
typedef vector< pair< pair<unsigned, unsigned>, unsigned > > minpaths; // Estructura que representa el costo del camino de un nodo a otro
class Grafo{
  public:
    unsigned        dirigido;
    Grafo(const char nombrefichero[], int &errorapertura);
    // Getters
    unsigned N() const { return n; }
    unsigned M() const { return m; }
    
    void Actualizar(char nombrefichero[], int &errorapertura);
    void Info_Grafo();
    void Mostrar_Listas(int l);
    void ListaPredecesores();
    void ComponentesConexas();
    void Dijkstra();
    minpaths* Dijkstra(unsigned s);
    void BellmanFordMoore();
    ~Grafo() { Clear(); }
  private:
    void Clear();
    int ParseFile(const char nombrefichero[]);  // Devuelve el posible "errorapertura"
    void MostrarLista(string symbol, const vector<LA_nodo> &lista);
    void dfs(unsigned i, vector<bool> &visitado, vector<unsigned> &conexas);
    int GetSmallerCost();
    // Atributos
    unsigned         n;   // Numero de nodos/vertices
    unsigned         m;   // Numero de arcos/aristas
    vector<LA_nodo>  LS;  // Lista de sucesores/adyacencia
    vector<LA_nodo>  LP;  // Lista de predecesores
};
#endif
