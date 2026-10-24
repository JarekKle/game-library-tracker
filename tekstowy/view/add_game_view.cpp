#include "add_game_view.h"
#include <algorithm>
#include <curses.h>
#include <algorithm>
#include <cstdlib>
#include <string>
#include "form_action.h"
#include <cmath>    // std::isfinite
#include <limits>   // std::numeric_limits
#include <cerrno>   // errno
#include <cstdlib>  // std::strtof, std::strtol
#include <cstdio>   // snprintf



template <typename T>
void cycleOption(T& value,
                 const std::vector<T>& options,
                 int direction)
{
    if (options.empty()) {
        return;
    }

    auto it = std::find(options.begin(), options.end(), value);

    int index = (it == options.end())
        ? 0
        : static_cast<int>(it - options.begin());

    const int count = static_cast<int>(options.size());
    index = (index + direction + count) % count;

    value = options[index];
}

// Dołącz tutaj nagłówek zawierający mapy tłumaczeń.
// #include "../model/game_translations.h"

bool AddGameView::editText(
    const char* prompt,
    std::string& value
) {
    char buffer[256] = {};

    std::copy_n(
        value.begin(),
        std::min(value.size(), sizeof(buffer) - 1),
        buffer
    );

    echo();
    curs_set(1);

    mvhline(LINES - 3, 0, ' ', COLS);
    mvprintw(LINES - 3, 2, "%s", prompt);
    mvgetnstr(LINES - 3, 2, buffer, sizeof(buffer) - 1);

    noecho();
    curs_set(0);

    value = buffer;
    return true;
}


void AddGameView::drawForm() {
    clear();

    mvprintw(
        1, 2,
        mAddToWishlist
            ? "=== DODAJ GRE DO LISTY ZYCZEN ==="
            : "=== DODAJ GRE DO BIBLIOTEKI ==="
    );

    int row = 3;

    // Rysuje pojedyncze pole formularza.
    auto drawField = [&](int field, const char* label,
                         const std::string& value) {
        if (field == mSelectedField) {
            attron(A_REVERSE);
        }

        mvprintw(row, 2, "%-25s %s",
                 label, value.c_str());

        if (field == mSelectedField) {
            attroff(A_REVERSE);
        }

        ++row;
    };

    // Pola wspólne dla biblioteki i listy życzeń.
    drawField(0, "Tytul:", mData.title);
    drawField(1, "Deweloper:", mData.developer);
    drawField(2, "Wydawca:", mData.publisher);

    // Pola dostępne tylko podczas dodawania do biblioteki.
    if (!mAddToWishlist) {
        drawField(
            3, "Osiagniecia (max):",
            std::to_string(mData.achievementCount)
        );

        drawField(
            4, "Odblokowane:",
            std::to_string(mData.unlockedAchievements)
        );

    char playtimeText[32];
    snprintf(playtimeText, sizeof(playtimeText), "%.1f",
            mData.playtime);

    drawField(5, "Czas gry (godziny):", playtimeText);

        drawField(
            6, "Ocena osobista:",
            std::to_string(mData.personalRating)
        );

        drawField(
            7, "Ocena Metacritic:",
            std::to_string(mData.metacriticRating)
        );

        drawField(
            8, "Zainstalowana:",
            mData.installed ? "Tak" : "Nie"
        );
        std::string selectedGenres;

        for (GameGenre genre : mData.genres) {
            if (!selectedGenres.empty()) {
                selectedGenres += ", ";
            }

            selectedGenres += genreTranslationMap.at(genre);
        }

        if (selectedGenres.empty()) {
            selectedGenres = "(brak)";
        }

        drawField(9, "Gatunki:", selectedGenres);

        drawField(
            10, "Sklep:",
            storeTranslationMap.at(mData.store)
        );

        drawField(
            11, "Platforma:",
            platformTranslationMap.at(mData.platform)
        );

        drawField(
            12, "Dostepnosc:",
            availabilityTranslationMap.at(mData.availability)
        );
    }

    // Indeksy przycisków muszą zgadzać się z mFieldCount
    // oraz warunkami w handleInput().
    const int saveIndex = mAddToWishlist ? 3 : 13;
    const int cancelIndex = saveIndex + 1;

    row++;

    if (mSelectedField == saveIndex) {
        attron(A_REVERSE);
    }

    mvprintw(row++, 2, "[ Zapisz ]");

    if (mSelectedField == saveIndex) {
        attroff(A_REVERSE);
    }

    if (mSelectedField == cancelIndex) {
        attron(A_REVERSE);
    }

    mvprintw(row, 2, "[ Anuluj ]");

    if (mSelectedField == cancelIndex) {
        attroff(A_REVERSE);
    }

    mvprintw(
        LINES - 2, 2,
        "Strzalki: nawigacja | Enter: edycja/zapis | Esc: anuluj"
    );

    refresh();
}

