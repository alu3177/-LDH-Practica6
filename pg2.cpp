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
 
#include <iostream>
#include <string.h>
#include <vector>

#include "lib/menu.h"
#include "lib/grafo.h"

using namespace std;

typedef void (*tfuncion)(); // Puntero a función que recibe 0 argumentos y no devuelve nada

static Grafo* g;
static Menu<tfuncion> *menu;

void RefreshMenu(string fname); // Recarga los items del menu, en función de si estamos ante un grafo dirigido o no

////////////////////////////////////////////////////////////////////
// Conjunto de funciones asociadas a cada posible opción del menu //
////////////////////////////////////////////////////////////////////
void CargarGrafo(){ // Carga del fichero
    char fname[32];
    int openstatus;
    openstatus = 10;
    while (openstatus != NOERROR){
        system("clear");
        if (openstatus == UERROR)
            cout << "Error al abrir el fichero \"" << fname << "\"" << endl;
        cout << "Ruta del fichero de entrada: ";
        cin >> fname;
        delete(g);
        g = new Grafo(fname, openstatus);
    }
    RefreshMenu(fname);
}
void InfoGrafo(){  // Información sobre el grafo
    if (g != NULL){
        cout << "Información del grafo:" << endl << endl;
        g->Info_Grafo();
    }else{
        cout << "[ERROR] NO hay ningún grafo cargado" << endl;
    }
}
void VerSucesores(){  // Lista de sucesores
    if (g != NULL){
        g->dirigido ? cout << "Lista de sucesores del grafo:" : cout << "Lista de adyacencia del grafo:";
        cout << endl << endl;
        g->Mostrar_Listas(0);
    }else{
        cout << "[ERROR] NO hay ningún grafo cargado" << endl;
    }
}
void VerPredecesores(){  // Lista de predecesores
    if (g != NULL){
        cout << "Lista de predecesores del grafo:" << endl << endl;
        g->ListaPredecesores();
        g->Mostrar_Listas(1);
    }else{
        cout << "[ERROR] NO hay ningún grafo cargado" << endl;
    }
}
void VerComponentesConexas(){  // Componentes conexas
    if (g != NULL){
        cout << "Componentes conexas del grafo:" << endl << endl;
        g->ComponentesConexas();
    }else{
        cout << "[ERROR] NO hay ningún grafo cargado" << endl;
    }
}

void VerDijkstra(){  // Dijkstra
    if (g != NULL){
        g->Dijkstra();
    }else{
        cout << "[ERROR] NO hay ningún grafo cargado" << endl;
    }
}

void VerBellmanFordMoore(){  // Bellman-Ford-Moore
    if (g != NULL){
        g->BellmanFordMoore();
    }else{
        cout << "[ERROR] NO hay ningún grafo cargado" << endl;
    }
}

// Recarga los items del menu, en función de si estamos ante un grafo dirigido o no
void RefreshMenu(string fname){
    string desc = "Grafo \"" + fname + "\" abierto.";
    menu->SetDescripcion(desc);
    menu->ClearItems();
    menu->AddItem("1 Cargar grafo desde un fichero", &CargarGrafo);
    menu->AddItem("2 Mostrar informacion basica del grafo", &InfoGrafo);
    if (g->dirigido == 0){
        menu->AddItem("3 Mostrar lista de adyacencia del grafo", &VerSucesores);
        menu->AddItem("4 Mostrar componentes conexas del grafo", &VerComponentesConexas);
    }else if (g->dirigido == 1){
        menu->AddItem("3 Mostrar lista de sucesores del grafo", &VerSucesores);
        menu->AddItem("4 Mostrar lista de predecesores del grafo", &VerPredecesores);
        menu->AddItem("5 Ejecutar algoritmo de Dijkstra", &VerDijkstra);
        menu->AddItem("6 Ejecutar algoritmo de Bellman-Ford-Moore", &VerBellmanFordMoore);
    }
}
        
int main(){
    
    menu = new Menu<tfuncion>("OPTIMIZACION 2013 - Practica GRAFOS 2  --  Fernando G L-P", "Ningún grafo abierto.");
    
    menu->AddItem("1 Cargar grafo desde un fichero", &CargarGrafo);
    menu->Run();
    
    delete(menu);
    delete(g);
    return(EXIT_SUCCESS);
}
