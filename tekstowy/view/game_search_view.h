#pragma once

class GameSearchView{
    public:
        GameSearchView();
        void displayGameSearchView();
        int getUserChoice();
        void displayResults(const std::vector<RawgGame>& games);
};