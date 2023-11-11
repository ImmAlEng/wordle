
#include "wordle.h"

void ft_clean_exit(t_data *d, char *err)
{
    (void)d;
    ft_putstr_fd(err, 2);
    exit(0);
}

void ft_init_data(t_data *d)
{
    srand(time(NULL));
    d->nb = rand() % d->size;
    d->sol = ft_strdup((const char*)ft_list_data_i(d->list, d->nb));
    if (!d->sol)
        ft_clean_exit(d, "Error: Bad alloc");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 5; j++)
            d->matrix[i][j] = '_';
    }
    d->guess = 0;
}

char *ft_list_data_i(t_slist *l, int32_t nb)
{
    while (--nb > 0)
        l = l->next;
    return (l->str);
}

void ft_print_input(t_data *d, char *input)
{
    int32_t i = 0;
    while (input[i])
    {
        if (input[i] == d->sol[i])
        {
            ft_putstr_fd(GREEN, 1);
            write(1, (&input[i]-32), 1);
            ft_putstr_fd(RESET, 1);
        }
        else if (ft_strchr(d->sol, input[i]))
        {
            ft_putstr_fd(YELLOW, 1);
            write(1, (&input[i]-32), 1);
            ft_putstr_fd(RESET, 1);
        }
        else
            write(1,(&input[i]-32), 1);
        if (i < 5)
            write(1, " ", 1);
        i++;
    }
}

void    ft_save_input(t_data *d, char *input)
{
    d->guess += 1;
    ft_putstr_fd(char *s, int fd)
    
}

void ft_get_guess(t_data *d)
{
    char *input;

    while (true)
    {
        ft_putstr_fd("Guess: ", 1);
        input = get_next_line(1);
        if (!ft_strncmp(input, d->sol, 5))
        {
            ft_save_input(d, input);
            break;
        }
        if (ft_check_input(d, input))
            ft_save_input(d, input);
        else
            ft_putstr_fd("Not Valid!\n", 1);
        free(input);
        input = NULL;
    }
}

void ft_game_loop(t_data *d)
{
    int i;
    char *input;
    //ft_putstr_fd(GREEN, 1);
    ft_putstr_fd("Welcome to Wordle\n", 1);
    while (true)
    {
        i = 6;
        ft_putstr_fd("Type New(n) or Exit(e)\n", 1);
        input = get_next_line(1);
        ft_get_guess(d);
        
        while (i--)
        {
            ft_putstr_fd("_ _ _ _ _\n", 1);
        }
    }
}

int main(void)
{
    t_data *d = malloc(sizeof(t_data));
    if (!d)
        return (printf("Error: Bad alloc"), 0);
    d->size = 0;
    ft_create_w_list(d);
    ft_print_slst(d->list);
    printf("%lu\n", d->size);
    ft_init_data(d);
    ft_game_loop(d);
    return (0);
}
