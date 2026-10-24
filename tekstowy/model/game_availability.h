#pragma once
#include <string>
#include <unordered_map>
enum GameAvailability {
    BOUGHT,
    BORROWED,
    PLATFORM_FAMILY,
    GAME_PASS,
    WISHLISTED
};
inline const std::unordered_map<GameAvailability, std::string> availabilityTranslationMap = {
{GameAvailability::BOUGHT, "Bought"},
{GameAvailability::BORROWED, "Borrowed"},
{GameAvailability::PLATFORM_FAMILY, "Platform Family"},
{GameAvailability::GAME_PASS, "Game Pass"},
{GameAvailability::WISHLISTED, "Wishlisted"}
};