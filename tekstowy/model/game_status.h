#pragma once
#include <string>
#include <unordered_map>

enum GameStatus {
    PLAYING,
    COMPLETED,
    PERFECTED,
    DROPPED,
    ON_HOLD,
    PLAN_TO_PLAY
};
inline const std::unordered_map<GameStatus, std::string> statusTranslationMap = {
{GameStatus::PLAYING, "Playing"},
{GameStatus::COMPLETED, "Completed"},
{GameStatus::PERFECTED, "Perfected"},
{GameStatus::DROPPED, "Dropped"},
{GameStatus::ON_HOLD, "On Hold"},
{GameStatus::PLAN_TO_PLAY, "Plan to Play"}
};