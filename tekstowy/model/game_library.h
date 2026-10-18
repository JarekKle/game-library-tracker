#pragma once

#include <string>
#include <vector>

#include "game.h"
#include "game_collection.h"
#include "game_sort_criteria.h"
#include "game_filter.h"

class GameLibrary
{
private:
    std::vector<Game> mGameLibrary;
    std::vector<GameCollection> mGameCollections;

public:
    GameLibrary(
        const std::vector<Game> &games = {});
    void addGame(const Game &game);
    bool removeGame(int id);
    Game *findGameById(int id);
    const Game *findGameById(int id) const;
    const std::vector<Game> &getGames() const;
    std::size_t getGameCount() const;
    void GameLibrary::addCollection(const std::string &name);
    std::vector<Game> getSortedGames(
        GameSortCriteria criteria,
        SortOrder order = SortOrder::ASCENDING) const;
    std::vector<Game> getFilteredGames(
        const GameFilter &filter) const;
};