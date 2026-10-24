#pragma once

#include <string>
#include <vector>

struct RawgGame {
    int id = 0;
    std::string title;
    int metacriticRating = 0;
    std::vector<std::string> developers;
    std::vector<std::string> publishers;
    std::vector<std::string> genres;
};