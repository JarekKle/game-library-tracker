#include "api_config.h"

#include <cstdlib> 
#include <iostream>
#include <string>
ApiConfig::ApiConfig() : mBaseUrl("https://api.rawg.io/api/"), mApiVar("RAWG_API_KEY") {};
const std::string& ApiConfig::getApiKey() const {
    const char* env_var_value = std::getenv(mApiVar);
    return env_var_value ? std::string(env_var_value) : std::string();
}
    const char* ApiConfig::getBaseUrl() const{
    return mBaseUrl;
    };
