#pragma once

#include <string>

class ApiConfig {
public:
    ApiConfig();

    const std::string& getApiKey() const;
    const char* getBaseUrl() const;

private:
    const char* mApiVar;
    const char* mBaseUrl;
};