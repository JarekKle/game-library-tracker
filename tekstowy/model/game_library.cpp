#include "game_library.h"
#include <algorithm>
#include <iterator>
GameLibrary::GameLibrary(const std::vector<Game> & games) :
    mGameLibrary(games),
    mGameCollections({})
{};

void GameLibrary::addGame(const Game& game){
    if (findGameById(game.getId()) != nullptr){
        return;
    }
    mGameLibrary.push_back(game);
}
bool GameLibrary::removeGame(int id){
    for (auto game = mGameLibrary.begin(); game != mGameLibrary.end() ; game++){
        if (game->getId() == id){
            mGameLibrary.erase(game);
            return true;
        }
    }
    return false;
}
Game* GameLibrary::findGameById(int id){
    for(Game& game : mGameLibrary){
        if (game.getId() == id){
            return &game;
        }
    }
    return nullptr;
}
const Game* GameLibrary::findGameById(int id) const{
    for(const Game& game : mGameLibrary){
        if (game.getId() == id){
            return &game;
        }
    }
    return nullptr;
}
const std::vector<Game>& GameLibrary::getGames() const{
    return mGameLibrary;
}
    std::vector<Game> GameLibrary::getLibraryGames() const{
            std::vector<Game> result;

    for (const Game& game : mGameLibrary) {
        if (game.getAvailability() != GameAvailability::WISHLISTED) {
            result.push_back(game);
        }
    }

    return result;
    }
    std::vector<Game> GameLibrary::getWishlistedGames() const{
        std::vector<Game> result;

    for (const Game& game : mGameLibrary) {
        if (game.getAvailability() == GameAvailability::WISHLISTED) {
            result.push_back(game);
        }
    }

    return result;
    }
std::size_t GameLibrary::getGameCount() const {
    return mGameLibrary.size();
}
void GameLibrary::addCollection(const std::string& name){
    int new_id = 0;
    for(const GameCollection& gc : mGameCollections){
        if( gc.getId() > new_id){
            new_id = gc.getId();
        }

    }
    new_id++;
    mGameCollections.emplace_back(new_id, name);
}


std::vector<Game> GameLibrary::getSortedGames(
    GameSortCriteria criteria,
    SortOrder order
) const {
    std::vector<Game> sortedGames = mGameLibrary;

    std::stable_sort(
        sortedGames.begin(),
        sortedGames.end(),
        [criteria, order](const Game& a, const Game& b) {
            switch (criteria) {
                case GameSortCriteria::Title:
                    return order == SortOrder::ASCENDING
                        ? a.getTitle() < b.getTitle()
                        : a.getTitle() > b.getTitle();

                case GameSortCriteria::Playtime:
                    return order == SortOrder::ASCENDING
                        ? a.getPlaytime() < b.getPlaytime()
                        : a.getPlaytime() > b.getPlaytime();

                case GameSortCriteria::PersonalRating:
                    return order == SortOrder::ASCENDING
                        ? a.getPersonalRating() < b.getPersonalRating()
                        : a.getPersonalRating() > b.getPersonalRating();

                case GameSortCriteria::MetacriticRating:
                    return order == SortOrder::ASCENDING
                        ? a.getMetacriticRating() < b.getMetacriticRating()
                        : a.getMetacriticRating() > b.getMetacriticRating();
                case GameSortCriteria::CompletionPercent:
                    return order == SortOrder::ASCENDING
                        ? a.getCompletionPercentage() < b.getCompletionPercentage()
                        : a.getCompletionPercentage() > b.getCompletionPercentage();
            }

            return false;
        }
    );

    return sortedGames;
}
std::vector<Game> GameLibrary::getFilteredGames(
    const GameFilter& filter
) const {
    std::vector<Game> result;

    std::copy_if(
        mGameLibrary.begin(),
        mGameLibrary.end(),
        std::back_inserter(result),
        [&filter](const Game& game) {
            if (filter.status.has_value() &&
                game.getStatus() != *filter.status) {
                return false;
            }

            if (filter.platform.has_value() &&
                game.getPlatform() != *filter.platform) {
                return false;
            }

            if (filter.minPlaytime.has_value() &&
                game.getPlaytime() < *filter.minPlaytime) {
                return false;
            }

            if (filter.minPersonalRating.has_value() &&
                game.getPersonalRating() < *filter.minPersonalRating) {
                return false;
            }

            return true;
        }
    );

    return result;
}
int GameLibrary::getNextId() const {
    int maxId = 0;
    for (const Game& game : mGameLibrary) {
        if (game.getId() > maxId) {
            maxId = game.getId();
        }
    }
    return maxId + 1;
}