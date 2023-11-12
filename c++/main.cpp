/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iengels <iengels@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 23:50:03 by iengels           #+#    #+#             */
/*   Updated: 2023/11/12 06:44:27 by iengels          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wordle.hpp"

bool ft_check_yellow(std::string guess, std::string solution, int index)
{
    int count = 0;
    int count_b = 0;
    if (solution.find(guess[index]) == std::string::npos)
        return false;
    for (int i = 0; i < 5; i++)
    {
        if (guess[index] == solution[i])
            count++;
        if (guess[i] == guess[index])
            count_b++;
    }
    if (count == 1 && count_b == 1)
        return true;
    for (int i = 0; i < index; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (guess[i] == solution[j] && count > 0)
            {
                count--;
                break;
            }
        }
    }
    for (int i = index + 1; i < 5; i++)
    {
        if (guess[index] == solution[i] && guess[i] == solution[i] && count > 0)
            count--;
    }
    if (count > 0)
        return true;
    return false;
}

void ft_print_guesses(t_data *data)
{
    for (const std::string &str : data->guesses)
    {
        std::cout << "          |" << BOLD;
        for (int i = 0; i < 5; i++)
        {
            if (str[i] == data->solution[i])
                std::cout << BOLD << B_GREEN << " " << (char)(str[i] - 32) << " " << RESET << "|";
            else if (ft_check_yellow(str, data->solution, i) == true)
                std::cout << BOLD << B_YELLOW << " " << (char)(str[i] - 32) << " " << RESET << "|";
            else
                std::cout << BOLD << B_GREY << " " << (char)(str[i] - 32) << " " << RESET << "|";
        }
        std::cout << std::endl;
    }
    for (int i = 6 - data->guess; i > 0; i--)
    {
        std::cout << "          |" << BOLD;
        for (int j = 0; j < 5; j++)
            std::cout << BOLD << B_GREY << "   " << RESET << "|";
        std::cout << std::endl;
    }
    std::cout << RESET << std::endl;
}

void ft_print_keyboard(t_data *data)
{
    std::cout << "  |";
    for (int i = 0; i < 26; i++)
    {
        if (i == 10)
            std::cout << "\n    |";
        if (i == 19)
            std::cout << "\n      |";
        if (data->keyboard[i] == 0)
            std::cout << B_GREY << " " << (char)(i + 'A') << " " << RESET;
        else if (data->keyboard[i] == 1)
            std::cout << B_YELLOW << " " << (char)(i + 'A') << " " << RESET;
        else if (data->keyboard[i] == 2)
            std::cout << B_GREEN << " " << (char)(i + 'A') << " " << RESET;
        std::cout << "|";
    }
    std::cout << RESET << std::endl;
}

bool ft_check_input(std::string input, t_data *data)
{
    if (input.length() != 5)
        return false;
    for (int i = 0; i < 5; i++)
        input[i] = std::tolower(input[i]);
    if (data->wordlist.find(input) == data->wordlist.end())
        return false;
    for (int i = 0; i < 5; i++)
    {
        if (input[i] < 'a' || input[i] > 'z')
            return false;
        if (input[i] == data->solution[i] && data->keyboard[input[i] - 'a'] != 2)
            data->keyboard[input[i] - 'a'] = 2;
        else if (data->solution.find(input[i]) != std::string::npos && data->keyboard[input[i] - 'a'] != 2)
            data->keyboard[input[i] - 'a'] = 1;
    }
    data->guess++;
    data->guesses.push_back(input);
    return true;
}

bool ft_game(t_data *data)
{
    ft_gui("Guess: ");
    while (std::cin.eof() == false)
    {
        ft_print_guesses(data);
        ft_print_keyboard(data);
        std::string input;
        std::cin >> input;

        if (ft_check_input(input, data) == true)
        {
            if (data->solution == input)
            {
                ft_gui("\n\t      🎉 \033[32mYou win!\033[0m 🎉\n");
                ft_print_guesses(data);
                ft_print_keyboard(data);
                std::cout << "Enter c to continue..." << std::endl;
                std::cin >> input;
                if (input == "c")
                    return true;
                return false;
            }
            else if (data->guess == 6)
            {
                ft_gui("\n\t\t\033[31mYou lose!\033[0m\n");
                std::cout << YELLOW  << BOLD << "           Solution: " << data->solution << RESET << std::endl;
                ft_print_guesses(data);
                ft_print_keyboard(data);
                std::cout << "Enter c to continue..." << std::endl;
                std::cin >> input;
                if (input == "c")
                    return true;
                return false;
            }
            else
            ft_gui("Guess: ");
        }
        else
            ft_gui("Word not in wordlist! Please try again\nGuess: ");
    }
    return false;
}
void ft_init_wordlist(t_data *data)
{
    std::ifstream wordlist("wordlist.txt");
    std::string word;
    while (std::getline(wordlist, word, '\n'))
    {
        data->o_wordlist.push_back(word);
        data->wordlist.insert(word);
    }
}

void ft_init_data(t_data *data)
{
    std::srand(static_cast<unsigned>(std::time(0)));
    for (int i = 0; i < 26; i++)
        data->keyboard[i] = 0;
    data->guess = 0;

    data->guesses = {};
    if (!data->o_wordlist.empty())
    {
        std::size_t randomIndex = std::rand() % data->o_wordlist.size();
        data->solution = data->o_wordlist[randomIndex];
    }
}

int main(void)
{
    t_data data;
    ft_init_wordlist(&data);
    if (data.o_wordlist.empty())
    {
        std::cout << RED << "Error: No wordlist found." << RESET << std::endl;
        return (0);
    }
    while (true)
    {
        ft_init_data(&data);
        ft_gui("\nWelcome to Wordle!\nPlease enter New Game(n) or Exit(e)");
        if (ft_new_game() == false)
            break;
        if (ft_game(&data) == false)
            break;
    }
    std::cout << GREEN << "Goodbye!" << RESET << std::endl;
    return (0);
}