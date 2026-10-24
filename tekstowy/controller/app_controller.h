#pragma once

#include "../view/screen.h"
#include "../model/game_library.h"
#include "../view/home_view.h"
#include "../view/activity_log_view.h"
#include "../view/export_view.h"
#include "../view/game_search_view.h"
#include "../view/import_view.h"
#include "../view/library_view.h"
#include "../view/settings_view.h"
#include "../view/wishlist_view.h"
#include "../view/add_game_view.h"

#include <iostream>
#include <curses.h>
#include <stack>
#include "../api/rawg_api_client.h"
class AppController{
    private:
        GameLibrary& mGameLibrary;
        RawgApiClient& mRawgApiClient;
        Screen mCurrentScreen;
        bool mRunning;
        ActivityLogView mActivityLogView;
        ExportView mExportView;
        GameSearchView mGameSearchView;
        HomeView mHomeView;
        ImportView mImportView;
        LibraryView mLibraryView;
        SettingsView mSettingsView;
        WishlistView mWishlistView;
        AddGameView mAddGameView;
        std::stack<Screen> mScreenStack;
        
        void changeScreen(Screen newScreen);
        void handleHome();
        void handleActivityLog();
        void handleExport();
        void handleGameSearch();
        void handleImport();
        void handleLibrary();
        void handleSettings();
        void handleWishlist();
        void handleAddGame(bool addToWishlist);
        void renderCurrentScreen();
        void goBackScreen();

    public:
        explicit AppController(
            GameLibrary& gameLibrary
        );
        void run();
};