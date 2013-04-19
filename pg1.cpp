#include <iostream>
#include <string.h>
#include <vector>

#include "lib/menu.h"
#include "lib/grafo.h"

using namespace std;

typedef void (*tfuncion)(); // Puntero a función que recibe 0 argumentos y no devuelve nada

static Grafo* g;
static Menu<tfuncion> *menu;

// Conjunto de funciones asociadas a cada posible opción del menu
void CargarGrafo();
void InfoGrafo();
void VerSucesores();
void VerPredecesores();
void VerComponentesConexas();

// Recarga los items del menu, en función de si estamos ante un grafo dirigido o no
void RefreshMenu(char fname[]){
    string desc = "Grafo \"";
    desc += fname;
    desc += "\" abierto.";
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
    }
}
// Conjunto de funciones asociadas a cada posible opción del menu
void CargarGrafo(){
    // Carga del fichero
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
void InfoGrafo(){
    if (g != NULL){
        cout << "Información del grafo:" << endl << endl;
        g->Info_Grafo();
    }else{
        cout << "[ERROR] NO hay ningún grafo cargado" << endl;
    }
}
void VerSucesores(){
    if (g != NULL){
        g->dirigido ? cout << "Lista de sucesores del grafo:" : cout << "Lista de adyacencia del grafo:";
        cout << endl << endl;
        g->Mostrar_Listas(0);
    }else{
        cout << "[ERROR] NO hay ningún grafo cargado" << endl;
    }
}
void VerPredecesores(){
    if (g != NULL){
        cout << "Lista de predecesores del grafo:" << endl << endl;
        g->ListaPredecesores();
        g->Mostrar_Listas(1);
    }else{
        cout << "[ERROR] NO hay ningún grafo cargado" << endl;
    }
}
void VerComponentesConexas(){
    if (g != NULL){
        cout << "Componentes conexas del grafo:" << endl << endl;
        g->ComponentesConexas();
    }else{
        cout << "[ERROR] NO hay ningún grafo cargado" << endl;
    }
}
            
        
int main(){
    // TODO: Hacer otro constructor para construir un menu pasándole sólo un item inicial
    vector<const char*> items;
    items.push_back("1 Cargar grafo desde un fichero");
    vector<tfuncion> *funciones = new vector<tfuncion>;
    funciones->push_back(&CargarGrafo);

    string titulo = "OPTIMIZACION 2013 - Practica GRAFOS 1  --  Fernando G L-P";
    string desc = "Ningún grafo abierto.";
    menu = new Menu<tfuncion>(titulo, desc, items, funciones);
    menu->Run();
        
    delete(menu);
    delete(g);
    return(EXIT_SUCCESS);
}
