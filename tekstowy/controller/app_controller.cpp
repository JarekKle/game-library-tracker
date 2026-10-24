#include "app_controller.h"
AppController::AppController(GameLibrary &gameLibrary) : mGameLibrary(gameLibrary),
                                                        mRawgApiClient(RawgApiClient(HttpClient(), ApiConfig())),
                                                         mCurrentScreen(Screen::HOME),
                                                         mRunning(true),
                                                         mActivityLogView(ActivityLogView()),
                                                         mExportView(ExportView()),
                                                         mGameSearchView(GameSearchView()),
                                                         mHomeView(HomeView()),
                                                         mImportView(ImportView()),
                                                         mLibraryView(LibraryView()),
                                                         mSettingsView(SettingsView()),
                                                         mWishlistView(WishlistView()),
                                                         mAddGameView(AddGameView()),
                                                         mScreenStack({mCurrentScreen}) {
                                                         };
void AppController::run()
{
    while (mRunning)
    {
        renderCurrentScreen();
    }
};
void AppController::changeScreen(Screen newScreen)
{
    mScreenStack.push(mCurrentScreen);
    mCurrentScreen = newScreen;
};
void AppController::goBackScreen()
{
    if (!mScreenStack.empty())
    {
        mCurrentScreen = mScreenStack.top();
        mScreenStack.pop();
    }
};
void AppController::handleActivityLog()
{
    mActivityLogView.displayActivityLogView();
    const int choice = mActivityLogView.getUserChoice();

    switch (choice)
    {
    case 0:
        goBackScreen();
        break;
    default:
        mvprintw(13, 2, "Nieprawidlowy wybor.");
        refresh();
        break;
    }
};
void AppController::handleExport()
{
    mExportView.displayExportView();
    const int choice = mExportView.getUserChoice();

    switch (choice)
    {
    case 0:
        goBackScreen();
        break;
    default:
        mvprintw(13, 2, "Nieprawidlowy wybor.");
        refresh();
        break;
    }
};
void AppController::handleGameSearch()
{
    mGameSearchView.displayGameSearchView();
    const int choice = mGameSearchView.getUserChoice();

    switch (choice)
    {
    case 0:
        goBackScreen();
        break;
    case 1:
        const std::vector<RawgGame>& games = mRawgApiClient.searchGames("Hollow%20Knight");
        mGameSearchView.displayResults(games);
        break;
    default:
        mvprintw(13, 2, "Nieprawidlowy wybor.");
        refresh();
        break;
    }
};
void AppController::handleImport()
{
    mImportView.displayImportView();
    const int choice = mImportView.getUserChoice();

    switch (choice)
    {
    case 0:
        goBackScreen();
        break;
    default:
        mvprintw(13, 2, "Nieprawidlowy wybor.");
        refresh();
        break;
    }
};
void AppController::handleLibrary()
{
    const LibraryAction action =
        mLibraryView.getUserChoice(mGameLibrary);

    switch (action) {
        case LibraryAction::BACK:
            goBackScreen();
            break;

        case LibraryAction::ADD_GAME:
            changeScreen(Screen::ADD_GAME);
            break;

        case LibraryAction::MODIFY_GAME: {
            const int index =
                mLibraryView.getSelectedGameIndex();

            // TODO: otworz formularz edycji gry.
            // index wskazuje wybrana gre.
            break;
        }

        case LibraryAction::DELETE_GAME: {
            const int index =
                mLibraryView.getSelectedGameIndex();

            // TODO: usun gre po potwierdzeniu.
            // index wskazuje wybrana gre.
            break;
        }

        case LibraryAction::FILTER_GAMES:
            // TODO: otworz panel filtrowania.
            break;

        case LibraryAction::SORT_GAMES:
            // TODO: otworz panel sortowania.
            break;

        case LibraryAction::NONE:
            break;
    }
}

