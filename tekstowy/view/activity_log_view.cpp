#include "activity_log_view.h"
#include <iostream>
#include <curses.h>
ActivityLogView::ActivityLogView(){

};
void ActivityLogView::displayActivityLogView(){
        clear();
        mvprintw(1, 2, "Activity log view");
        mvprintw(11, 2, "0 - exit");
        refresh();
}

int ActivityLogView::getUserChoice(){
        int key = getch();
    return key - '0';
};