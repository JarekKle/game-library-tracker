#include "game_search_view.h"
#include <iostream>
#include <curses.h>
#include "../api/rawg_game.h"
GameSearchView::GameSearchView(){

};
void GameSearchView::displayGameSearchView(){
        clear();
        mvprintw(1, 2, "Game search view");
        mvprintw(11, 2, "0 - exit");
        refresh();
};

int GameSearchView::getUserChoice(){
        int key = getch();
    return key - '0';
};

void GameSearchView::displayResults(const std::vector<RawgGame>& games) {
        for (const RawgGame& game : games) {
            // Display game details
                mvprintw(3, 2, "Game ID: %d", game.id);
                mvprintw(4, 2, "Title: %s", game.title.c_str());
                mvprintw(5, 2, "Metacritic Rating: %d",
                                game.metacriticRating);
                mvprintw(6, 2, "Developers: %s",
                                game.developers.empty() ? "N/A" : game.developers[0].c_str());
                mvprintw(7, 2, "Publishers: %s",
                                game.publishers.empty() ? "N/A" : game.publishers[0].c_str());
                mvprintw(8, 2, "Genres: %s",
                                game.genres.empty() ? "N/A" : game.genres[0].c_str());
                refresh();
        }
}