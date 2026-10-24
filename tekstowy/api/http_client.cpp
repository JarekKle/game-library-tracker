#include "http_client.h"
#include <curl/curl.h>
HttpClient::HttpClient() {
    
    // Inicjalizacja libcurl
    CURL* curl = curl_easy_init();

    if (curl == nullptr) {
        std::cerr << "Nie mozna zainicjalizowac curl.\n";
        return HttpResponse();
    }

}
HttpClient::~HttpClient() {
    // Cleanup libcurl
    curl_global_cleanup();
}
HttpResponse HttpClient::get(const std::string& url) const {
    HttpResponse response;

    // Inicjalizacja libcurl
    CURL* curl = curl_easy_init();

    if (curl == nullptr) {
        std::cerr << "Nie mozna zainicjalizowac curl.\n";
        return response;
    }

    std::string responseBody;

    // Konfiguracja żądania HTTP
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBody);

    // Wykonanie żądania
    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        std::cerr << "Blad HTTP: "
                  << curl_easy_strerror(result) << '\n';

        curl_easy_cleanup(curl);
        return response;
    }

    // Sprawdzenie kodu odpowiedzi HTTP
    long statusCode = 0;
    curl_easy_getinfo(
        curl, CURLINFO_RESPONSE_CODE, &statusCode
    );

    response.statusCode = statusCode;
    response.body = responseBody;

    curl_easy_cleanup(curl);

    return response;
}