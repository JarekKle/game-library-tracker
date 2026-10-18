#include "game.h"

Game::Game(
    int id,
    const std::string& title,
    const std::string& developer,
    const std::string& publisher,
    int achievementCount,
    int unlockedAchievements,
    float playtime,
    int personalRating,
    int metacriticRating,
    const std::vector<std::string>& notes,
    const std::vector<GameGenre>& genres,
    GameStore game_store,
    GamePlatform game_platform,
    GameStatus game_status,
    GameAvailability game_availability,
    bool installed
)
    : id(id),
      mTitle(title),
      mDeveloper(developer),
      mPublisher(publisher),
      mAchievementCount(achievementCount),
      mUnlockedAchievements(unlockedAchievements),
      mPlaytime(playtime),
      mPersonalRating(personalRating),
      mMetacriticRating(metacriticRating),
      mNotes(notes),
      mGenres(genres),
      mStore(game_store),
      mPlatform(game_platform),
      mStatus(game_status),
      mAvailability(game_availability),
      mInstalled(installed)
{
}

int Game::getId() const {
    return id;
}

std::string Game::getTitle() const {
    return mTitle;
}

std::string Game::getDeveloper() const {
    return mDeveloper;
}

std::string Game::getPublisher() const {
    return mPublisher;
}

int Game::getAchievementCount() const {
    return mAchievementCount;
}

int Game::getUnlockedAchievements() const {
    return mUnlockedAchievements;
}

float Game::getPlaytime() const {
    return mPlaytime;
}

int Game::getPersonalRating() const {
    return mPersonalRating;
}

int Game::getMetacriticRating() const {
    return mMetacriticRating;
}
bool Game::getInstalled() const {
    return mInstalled;
}

std::vector<std::string> Game::getNotes() const {
    return mNotes;
}

std::vector<GameGenre> Game::getGenres() const {
    return mGenres;
}

GameStore Game::getStore() const {
    return mStore;
}

GamePlatform Game::getPlatform() const {
    return mPlatform;
}

GameStatus Game::getStatus() const {
    return mStatus;
}

GameAvailability Game::getAvailability() const {
    return mAvailability;
}

int Game::getCompletionPercentage() const {
    if (mAchievementCount <= 0) {
        return 0;
    }

    return static_cast<int>(
        static_cast<float>(mUnlockedAchievements)
        / mAchievementCount * 100
    );
}

void Game::setTitle(const std::string& title) {
    mTitle = title;
}
void Game::setDeveloper(const std::string& developer) {
    mDeveloper = developer;
}
void Game::setPublisher(const std::string& publisher) {
    mPublisher = publisher;
}
void Game::setAchievementCount(int count) {
    if (count >= -1) {
        mAchievementCount = count;
    }
}
void Game::setUnlockedAchievements(int unlockedAchievements) {
    if (unlockedAchievements >= 0 && unlockedAchievements <= mAchievementCount) {
        mUnlockedAchievements = unlockedAchievements;
    }
}
void Game::setPlaytime(float playtime) {
    if (playtime >= 0.0f) {
        mPlaytime = playtime;
    }
}
void Game::setPersonalRating(int rating) {
    if (rating >= 1 && rating <= 100) {
        mPersonalRating = rating;
    }
}

void Game::setMetacriticRating(int rating) {
    if (rating >= 0 && rating <= 100) {
        mMetacriticRating = rating;
    }
}
void Game::setNotes(const std::vector<std::string>& notes) {
    mNotes = notes;
}
void Game::setGenres(const std::vector<GameGenre>& genres) {
    mGenres = genres;
}
void Game::setStore(GameStore store) {
    mStore = store;
}
void Game::setPlatform(GamePlatform platform) {
    mPlatform = platform;
}
void Game::setStatus(GameStatus status) {
    mStatus = status;
}
void Game::setAvailability(GameAvailability availability) {
    mAvailability = availability;
}
void Game::setInstalled(bool installed) {
    mInstalled = installed;
}
void Game::addNote(const std::string& note) {
    mNotes.push_back(note);
}
void Game::removeNote(const std::string& note) {
    auto it = std::find(mNotes.begin(), mNotes.end(), note);
    if (it != mNotes.end()) {
        mNotes.erase(it);
    }
}
void Game::addGenre(GameGenre genre) {
    if (std::find(mGenres.begin(), mGenres.end(), genre) == mGenres.end()) {
        mGenres.push_back(genre);
    }
}
void Game::removeGenre(GameGenre genre) {
    auto it = std::find(mGenres.begin(), mGenres.end(), genre);
    if (it != mGenres.end()) {
        mGenres.erase(it);
    }
}