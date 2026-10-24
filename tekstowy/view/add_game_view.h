#pragma once

#include "form_action.h"
#include "../model/game.h"

#include <optional>
#include <string>


struct AddGameFormData {
    std::string title;
    std::string developer = "Unknown";
    std::string publisher = "Unknown";

    int achievementCount = -1;
    int unlockedAchievements = 0;
    float playtime = 0.0f;
    int personalRating = 0;
    int metacriticRating = 0;

    std::vector<std::string> notes;
    std::vector<GameGenre> genres;

    GameStore store{};
    GamePlatform platform{};
    GameStatus status{};
    GameAvailability availability{};

    bool installed = false;


};

class AddGameView {
public:
    AddGameView() = default;

    void beginForm(bool addToWishlist);
    void drawForm();

    FormAction handleInput();
    void moveSelection(int direction);
    void changeSelectedValue(int direction);
    void editSelectedField();

    const AddGameFormData& getFormData() const;

private:
    AddGameFormData mData;
    bool mAddToWishlist = false;
    int mSelectedField = 0;
    int mFieldCount = 0;
    std::vector<GameGenre> mGenreOptions;
    std::vector<GameStore> mStoreOptions;
    std::vector<GamePlatform> mPlatformOptions;
    std::vector<GameAvailability> mAvailabilityOptions;

    int mGenreCursor = 0;
    bool editText(const char* prompt, std::string& value);
    bool editInteger(const char* prompt, int& value);
    bool editFloat(const char* prompt, float& value);
};