FormAction AddGameView::handleInput()
{
    int key = getch();

    switch (key) {
        case KEY_UP:
            return FormAction::MOVE_UP;

        case KEY_DOWN:
            return FormAction::MOVE_DOWN;

        case KEY_LEFT:
            return FormAction::MOVE_LEFT;

        case KEY_RIGHT:
            return FormAction::MOVE_RIGHT;

        case '\n':
        case '\r':
        case KEY_ENTER:
            if (mSelectedField == mFieldCount - 2)
                return FormAction::SAVE;

            if (mSelectedField == mFieldCount - 1)
                return FormAction::CANCEL;

            return FormAction::EDIT;

        case 27:
            return FormAction::CANCEL;

        default:
            return FormAction::NONE;
    }
}
void AddGameView::beginForm(bool addToWishlist)
{
    mData = AddGameFormData{};
    mAddToWishlist = addToWishlist;
    mSelectedField = 0;
    mGenreOptions = {
        GameGenre::ACTION,
        GameGenre::INDIE,
        GameGenre::ADVENTURE,
        GameGenre::RPG,
        GameGenre::STRATEGY,
        GameGenre::SHOOTER,
        GameGenre::CASUAL,
        GameGenre::SIMULATION,
        GameGenre::PUZZLE,
        GameGenre::ARCADE,
        GameGenre::PLATFORMER,
        GameGenre::MASSIVELY_MULTIPLAYER,
        GameGenre::RACING,
        GameGenre::SPORTS,
        GameGenre::FIGHTING,
        GameGenre::FAMILY,
        GameGenre::BOARD_GAME,
        GameGenre::CARD,
        GameGenre::EDUCATIONAL
    };
    mStoreOptions = {
        GameStore::STEAM,
        GameStore::PLAYSTATION_STORE,
        GameStore::XBOX_STORE,
        GameStore::APP_STORE,
        GameStore::EPIC_GAMES,
        GameStore::GOG,
        GameStore::UBISOFT,
        GameStore::NINTENDO_SWITCH_STORE,
        GameStore::MICROSOFT_STORE,
        GameStore::GOOGLE_PLAY,
        GameStore::OTHER_STORE
    };
    mPlatformOptions = {
        GamePlatform::PC,
        GamePlatform::PLAYSTATION_5,
        GamePlatform::PLAYSTATION_4,
        GamePlatform::XBOX_ONE,
        GamePlatform::XBOX_SERIES_S_X,
        GamePlatform::NINTENDO_SWITCH,
        GamePlatform::IOS,
        GamePlatform::ANDROID,
        GamePlatform::NINTENDO_3DS,
        GamePlatform::NINTENDO_DS,
        GamePlatform::NINTENDO_DSI,
        GamePlatform::MACOS,
        GamePlatform::LINUX,
        GamePlatform::XBOX_360,
        GamePlatform::XBOX,
        GamePlatform::PLAYSTATION_3,
        GamePlatform::PLAYSTATION_2,
        GamePlatform::PLAYSTATION,
        GamePlatform::PS_VITA,
        GamePlatform::PSP,
        GamePlatform::WII_U,
        GamePlatform::WII,
        GamePlatform::GAMECUBE,
        GamePlatform::NINTENDO_64,
        GamePlatform::GAME_BOY_ADVANCE,
        GamePlatform::GAME_BOY_COLOR,
        GamePlatform::GAME_BOY,
        GamePlatform::SNES,
        GamePlatform::NES,
        GamePlatform::CLASSIC_MACINTOSH,
        GamePlatform::APPLE_II,
        GamePlatform::COMMODORE_AMIGA,
        GamePlatform::ATARI_7800,
        GamePlatform::ATARI_5200,
        GamePlatform::ATARI_2600,
        GamePlatform::ATARI_FLASHBACK,
        GamePlatform::ATARI_8BIT,
        GamePlatform::ATARI_ST,
        GamePlatform::ATARI_LYNX,
        GamePlatform::ATARI_XEGS,
        GamePlatform::GENESIS,
        GamePlatform::SEGA_SATURN,
        GamePlatform::SEGA_CD,
        GamePlatform::SEGA_32X,
        GamePlatform::SEGA_MASTER_SYSTEM,
        GamePlatform::DREAMCAST,
        GamePlatform::THREEDO,
        GamePlatform::JAGUAR,
        GamePlatform::GAME_GEAR,
        GamePlatform::NEO_GEO,
        GamePlatform::WEB
    };
    mAvailabilityOptions = {
        GameAvailability::BOUGHT,
        GameAvailability::BORROWED,
        GameAvailability::PLATFORM_FAMILY,
        GameAvailability::GAME_PASS,
    };
    mData.availability = addToWishlist ? GameAvailability::WISHLISTED : GameAvailability::BOUGHT;
    // 3 pola tekstowe + opcjonalne pola biblioteki + Zapisz + Anuluj.
    mFieldCount = addToWishlist ? 5 : 15;
}

