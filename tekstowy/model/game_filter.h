#pragma once

#include <optional>
#include "game_status.h"
#include "game_platform.h"
#include "game_genre.h"
#include <vector>

struct GameFilter {
    std::optional<GameStatus> status;
    std::optional<GamePlatform> platform;
    std::optional<float> minPlaytime;
    std::optional<int> minPersonalRating;
    std::optional<std::vector<GameGenre>> genres;
    std::optional<bool> installed;
};