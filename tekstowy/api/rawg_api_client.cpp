
#include "rawg_api_client.h"
#include <nlohmann/json.hpp>

#include <stdexcept>
#include <string>
#include <vector>

using json = nlohmann::json;

namespace {
std::vector<std::string> readNames(
    const json& data,
    const std::string& field
) {
    std::vector<std::string> names;

    if (!data.contains(field) || !data[field].is_array()) {
        return names;
    }

    for (const auto& item : data[field]) {
        if (item.is_object() && item.contains("name")
            && item["name"].is_string()) {
            names.push_back(item["name"].get<std::string>());
        }
    }

    return names;
}
}

RawgApiClient::RawgApiClient(
    const HttpClient& httpClient,
    const ApiConfig& config
)
    : mHttpClient(httpClient), mConfig(config) {}

std::vector<RawgGame> RawgApiClient::searchGames(
    const std::string& query
) const {
    // Zakładamy, że baseUrl kończy się znakiem '/'.
    const std::string url =
        mConfig.getBaseUrl() + "games?key=" +
        mConfig.getApiKey() + "&search=" + query;

    HttpResponse response = mHttpClient.get(url);

    if (response.statusCode != 200) {
        throw std::runtime_error(
            "Nie udalo sie pobrac gier z RAWG API. HTTP: " +
            std::to_string(response.statusCode)
        );
    }

    try {
        const json data = json::parse(response.body);
        std::vector<RawgGame> games;

        if (!data.contains("results") ||
            !data["results"].is_array()) {
            return games;
        }

        for (const auto& item : data["results"]) {
            RawgGame game;
            game.id = item.value("id", 0);
            game.title = item.value("name", std::string("Brak"));
            game.metacriticRating = item.value("metacritic", 0);

            // Wyniki wyszukiwania nie zawsze zawierają te pola.
            // Jeśli ich nie ma, wektory pozostaną puste.
            game.developers = readNames(item, "developers");
            game.publishers = readNames(item, "publishers");
            game.genres = readNames(item, "genres");

            games.push_back(game);
        }

        return games;
    }
    catch (const json::exception& e) {
        throw std::runtime_error(
            std::string("Blad parsowania odpowiedzi RAWG: ") + e.what()
        );
    }
}

RawgGame RawgApiClient::getGameDetails(int rawgId) const {
    const std::string url =
        mConfig.getBaseUrl() + "games/" +
        std::to_string(rawgId) + "?key=" + mConfig.getApiKey();

    HttpResponse response = mHttpClient.get(url);

    if (response.statusCode != 200) {
        throw std::runtime_error(
            "Nie udalo sie pobrac szczegolow gry. HTTP: " +
            std::to_string(response.statusCode)
        );
    }

    try {
        const json data = json::parse(response.body);

        RawgGame game;
        game.id = data.value("id", 0);
        game.title = data.value("name", std::string("Brak"));
        game.metacriticRating = data.value("metacritic", 0);
        game.developers = readNames(data, "developers");
        game.publishers = readNames(data, "publishers");
        game.genres = readNames(data, "genres");

        return game;
    }
    catch (const json::exception& e) {
        throw std::runtime_error(
            std::string("Blad parsowania szczegolow gry: ") + e.what()
        );
    }
}
