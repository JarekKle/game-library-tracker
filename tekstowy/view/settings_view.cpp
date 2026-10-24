#include "settings_view.h"
#include <iostream>
#include <curses.h>
SettingsView::SettingsView(){

};
void SettingsView::displaySettingsView(){
        clear();
        mvprintw(1, 2, "Settings view");
        mvprintw(11, 2, "0 - exit");
        refresh();
};

int SettingsView::getUserChoice(){
        int key = getch();
    return key - '0';
};