#include <iostream>
#include "lib/grafo.h"

int main(){
    int openstatus = 0;
    Grafo* graf = new Grafo("grafos/grafo1.gr", openstatus);
    if (openstatus == 0){
        graf->ListaPredecesores();
        graf->Info_Grafo();
        graf->Mostrar_Listas(0);
    
        vector<bool> vis;
        vis.resize(9);
        graf->dfs(0, vis);
        cout << endl;
    }
    
    delete(graf);
    return 0;
}

