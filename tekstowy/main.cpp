// #include <curses.h>
// #include "controller/app_controller.h"
// int main() {
//         initscr();
//     cbreak();
//     noecho();
//     keypad(stdscr, TRUE);
//     Game game1(
//         1,
//         "The Legend of Zelda: Breath of the Wild",
//         "Nintendo",
//         "Nintendo",
//         120,
//         100,
//         200.5f,
//         10,
//         97,
//         {"Amazing open-world adventure!", "Best game ever!"},
//         {GameGenre::ACTION, GameGenre::ADVENTURE},
//         GameStore::NINTENDO_SWITCH_STORE,
//         GamePlatform::NINTENDO_SWITCH,
//         GameStatus::COMPLETED,
//         GameAvailability::BOUGHT,
//         true
//     );
//     Game game2(
//         2,
//         "Hollow Knight",
//         "Team Cherry",
//         "Team Cherry",
//         50,
//         50,
//         80.0f,
//         9,
//         90,
//         {"Challenging and beautiful!", "A must-play for Metroidvania fans."},
//         {GameGenre::ACTION, GameGenre::ADVENTURE, GameGenre::PLATFORMER},
//         GameStore::STEAM,
//         GamePlatform::PC,
//         GameStatus::PERFECTED,
//         GameAvailability::BOUGHT,
//         true
//     );
//     Game game4(
//         4,
//         "Dark souls",
//         "Matt Makes Games",
//         "Matt Makes Games",
//         30,
//         95,
//         {GameGenre::PLATFORMER, GameGenre::INDIE},
//         GameStore::EPIC_GAMES,
//         GamePlatform::PC,
//         GameStatus::PLAN_TO_PLAY,
//         GameAvailability::WISHLISTED
//     );
//      Game game3(
//         3,
//         "Celeste",
//         "Matt Makes Games",
//         "Matt Makes Games",
//         30,
//         95,
//         {GameGenre::PLATFORMER, GameGenre::INDIE},
//         GameStore::EPIC_GAMES,
//         GamePlatform::PC,
//         GameStatus::PLAN_TO_PLAY,
//         GameAvailability::WISHLISTED
//     );   
//     GameLibrary myGameLibrary({game1, game2, game3});
//     AppController appController(myGameLibrary);
//     myGameLibrary.addGame(game4);
//     appController.run();

//     endwin();
//     return 0;
// }

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include <iostream>
#include <string>

using json = nlohmann::json;

// Ta funkcja odbiera fragmenty odpowiedzi HTTP
// i zapisuje je do std::string.
size_t writeCallback(
    char* data,
    size_t size,
    size_t nmemb,
    void* userData
) {
    size_t bytes = size * nmemb;

    auto* response = static_cast<std::string*>(userData);
    response->append(data, bytes);

    return bytes;
}

int main() {
    const std::string apiKey = "8843ba4c49fe444abfdd8571c4524659";

    // Wyszukiwanie gry po nazwie
    const std::string url =
        "https://api.rawg.io/api/games?key=" + apiKey +
        "&search=Hollow%20Knight&page_size=5";

    // Inicjalizacja libcurl
    CURL* curl = curl_easy_init();

    if (curl == nullptr) {
        std::cerr << "Nie mozna zainicjalizowac curl.\n";
        return 1;
    }

    std::string response;

    // Konfiguracja żądania HTTP
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Wykonanie żądania
    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        std::cerr << "Blad HTTP: "
                  << curl_easy_strerror(result) << '\n';

        curl_easy_cleanup(curl);
        return 1;
    }

    // Sprawdzenie kodu odpowiedzi HTTP
    long statusCode = 0;
    curl_easy_getinfo(
        curl, CURLINFO_RESPONSE_CODE, &statusCode
    );

    curl_easy_cleanup(curl);

    if (statusCode != 200) {
        std::cerr << "Serwer zwrocil kod: "
                  << statusCode << '\n';
        std::cerr << response << '\n';
        return 1;
    }

    // Parsowanie tekstu JSON
    try {
        json data = json::parse(response);

        // Wyniki wyszukiwania znajdują się w polu "results"
        for (const auto& game : data.at("results")) {
            std::cout
                << "ID RAWG: " << game.value("id", 0) << '\n'
                << "Tytul: "
                << game.value("name", std::string("Brak"))
                << '\n'
                << "Metacritic: "
                << game.value("metacritic", 0)
                << "\n------------------\n";
        }
        
    
    }
    catch (const json::exception& e) {
        std::cerr << "Blad parsowania JSON: "
                  << e.what() << '\n';
                
        return 1;
    }
    return 0;
}
