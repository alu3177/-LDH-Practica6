// Email profesor: salonso@ull.edu.es

#include <vector>

using namespace std;

const unsigned NOERROR = 0;
const unsigned UERROR = 65000;
const int MAXINT = 1000000;

typedef struct{
    unsigned j;  // nodo
    int      c;  // costo
} ElementoLista;

typedef vector<ElementoLista> LA_nodo;

class Grafo{
    unsigned         n;   // Numero de nodos/vertices
    unsigned         m;   // Numero de arcos/aristas
    vector<LA_nodo>  LS;  // Lista de sucesores/adyacencia
    vector<LA_nodo>  LP;  // Lista de predecesores
  public:
    unsigned        dirigido;
    Grafo(char nombrefichero[], int &errorapertura);
    void Actualizar(char nombrefichero[], int &errorapertura);
    void Info_Grafo();
    void Mostrar_Listas(int l);
    void ListaPredecesores();
    void ComponentesConexas();
    void dfs(unsigned i, vector<bool> &visitado);
    ~Grafo() { Clear(); }
  private:
    void Clear();
    int ParseFile(char nombrefichero[]);  // Devuelve el posible "errorapertura"
    void MostrarLista(const vector<LA_nodo> &lista);
};


/*

    Usar un SET de la stl, para la "bolsa"
    // Recorrido

    limpiar marcas
    vacio bolsa

    marcar[1]
    meto_en_bolsa(1)

    Mientras bolsa no vacía{
        e = saco_de_bolsa
        para todo j € adyacente(e) {
            si j no marcado{
                marcar[j]
                meter_en_bolsa(j)
            }
        }
    }

*/


// EL orden de recorrido del WFS (Primero en anchura) es irrelevante
// WFS es como el recorrido de arriba, pero con una cola (FIFO) en vez de bolsa (en la que da igual el orden d añadir nodos del mismo nivel)
// Va "por niveles" de nodos, y cada nivel es el camino dsd el nodo inicial hasta el nodo actual


// IDEM con pila (LIFO) => DFS


// Para calcular componentes conexas:
// Hacer dfs => Si hay nodos sin visitar, Repeat esta linea
