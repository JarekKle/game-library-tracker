#pragma once

#include <string>

struct HttpResponse {
    long statusCode = 0;
    std::string body;
};

class HttpClient {
public:
    HttpClient();
    ~HttpClient();

    HttpResponse get(const std::string& url) const;
};