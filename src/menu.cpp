#include "menu.h"
#include <functional>
#include <unordered_map>
#include "connect_4.h"
#include "get_input_from_user.h"
#include "hangman.h"
#include "noughts_and_crosses.h"
#include "play_guess_the_number.h"

struct Game {
    std::string           name;
    std::function<void()> play;
};

static const std::unordered_map<char, Game> games{
    {'1', {"Guess the Number", &play_guess_the_number}},
    {'2', {"Hangman", &play_hangman}},
    {'3', {"Noughts and Crosses", &play_noughts_and_crosses}},
    {'4', {"Connect 4", &play_connect_4}},
};

void show_the_list_of_commands(const std::unordered_map<char, Game>& games)
{
    std::cout << "What do you want to do?\n";
    for (const auto& [command, game] : games) {
        std::cout << command << ": Play \"" << game.name << "\"\n";
    }
    std::cout << "q: Quit\n";
}

void show_menu()
{
    bool quit = false;
    while (!quit) {
        show_the_list_of_commands(games);
        const auto command = get_input_from_user<char>();
        if (command == 'q') {
            quit = true;
        }
        else {
            const auto game = games.find(command);
            if (game != games.end()) {
                game->second.play();
            }
            else {
                std::cout << "Sorry I don't know that command!\n";
            }
        }
    }
}