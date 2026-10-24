
#include "library_view.h"

#include <curses.h>
#include <algorithm>

LibraryView::LibraryView() = default;

void LibraryView::displayLibraryView(const GameLibrary& library)
{
    clear();

    mvprintw(1, 2, "=== TWOJA BIBLIOTEKA ===");

    switch (mPanel) {
        case Panel::GAME_LIST:
            drawGameList(library);
            break;

        case Panel::GAME_ACTIONS:
            drawGameActions(library);
            break;

        case Panel::TOOLS:
            drawTools(library);
            break;
    }

    refresh();
}

void LibraryView::drawGameList(const GameLibrary& library)
{
    const auto& games = library.getLibraryGames();

    const int addRow = static_cast<int>(games.size());
    const int backRow = addRow + 1;

    int row = 3;
    const int visibleRows = LINES - 7;

    if (games.empty()) {
        mvprintw(row++, 4, "Biblioteka jest pusta.");
    }

    // Wyświetl widoczną część listy gier.
    // Kursor przewija listę również wtedy, gdy gier jest dużo.
    int firstGame = 0;

    if (mSelectedRow >= visibleRows && visibleRows > 0) {
        firstGame = mSelectedRow - visibleRows + 1;
    }

    const int lastGame = std::min(
        static_cast<int>(games.size()),
        firstGame + visibleRows
    );

    for (int i = firstGame; i < lastGame; ++i) {
        if (i == mSelectedRow) {
            attron(A_REVERSE);
        }

        mvprintw(
            row++, 4, "%s",
            games[i].getTitle().c_str()
        );

        if (i == mSelectedRow) {
            attroff(A_REVERSE);
        }
    }

    // Opcja dodawania gry.
    if (mSelectedRow == addRow) {
        attron(A_REVERSE);
    }

    mvprintw(LINES - 4, 4, "+ Dodaj gre");

    if (mSelectedRow == addRow) {
        attroff(A_REVERSE);
    }

    // Opcja powrotu.
    if (mSelectedRow == backRow) {
        attron(A_REVERSE);
    }

    mvprintw(LINES - 3, 4, "Powrot do menu");

    if (mSelectedRow == backRow) {
        attroff(A_REVERSE);
    }

    mvprintw(
        LINES - 1, 2,
        "Gora/dol: wybor | Prawo: akcje | Lewo: filtr/sort | Enter: wybierz | Esc: wstecz"
    );
}


void LibraryView::drawGameActions(const GameLibrary& library)
{
    const auto& games = library.getLibraryGames();

    if (mSelectedRow < 0 ||
        mSelectedRow >= static_cast<int>(games.size())) {
        mPanel = Panel::GAME_LIST;
        return;
    }

    const Game& game = games[mSelectedRow];

    clear();
    mvprintw(1, 2, "=== SZCZEGOLOWE INFORMACJE O GRZE ===");

    int row = 3;
    const int leftColumn = 2;
    const int rightColumn = COLS / 2 + 4;

    // Funkcja pomocnicza do wyświetlania pojedynczej informacji.
    auto drawInfo = [&](const char* label, const std::string& value) {
        if (row < LINES - 3) {
            mvprintw(row++, leftColumn, "%s %s", label, value.c_str());
        }
    };

    drawInfo("ID:", std::to_string(game.getId()));
    drawInfo("Tytul:", game.getTitle());
    drawInfo("Deweloper:", game.getDeveloper());
    drawInfo("Wydawca:", game.getPublisher());

    // Osiagniecia
    drawInfo(
        "Osiagniecia:",
        std::to_string(game.getUnlockedAchievements()) + " / " +
        std::to_string(game.getAchievementCount())
    );

    // Czas gry z jednym miejscem po przecinku.
    char playtimeText[32];
    std::snprintf(
        playtimeText,
        sizeof(playtimeText),
        "%.1f godz.",
        static_cast<double>(game.getPlaytime())
    );

    drawInfo("Czas gry:", playtimeText);

    drawInfo(
        "Ocena osobista:",
        std::to_string(game.getPersonalRating())
    );

    drawInfo(
        "Metacritic:",
        std::to_string(game.getMetacriticRating())
    );

    drawInfo(
        "Zainstalowana:",
        game.getInstalled() ? "Tak" : "Nie"
    );

    // Gatunki
    std::string genresText;

    for (const auto& genre : game.getGenres()) {
        if (!genresText.empty()) {
            genresText += ", ";
        }

        auto it = genreTranslationMap.find(genre);

        genresText += (it != genreTranslationMap.end())
            ? it->second
            : "Nieznany";
    }

    drawInfo(
        "Gatunki:",
        genresText.empty() ? "(brak)" : genresText
    );

    // Notatki
    drawInfo("Notatki:", "");

    for (const auto& note : game.getNotes()) {
        if (row < LINES - 3) {
            mvprintw(row++, leftColumn + 2, "- %s", note.c_str());
        }
    }

    // Panel akcji po prawej stronie.
    mvprintw(3, rightColumn, "=== OPCJE ===");

    const char* options[] = {
        "Modyfikuj",
        "Usun"
    };

    for (int i = 0; i < 2; ++i) {
        if (i == mSelectedAction) {
            attron(A_REVERSE);
        }

        mvprintw(5 + i, rightColumn, "%s", options[i]);

        if (i == mSelectedAction) {
            attroff(A_REVERSE);
        }
    }

    mvprintw(
        LINES - 2, 2,
        "Gora/dol: wybor opcji | Enter: zatwierdz | Esc/lewo: wroc"
    );

    refresh();
}

