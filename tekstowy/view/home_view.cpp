#include "home_view.h"
#include <curses.h>
HomeView::HomeView(){};
void HomeView::displayHomeView()
{
    clear();

    mvprintw(1, 2, "=== GAMEVAULT ===");

    const char* options[] = {
        "Biblioteka",
        "Wyszukaj gre",
        "Lista zyczen",
        "Dziennik aktywnosci",
        "Ustawienia",
        "Eksport",
        "Wyjscie"
    };

    const int optionCount =
        sizeof(options) / sizeof(options[0]);

    for (int i = 0; i < optionCount; ++i) {
        if (i == mSelectedOption) {
            attron(A_REVERSE);
        }

        mvprintw(4 + i, 4, "%s", options[i]);

        if (i == mSelectedOption) {
            attroff(A_REVERSE);
        }
    }

    mvprintw(
        LINES - 2, 2,
        "Strzalki: wybor | Enter: zatwierdz"
    );

    refresh();
}
int HomeView::getUserChoice()
{
    const int optionCount = 7;

    while (true) {
        int key = getch();

        switch (key) {
            case KEY_UP:
                mSelectedOption =
                    (mSelectedOption - 1 + optionCount)
                    % optionCount;
                break;

            case KEY_DOWN:
                mSelectedOption =
                    (mSelectedOption + 1)
                    % optionCount;
                break;

            case '\n':
            case '\r':
            case KEY_ENTER:
                return mSelectedOption + 1;

            default:
                break;
        }

        displayHomeView();
    }
}