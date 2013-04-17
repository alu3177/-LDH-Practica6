#include <cstdlib>
#include <curses.h>
#include <menu.h>
#include <vector>

using namespace std;

class Menu{
    
  public:
    Menu(const ){
    }
  private:
    void ShowMenu(){
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
    }
    // Carga items en my_items
    void LoadItems(){
        my_items = (ITEM **)calloc(items.size() + 1, sizeof(ITEM *));
        for(int i = 0; i < items.size(); i++)
            my_items[i] = new_item(items[i], " ");
        my_items[items.size()] = (ITEM *)NULL;
        my_menu = new_menu((ITEM **)my_items);
    }
    
    MENU*  my_menu;
    ITEM** my_items;
    vector<const char*> items;
};
