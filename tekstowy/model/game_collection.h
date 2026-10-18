#pragma once

#include <string>
#include <vector>

#include "game.h"
class GameCollection{
    private:
        int mId;
        std::vector<const Game*> pGames;
        std::string mName;
    public:
        GameCollection(
            int id,
            const std::string& name = "Untitled"
        );
        const std::string& getName();
        const int getId() const;
        void setName(const std::string& name);
        bool addGame(const Game* game);
        bool removeGame(int id);
        const std::vector<const Game*>& getGames() const;
        bool containsGame(int id) const;
};
