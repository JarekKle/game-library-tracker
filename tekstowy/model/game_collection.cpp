#include "game_collection.h"
GameCollection::GameCollection(int id, const std::string& name) :
    mId(id),
    mName(name),
    pGames({}) 
{};
const std::string& GameCollection::getName(){
    return mName;
}
const int GameCollection::getId() const{
    return mId;
}
void GameCollection::setName(const std::string& name){
    mName = name;
}
bool GameCollection::addGame(const Game* game){
    if (game == nullptr || containsGame(game->getId())){
        return false;
    }
    pGames.push_back(game);
    return true;
}
bool GameCollection::removeGame(int id){
    for(auto it=pGames.begin(); it!=pGames.end(); it++){
        if((*it)->getId() == id){
            pGames.erase(it);
            return true;
        }
    }
    return false;
}
const std::vector<const Game*>& GameCollection::getGames() const{
    return pGames;
}
bool GameCollection::containsGame(int id) const{
    for(const Game* game : pGames){
        if(game != nullptr && game->getId() == id){
            return true;
        }
    }
    return false;
}