#pragma once
#include "../model/game_library.h"

enum class WishlistAction {
    NONE,
    BACK,
    ADD_GAME,
    MODIFY_GAME,
    DELETE_GAME
};

class WishlistView {
private:
    enum class Panel {
        GAME_LIST,
        GAME_ACTIONS
    };

    Panel mPanel = Panel::GAME_LIST;

    int mSelectedRow = 0;
    int mSelectedAction = 0;

    void drawGameList(const GameLibrary& library);
    void drawGameActions(const GameLibrary& library);

public:
    WishlistView();

    void displayWishlistView(const GameLibrary& library);

    WishlistAction getUserChoice(const GameLibrary& library);

    int getSelectedGameIndex() const;
};
