
#pragma once

#include "../model/game_library.h"
#include <vector>

enum class LibraryAction {
    NONE,
    BACK,
    ADD_GAME,
    MODIFY_GAME,
    DELETE_GAME,
    FILTER_GAMES,
    SORT_GAMES
};

class LibraryView {
private:
    enum class Panel {
        GAME_LIST,
        GAME_ACTIONS,
        TOOLS
    };

    Panel mPanel = Panel::GAME_LIST;

    int mSelectedRow = 0;
    int mSelectedAction = 0;

    void drawGameList(const GameLibrary& library);
    void drawGameActions(const GameLibrary& library);
    void drawTools(const GameLibrary& library);

public:
    LibraryView();

    void displayLibraryView(const GameLibrary& library);

    LibraryAction getUserChoice(const GameLibrary& library);

    int getSelectedGameIndex() const;
};
