#include "import_view.h"
#include <iostream>
#include <curses.h>
ImportView::ImportView(){

};
void ImportView::displayImportView(){
        clear();
        mvprintw(1, 2, "Import view");
        mvprintw(11, 2, "0 - exit");
        refresh();
};

int ImportView::getUserChoice(){
        int key = getch();
    return key - '0';
};