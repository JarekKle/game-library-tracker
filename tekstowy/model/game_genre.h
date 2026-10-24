#pragma once
#include <string>
#include <unordered_map>

enum GameGenre {
    ACTION,
    INDIE,
    ADVENTURE,
    RPG,
    STRATEGY,
    SHOOTER,
    CASUAL,
    SIMULATION,
    PUZZLE,
    ARCADE,
    PLATFORMER,
    MASSIVELY_MULTIPLAYER,
    RACING,
    SPORTS,
    FIGHTING,
    FAMILY,
    BOARD_GAME,
    CARD,
    EDUCATIONAL
};
inline const std::unordered_map<GameGenre, std::string> genreTranslationMap = {
{GameGenre::ACTION, "Action"},
{GameGenre::INDIE, "Indie"},
{GameGenre::ADVENTURE, "Adventure"},
{GameGenre::RPG, "RPG"},
{GameGenre::STRATEGY, "Strategy"},
{GameGenre::SHOOTER, "Shooter"},
{GameGenre::CASUAL, "Casual"},
{GameGenre::SIMULATION, "Simulation"},
{GameGenre::PUZZLE, "Puzzle"},
{GameGenre::ARCADE, "Arcade"},
{GameGenre::PLATFORMER, "Platformer"},
{GameGenre::MASSIVELY_MULTIPLAYER, "Massively Multiplayer"},
{GameGenre::RACING, "Racing"},
{GameGenre::SPORTS, "Sports"},
{GameGenre::FIGHTING, "Fighting"},
{GameGenre::FAMILY, "Family"},
{GameGenre::BOARD_GAME, "Board Game"},
{GameGenre::CARD, "Card"},
{GameGenre::EDUCATIONAL, "Educational"}
};