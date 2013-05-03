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

class Grafo{
  public:
    unsigned        dirigido;
    Grafo(char nombrefichero[], int &errorapertura);
    void Actualizar(char nombrefichero[], int &errorapertura);
    void Info_Grafo();
    void Mostrar_Listas(int l);
    void ListaPredecesores();
    void ComponentesConexas();
    ~Grafo() { Clear(); }
  private:
    void Clear();
    int ParseFile(char nombrefichero[]);  // Devuelve el posible "errorapertura"
    void MostrarLista(string symbol, const vector<LA_nodo> &lista);
    void dfs(unsigned i, vector<bool> &visitado, vector<unsigned> &conexas);
    // Atributos
    unsigned         n;   // Numero de nodos/vertices
    unsigned         m;   // Numero de arcos/aristas
    vector<LA_nodo>  LS;  // Lista de sucesores/adyacencia
    vector<LA_nodo>  LP;  // Lista de predecesores
};
#endif
