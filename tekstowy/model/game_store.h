#pragma once
#include <string>
#include <unordered_map>
enum GameStore{
    STEAM,
    PLAYSTATION_STORE,
    XBOX_STORE,
    APP_STORE,
    EPIC_GAMES,
    GOG,
    UBISOFT,
    NINTENDO_SWITCH_STORE,
    MICROSOFT_STORE,
    GOOGLE_PLAY,
    OTHER_STORE
};
inline const std::unordered_map<GameStore, std::string> storeTranslationMap = {
{GameStore::STEAM, "Steam"},
{GameStore::PLAYSTATION_STORE, "PlayStation Store"},
{GameStore::XBOX_STORE, "Xbox Store"},
{GameStore::APP_STORE, "App Store"},
{GameStore::EPIC_GAMES, "Epic Games"},
{GameStore::GOG, "GOG"},
{GameStore::UBISOFT, "Ubisoft"},
{GameStore::NINTENDO_SWITCH_STORE, "Nintendo Switch Store"},
{GameStore::MICROSOFT_STORE, "Microsoft Store"},
{GameStore::GOOGLE_PLAY, "Google Play"},
{GameStore::OTHER_STORE, "Other Store"}
};