void AppController::handleSettings()
{
    mSettingsView.displaySettingsView();
    const int choice = mSettingsView.getUserChoice();

    switch (choice)
    {
    case 0:
        goBackScreen();
        break;
    default:
        mvprintw(13, 2, "Nieprawidlowy wybor.");
        refresh();
        break;
    }
};
void AppController::handleWishlist()
{
    const WishlistAction action =
        mWishlistView.getUserChoice(mGameLibrary);

    switch (action) {
        case WishlistAction::BACK:
            goBackScreen();
            break;

        case WishlistAction::ADD_GAME:
            changeScreen(Screen::ADD_GAME);
            break;

        case WishlistAction::MODIFY_GAME: {
            const int index =
                mLibraryView.getSelectedGameIndex();

            // TODO: otworz formularz edycji gry.
            // index wskazuje wybrana gre.
            break;
        }

        case WishlistAction::DELETE_GAME: {
            const int index =
                mLibraryView.getSelectedGameIndex();

            // TODO: usun gre po potwierdzeniu.
            // index wskazuje wybrana gre.
            break;
        }
        case WishlistAction::NONE:
            break;
    }
};

void AppController::handleHome()
{

    mHomeView.displayHomeView();
    const int choice = mHomeView.getUserChoice();

    switch (choice)
    {
    case 1:
        changeScreen(Screen::LIBRARY);
        break;
    case 2:
        changeScreen(Screen::GAME_SEARCH);
        break;
    case 3:
        changeScreen(Screen::WISHLIST);
        break;
    case 4:
        changeScreen(Screen::ACTIVITY_LOG);
        break;
    case 5:
        changeScreen(Screen::SETTINGS);
        break;
    case 6:
        changeScreen(Screen::EXPORT);
        break;
    case 7:
        mRunning = false;
        break;
    default:
        mvprintw(13, 2, "Nieprawidlowy wybor.");
        refresh();
        break;
    }
};
void AppController::renderCurrentScreen()
{
    switch (mCurrentScreen)
    {
    case Screen::HOME:
        handleHome();
        break;
    case Screen::LIBRARY:
        handleLibrary();
        break;
    case Screen::GAME_SEARCH:
        handleGameSearch();
        break;
    case Screen::WISHLIST:
        handleWishlist();
        break;
    case Screen::ACTIVITY_LOG:
        handleActivityLog();
        break;
    case Screen::SETTINGS:
        handleSettings();
        break;
    case Screen::EXPORT:
        handleExport();
        break;
    case Screen::ADD_GAME:
        handleAddGame(static_cast<bool>(mScreenStack.top() == Screen::WISHLIST));
        break;
    }
};
void AppController::handleAddGame(bool addToWishlist)
{
    mAddGameView.beginForm(addToWishlist);

    bool formOpen = true;

    while (formOpen) {
        mAddGameView.drawForm();

        FormAction action = mAddGameView.handleInput();

        switch (action) {
            case FormAction::MOVE_UP:
                mAddGameView.moveSelection(-1);
                break;

            case FormAction::MOVE_DOWN:
                mAddGameView.moveSelection(1);
                break;

            case FormAction::MOVE_LEFT:
                mAddGameView.changeSelectedValue(-1);
                break;

            case FormAction::MOVE_RIGHT:
                mAddGameView.changeSelectedValue(1);
                break;

            case FormAction::EDIT:
                mAddGameView.editSelectedField();
                break;

            case FormAction::SAVE: {
                const AddGameFormData& data =
                    mAddGameView.getFormData();
                Game newGame(
                    mGameLibrary.getNextId(),
                    data.title,
                    data.developer,
                    data.publisher,
                    data.achievementCount,
                    data.unlockedAchievements,
                    data.playtime,
                    data.personalRating,
                    data.metacriticRating,
                    data.notes,
                    data.genres,
                    data.store,
                    data.platform,
                    data.status,
                    data.availability,
                    data.installed
                );
                mGameLibrary.addGame(newGame);
                formOpen = false;
                goBackScreen();

                break;
            }

            case FormAction::CANCEL:
                formOpen = false;
                goBackScreen();

            case FormAction::NONE:
                break;
        }
    }
}