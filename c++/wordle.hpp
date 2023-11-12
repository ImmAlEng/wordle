#ifndef WORDLE_HPP
#define WORDLE_HPP

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <fstream>
#include <random>
#include <vector>

#pragma once

#ifndef WHITE
#define WHITE "\033[97m"
#endif 

#ifndef GREEN
#define GREEN "\033[32m"
#endif

#ifndef YELLOW
#define YELLOW "\033[33m"
#endif

#ifndef GRAY
#define GRAY "\033[37m"
#endif

#ifndef RED
#define RED "\033[31m"
#endif

#ifndef RESET
#define RESET "\033[0m"
#endif

#ifndef BOLD
#define BOLD "\033[1m"
#endif

#ifndef B_GREY
#define B_GREY "\033[100;97m"
#endif

#ifndef B_YELLOW
#define B_YELLOW "\033[43;97m"
#endif

#ifndef B_GREEN
#define B_GREEN "\033[42;97m"
#endif

#ifndef WORDLE 
#define WORDLE "██     ██  ██████  ██████  ██████  ██      ███████\n██     ██ ██    ██ ██   ██ ██   ██ ██      ██\n██  █  ██ ██    ██ ██████  ██   ██ ██      █████   \n██ ███ ██ ██    ██ ██   ██ ██   ██ ██      ██      \n ███ ███   ██████  ██   ██ ██████  ███████ ███████"
#endif

typedef struct s_data
{
    int keyboard[26];
    int guess;
    std::vector<std::string> guesses;
    std::string solution;

    std::unordered_set<std::string> wordlist;
    std::vector<std::string> o_wordlist;
} t_data;

bool ft_gui(std::string message);
bool ft_new_game(void);

#endif