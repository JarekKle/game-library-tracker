#pragma once
#include <string>
#include <unordered_map>
enum class GameSortCriteria {
    Title,
    Playtime,
    PersonalRating,
    MetacriticRating,
    CompletionPercent
};

enum class SortOrder {
    ASCENDING,
    DESCENDING
};
inline const std::unordered_map<GameSortCriteria, std::string> sortCriteriaTranslationMap = {
{GameSortCriteria::Title, "Title"},
{GameSortCriteria::Playtime, "Playtime"},
{GameSortCriteria::PersonalRating, "Personal Rating"},
{GameSortCriteria::MetacriticRating, "Metacritic Rating"},
{GameSortCriteria::CompletionPercent, "Completion Percent"}
};
inline const std::unordered_map<SortOrder, std::string> sortOrderTranslationMap = {
{SortOrder::ASCENDING, "Ascending"},
{SortOrder::DESCENDING, "Descending"}
};