void AddGameView::moveSelection(int direction)
{
    if (mFieldCount <= 0)
        return;

    mSelectedField =
        (mSelectedField + direction + mFieldCount) % mFieldCount;
}

void AddGameView::changeSelectedValue(int direction)
{
    // Tutaj zmieniaj wartości enumów i pól typu bool.
    // Nie zmieniaj tekstu — ten edytuje editSelectedField().
    // Implementacja zależy od kolejności enumów w Twoim projekcie.
        switch (mSelectedField) {
    case 9:
        if (!mGenreOptions.empty()) {
            const int count =
                static_cast<int>(mGenreOptions.size());

            mGenreCursor =
                (mGenreCursor + direction + count) % count;
        }
        break;  
        case 10:
            cycleOption(mData.store, mStoreOptions, direction);
            break;

        case 11:
            cycleOption(mData.platform, mPlatformOptions, direction);
            break;

        case 12:
            cycleOption(
                mData.availability,
                mAvailabilityOptions,
                direction
            );
            break;
        };
}

void AddGameView::editSelectedField()
{
    switch (mSelectedField) {
        case 0:
            editText("Tytul:", mData.title);
            break;

        case 1:
            editText("Deweloper:", mData.developer);
            break;

        case 2:
            editText("Wydawca:", mData.publisher);
            break;

        case 3:
            editInteger(
                "Liczba osiagniec:",
                mData.achievementCount
            );
            break;

        case 4:
            editInteger(
                "Odblokowane osiagniecia:",
                mData.unlockedAchievements
            );
            break;

        case 5:
            editFloat(
                "Czas gry (godziny):",
                mData.playtime
            );
            break;

        case 6:
            editInteger(
                "Ocena osobista (1-100):",
                mData.personalRating
            );
            break;

        case 7:
            editInteger(
                "Ocena Metacritic (0-100):",
                mData.metacriticRating
            );
            break;

        case 8:
            mData.installed = !mData.installed;
            break;

        case 9: {
            if (mGenreOptions.empty()) {
                break;
            }

            const GameGenre genre =
                mGenreOptions[mGenreCursor];

            auto it = std::find(
                mData.genres.begin(),
                mData.genres.end(),
                genre
            );

            if (it == mData.genres.end()) {
                mData.genres.push_back(genre);
            } else {
                mData.genres.erase(it);
            }

            break;
        }

        default:
            break;
    }
}


const AddGameFormData& AddGameView::getFormData() const
{
    return mData;
}
bool AddGameView::editInteger(const char* prompt, int& value)
{
    char buffer[64];

    std::snprintf(
        buffer, sizeof(buffer), "%d", value
    );

    echo();
    curs_set(1);

    mvhline(LINES - 3, 0, ' ', COLS);
    mvprintw(LINES - 3, 2, "%s", prompt);
    mvgetnstr(LINES - 3, 2, buffer, sizeof(buffer) - 1);

    noecho();
    curs_set(0);

    char* end = nullptr;
    errno = 0;
    long parsed = std::strtol(buffer, &end, 10);

    if (end == buffer || *end != '\0' ||
        errno == ERANGE ||
        parsed < std::numeric_limits<int>::min() ||
        parsed > std::numeric_limits<int>::max()) {
        return false;
    }

    value = static_cast<int>(parsed);
    return true;
}

bool AddGameView::editFloat(const char* prompt, float& value)
{
    char buffer[64];

    std::snprintf(
        buffer, sizeof(buffer), "%.2f", value
    );

    echo();
    curs_set(1);

    mvhline(LINES - 3, 0, ' ', COLS);
    mvprintw(LINES - 3, 2, "%s", prompt);
    mvgetnstr(LINES - 3, 2, buffer, sizeof(buffer) - 1);

    noecho();
    curs_set(0);

    char* end = nullptr;
    errno = 0;
    float parsed = std::strtof(buffer, &end);

    if (end == buffer || *end != '\0' ||
        errno == ERANGE ||
        !std::isfinite(parsed) ||
        parsed < 0.0f) {
        return false;
    }

    value = parsed;
    return true;
}

