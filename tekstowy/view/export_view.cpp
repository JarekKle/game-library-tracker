#include "export_view.h"
#include <iostream>
#include <curses.h>
ExportView::ExportView(){

};
void ExportView::displayExportView(){
        clear();
        mvprintw(1, 2, "Export view");
        mvprintw(11, 2, "0 - exit");
        refresh();
};

int ExportView::getUserChoice(){
        int key = getch();
    return key - '0';
};