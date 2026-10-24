#pragma once

#include "http_client.h"
#include "api_config.h"
#include "rawg_game.h"

#include <string>
#include <vector>

class RawgApiClient {
public:
    RawgApiClient(
        const HttpClient& httpClient,
        const ApiConfig& config
    );

    std::vector<RawgGame> searchGames(
        const std::string& query
    ) const;

    RawgGame getGameDetails(int rawgId) const;

private:
    const HttpClient& mHttpClient;
    const ApiConfig& mConfig;
};