/*
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
*/

#include <cstdlib>
#include <curses.h>
#include <menu.h>

#include <iostream>
#include <vector>

#include "lib/grafo.h"

using namespace std;

const unsigned N_ITEMS = 5;  // Número de items en el menú

void LoadMenu(MENU* &my_menu, ITEM** &my_items){
    vector<const char*> items;
    items.push_back("OPTIMIZACION 2013 - Practica GRAFOS 1  ||  Fernando G L-P");
    items.push_back("1 Cargar grafo desde un fichero");
    items.push_back("2 Mostrar informacion basica del grafo");
    items.push_back("3 Mostrar lista de sucesores del grafo");
    items.push_back("4 Mostrar lista de predecesores del grafo");
    
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	
	my_items = (ITEM **)calloc(items.size() + 1, sizeof(ITEM *));
	for(int i = 0; i < items.size(); i++)
        my_items[i] = new_item(items[i], " ");
	my_items[items.size()] = (ITEM *)NULL;
	my_menu = new_menu((ITEM **)my_items);
    mvprintw(LINES - 2, 0, "F4 para salir");
	post_menu(my_menu);
	refresh();
}

void CloseMenu(MENU* &my_menu, ITEM** &my_items){
    for (unsigned i = 0; i < N_ITEMS; i++)
        free_item(my_items[i]);
    free_menu(my_menu);
    endwin();
    system("clear");
}

void MoveCursor(MENU* &my_menu, char c){
    menu_driver(my_menu, c);
    menu_driver(my_menu, REQ_CLEAR_PATTERN);
}

void Pausa(){
    cout << "Pulse enter para continuar..." << endl;
    cin.ignore().get();
}
     
void Menu(Grafo* &g){   
    ITEM **my_items;			
	MENU *my_menu;
    unsigned c;
	
    LoadMenu(my_menu, my_items);
	while((c = getch()) != KEY_F(4)){
        switch(c){
            case KEY_DOWN:
		        menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
                
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
            
            case '1':
                MoveCursor(my_menu, c);
                break;
                
            case '2':
                MoveCursor(my_menu, c);
                break;
                
            case '3':
                MoveCursor(my_menu, c);
                break;
                
            case '4':
                MoveCursor(my_menu, c);
                break;
                
            case '\n': // Enter en un elemento
                //char* index = new char[2];  // DEBUG
                //sprintf(index, "%d", item_index(current_item(my_menu))); // Convertimos a char // DEBUG
                //mvprintw(LINES - 3, 0, index);  // DEBUG
                switch (item_index(current_item(my_menu))){
                    case 1:  // Cargar fichero
                        CloseMenu(my_menu, my_items);
                        char fname[32];
                        int openstatus;
                        openstatus = 10;
                        while (openstatus != NOERROR){
                            if (openstatus == UERROR)
                                cout << "Error al abrir el fichero " << fname << endl;
                            cout << "Ruta del fichero de entrada: ";
                            cin >> fname;
                            delete(g);
                            g = new Grafo(fname, openstatus);
                            system("clear");
                        }
                        LoadMenu(my_menu, my_items);
                        break;
                        
                    case 2:  // Mostrar información del grafo
                        CloseMenu(my_menu, my_items);
                        g->Info_Grafo();
                        Pausa();
                        LoadMenu(my_menu, my_items);
                        break;
                        
                    case 3:  // Mostrar lista de sucesores
                        CloseMenu(my_menu, my_items);
                        g->Mostrar_Listas(0);
                        Pausa();
                        LoadMenu(my_menu, my_items);
                        break;
                        
                    case 4:  // Mostar lista de predecesores
                        break;
                }
                break;
		}
	}
    CloseMenu(my_menu, my_items);
}
                
int main(){
    int openstatus = NOERROR;
    Grafo* g = new Grafo("grafos/grafo1.gr", openstatus);
    g->ListaPredecesores(); // Sólo si es dirigido
    system("clear");
    Menu(g);
    delete(g);
    
    return(EXIT_SUCCESS);
}
