#include <cstdlib>
#include <curses.h>
#include <menu.h>

using namespace std;

template <typename T>
class Menu{
    
  public:
    // Constructor paramétrico
    Menu(string title, string desc, const vector<const char*> &elems, vector<T>* &funcs){
        titulo = title;
        descripcion = desc;
        items = elems;
        LoadItems();
        funciones = funcs;
    }
    ~Menu(){
        UnloadItems();
        Close();
        delete(my_menu);
        delete(my_items);
        items.clear();
    }
    // Borra el contenido de los vectores 'items' y 'funciones'
    void ClearItems(){
        items.clear();
        funciones->clear();
    }
    // Añade un elemento y su función asociada a los vectores 'items' y 'funciones'
    void AddItem(const char item[], T funcion){
        UnloadItems();
        items.push_back(item);
        funciones->push_back(funcion);
        LoadItems();
    }
    // Establece el campo 'descripcion'
    void SetDescripcion(string desc){
        descripcion.clear();
        descripcion = desc;
    }
    void Run(){
        unsigned key;
        
        Show();
        while((key = getch()) != KEY_F(4)){
            switch(key){
                // Movimiento por el menu
                case KEY_DOWN:
                    menu_driver(my_menu, REQ_DOWN_ITEM);
                    break;
                case KEY_UP:
                    menu_driver(my_menu, REQ_UP_ITEM);
                    break;
                default:
                    MoveCursor(key);
                    break;

                // Llamadas a las funciones asociadas a cada item
                case '\n':
                    Close();
                    funciones->at(item_index(current_item(my_menu)))();  // Ejecutamos la funcion asociada al item actual
                    Pausa();
                    Show();
                    break;
            }
        }
        Close();
    }
    
  private:
    // Carga 'items' en 'my_items'
    void LoadItems(){
        my_items = (ITEM **)calloc(items.size() + 1, sizeof(ITEM *));
        for(int i = 0; i < items.size(); i++)
            my_items[i] = new_item(items[i], " ");
        my_items[items.size()] = (ITEM *)NULL;
        my_menu = new_menu((ITEM **)my_items);
    }
    // Vacía el contenido de 'my_items'
    void UnloadItems(){
        for (unsigned i = 0; i < items.size(); i++)
            free_item(my_items[i]);
        free_menu(my_menu);
    }
    void MoveCursor(char c){
        menu_driver(my_menu, c);
        menu_driver(my_menu, REQ_CLEAR_PATTERN);
    }
    void Show(){
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        char blankLine[] = {"                                                     "};
        mvprintw(LINES - 6, 0, blankLine); // Borrar anterior descripción
        mvprintw(LINES - 6, 0, (char *)descripcion.c_str());
        mvprintw(LINES - 4, 0, (char *)titulo.c_str());
        mvprintw(LINES - 2, 0, "F4 para salir");
        post_menu(my_menu);
        refresh();
    }
    void Close(){
        endwin();
        system("clear");
    }
    void Pausa(){
        int c;
        cout << endl << "Pulse enter para continuar..." << endl;
        fflush(stdout);
        do c = getchar(); while((c != '\n') && (c != EOF));

    }
    
    
    MENU*  my_menu;
    ITEM** my_items;
    vector<const char*> items;
    vector<T>* funciones;
    string descripcion;
    string titulo;
};
