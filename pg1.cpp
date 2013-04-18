#include <iostream>
#include <vector>

#include "lib/menu.h"
#include "lib/grafo.h"

using namespace std;

typedef void (*tfuncion)(); // Puntero a función que recibe 0 argumentos y no devuelve nada

static Grafo* g;
static Menu<tfuncion> *menu;

void CargarGrafo();
void InfoGrafo();
void VerSucesores();
void VerPredecesores();

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
    // Actualización del menu
    // TODO: Borrar "items" antes de volver a meter más
    menu->ClearItems();
    menu->AddItem("2 Mostrar informacion basica del grafo", &InfoGrafo);
    if (g->dirigido == 0){
        menu->AddItem("3 Mostrar lista de adyacencia del grafo", &InfoGrafo);
        menu->AddItem("4 Mostrar componentes conexas del grafo", &InfoGrafo);
    }else if (g->dirigido == 1){
        menu->AddItem("3 Mostrar lista de sucesores del grafo", &VerSucesores);
        menu->AddItem("4 Mostrar lista de predecesores del grafo", &VerPredecesores);
    }
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
        cout << "Lista de sucesores del grafo:" << endl << endl;
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
            
            
int main(){
    
    vector<const char*> items;
    items.push_back("1 Cargar grafo desde un fichero");
    /*
    items.push_back("3 Mostrar lista de sucesores del grafo");
    items.push_back("4 Mostrar lista de predecesores del grafo");
    */
    vector<tfuncion> *funciones = new vector<tfuncion>;
    funciones->push_back(&CargarGrafo);
    /*
    funciones->push_back(&InfoGrafo);
    funciones->push_back(&VerSucesores);
    funciones->push_back(&VerPredecesores);
    */
    char titulo[] = {"OPTIMIZACION 2013 - Practica GRAFOS 1  --  Fernando G L-P"};
    menu = new Menu<tfuncion>(titulo, items, funciones);
    menu->Run();
        
    delete(menu);
    delete(g);
    return(EXIT_SUCCESS);
}
