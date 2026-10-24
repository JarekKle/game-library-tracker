#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "game_platform.h"
#include "game_store.h"
#include "game_genre.h"
#include "game_status.h"
#include "game_availability.h"

class Game
{
private:
    int id;
    std::string mTitle;
    std::string mDeveloper;
    std::string mPublisher;
    int mAchievementCount;
    int mUnlockedAchievements;
    float mPlaytime;
    int mPersonalRating;
    int mMetacriticRating;
    std::vector<std::string> mNotes;
    std::vector<GameGenre> mGenres;
    GameStore mStore;
    GamePlatform mPlatform;
    GameStatus mStatus;
    GameAvailability mAvailability;
    bool mInstalled;

public:
    Game(
        int id,
        const std::string& title,
        const std::string& developer = "Unknown",
        const std::string& publisher = "Unknown",
        int achievementCount = -1,
        int unlockedAchievements = 0,
        float playtime = 0.0f,
        int personalRating = 0,
        int metacriticRating = 0,
        const std::vector<std::string>& notes = {},
        const std::vector<GameGenre>& genres = {},
        GameStore game_store = STEAM,
        GamePlatform game_platform = PC,
        GameStatus game_status = COMPLETED,
        GameAvailability game_availability = BOUGHT,
        bool installed = true
    );
    Game(
        int id,
        const std::string& title,
        const std::string& developer = "Unknown",
        const std::string& publisher = "Unknown",
        int achievementCount = -1,
        int metacriticRating = 0,
        const std::vector<GameGenre>& genres = {},
        GameStore game_store = STEAM,
        GamePlatform game_platform = PC,
        GameStatus game_status = PLAN_TO_PLAY,
        GameAvailability game_availability = WISHLISTED
    );
    int getId() const;
    std::string getTitle() const;
    std::string getDeveloper() const;
    std::string getPublisher() const;

    int getAchievementCount() const;
    int getUnlockedAchievements() const;

    float getPlaytime() const;
    int getPersonalRating() const;
    int getMetacriticRating() const;

    std::vector<std::string> getNotes() const;
    std::vector<GameGenre> getGenres() const;

    GameStore getStore() const;
    GamePlatform getPlatform() const;
    GameStatus getStatus() const;
    GameAvailability getAvailability() const;
    bool getInstalled() const;
    int getCompletionPercentage() const;

    void setTitle(const std::string& title);
    void setDeveloper(const std::string& developer);
    void setPublisher(const std::string& publisher);
    void setAchievementCount(int count);
    void setUnlockedAchievements(int unlockedAchievements);
    void setPlaytime(float playtime);
    void setPersonalRating(int rating);
    void setMetacriticRating(int rating);
    void setNotes(const std::vector<std::string>& notes);
    void setGenres(const std::vector<GameGenre>& genres);
    void setStore(GameStore store);
    void setPlatform(GamePlatform platform);
    void setStatus(GameStatus status);
    void setAvailability(GameAvailability availability);
    void setInstalled(bool installed);
    void addNote(const std::string& note);
    void removeNote(const std::string& note);
    void addGenre(GameGenre genre);
    void removeGenre(GameGenre genre);
};