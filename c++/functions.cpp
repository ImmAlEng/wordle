#include "wordle.hpp"

// void ft_draw_boxes(t_data *data)
// {
//     std::cout << data->guesses << std::endl;
//     std::cout << data->keyboard << std::endl;
// }

bool ft_new_game(void)
{
    while (std::cin.eof() == false)
    {
        std::string input;
        std::cin >> input;
        if (input == "n")
            return true;
        else if (input == "e")
            return false;
        else
            ft_gui("Invalid input, please try again. (n)ew game or (e)xit");
    }
    return false;
}

bool ft_gui(std::string message)
{

    system("clear");
    std::flush(std::cout);
    std::cout << GREEN << WORDLE << RESET << std::endl;
    std::cout << BOLD << YELLOW << message << RESET << std::endl;
    return true;
}