void LibraryView::drawTools(const GameLibrary&)
{
    const char* options[] = {
        "Filtruj",
        "Sortuj"
    };

    mvprintw(3, 4, "=== NARZEDZIA BIBLIOTEKI ===");

    for (int i = 0; i < 2; ++i) {
        if (i == mSelectedAction) {
            attron(A_REVERSE);
        }

        mvprintw(5 + i, 6, "%s", options[i]);

        if (i == mSelectedAction) {
            attroff(A_REVERSE);
        }
    }

    mvprintw(LINES - 2, 2, "Gora/dol: wybor | Enter: zatwierdz | Esc/prawo: wstecz");
}

int LibraryView::getSelectedGameIndex() const
{
    return mSelectedRow;
}

LibraryAction LibraryView::getUserChoice(const GameLibrary& library)
{
    while (true) {
        displayLibraryView(library);

        const int key = getch();
        const auto& games = library.getLibraryGames();

        const int addRow = static_cast<int>(games.size());
        const int backRow = addRow + 1;

        switch (mPanel) {
            case Panel::GAME_LIST:
                switch (key) {
                    case KEY_UP:
                        if (mSelectedRow > 0) {
                            --mSelectedRow;
                        }
                        break;

                    case KEY_DOWN:
                        if (mSelectedRow < backRow) {
                            ++mSelectedRow;
                        }
                        break;

                    case KEY_RIGHT:
                        if (mSelectedRow >= 0 &&
                            mSelectedRow < static_cast<int>(games.size())) {
                            mPanel = Panel::GAME_ACTIONS;
                            mSelectedAction = 0;
                        }
                        break;

                    case KEY_LEFT:
                        mPanel = Panel::TOOLS;
                        mSelectedAction = 0;
                        break;

                    case '\n':
                    case '\r':
                    case KEY_ENTER:
                        if (mSelectedRow == addRow) {
                            return LibraryAction::ADD_GAME;
                        }

                        if (mSelectedRow == backRow) {
                            return LibraryAction::BACK;
                        }

                        if (!games.empty()) {
                            mPanel = Panel::GAME_ACTIONS;
                            mSelectedAction = 0;
                        }
                        break;

                    case 27: // Esc
                        return LibraryAction::BACK;

                    default:
                        break;
                }
                break;

            case Panel::GAME_ACTIONS:
                switch (key) {
                    case KEY_UP:
                        mSelectedAction =
                            (mSelectedAction + 1) % 2;
                        break;

                    case KEY_DOWN:
                        mSelectedAction =
                            (mSelectedAction + 1) % 2;
                        break;

                    case KEY_LEFT:
                    case 27:
                        mPanel = Panel::GAME_LIST;
                        break;

                    case '\n':
                    case '\r':
                    case KEY_ENTER:
                        return mSelectedAction == 0
                            ? LibraryAction::MODIFY_GAME
                            : LibraryAction::DELETE_GAME;

                    default:
                        break;
                }
                break;

            case Panel::TOOLS:
                switch (key) {
                    case KEY_UP:
                    case KEY_DOWN:
                        mSelectedAction =
                            (mSelectedAction + 1) % 2;
                        break;

                    case KEY_RIGHT:
                    case 27:
                        mPanel = Panel::GAME_LIST;
                        break;

                    case '\n':
                    case '\r':
                    case KEY_ENTER:
                        return mSelectedAction == 0
                            ? LibraryAction::FILTER_GAMES
                            : LibraryAction::SORT_GAMES;

                    default:
                        break;
                }
                break;
        }
    }
}
