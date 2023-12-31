
#include "wordle.h"

void	ft_clean_exit(t_data *d, char *err, int error)
{
	t_slist	*tmp;

	if (d)
	{
		if (d->list)
		{
			while (d->list)
			{
				tmp = d->list;
				d->list = d->list->next;
				if (tmp->str)
					free(tmp->str);
				free(tmp);
			}
			free(d->list);
		}
		if (d->sol)
			free(d->sol);
		free(d);
	}
	ft_putstr_fd(err, 2);
	exit(error);
}

bool	ft_check_yellow(t_data *d, char *input, int i)
{
	int16_t	check;

	if (!ft_strchr(d->sol, input[i]))
		return (false);
	check = d->table[((int)d->sol[i]) - 'a'];
	for (int j = 0; j < i; j++)
	{
		for (int k = 0; k < i; k++)
		{
			if (input[j] == d->sol[k] && check > 0)
			{
				check--;
				break;
			}
		}
	}
	for (int j = i + 1; j < 5; j++)
	{
		if (input[i] == d->sol[j] && input[j] == d->sol[j] && check > 0)
			check--;
	}
	if (check > 0)
		return (true);
	return (false);
}

char	*ft_list_data_i(t_slist *l, int32_t nb)
{
	t_slist	*tmp;

	tmp = l;
	while (--nb > 0)
		tmp = tmp->next;
	return (tmp->str);
}

void	ft_init_data(t_data *d)
{
	srand(time(NULL));
	d->nb = rand() % d->size;
	if (d->sol)
		free(d->sol);
	d->sol = ft_strdup((const char *)ft_list_data_i(d->list, d->nb));
	if (!d->sol)
		ft_clean_exit(d, "Error: Bad alloc", 1);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
			d->matrix[i][j] = '_';
	}
	for (int i = 0; i < 26; i++)
		d->table[i] = 0;
	for (int i = 0; i < 5; i++)
		d->table[((int)d->sol[i]) - 'a'] += 1;
	d->guess = 0;
}

void	ft_string_normalize(char *input)
{
	for (uint16_t i = 0; i < 5; i++)
	{
		if (input[i] >= 'A' && input[i] <= 'Z')
			input[i] += 32;
	}
}

bool	ft_check_input(t_data *d, char *input)
{
	t_slist	*tmp;

	if (ft_strlen(input) != 6)
		return (false);
	ft_string_normalize(input);
	for (uint16_t i = 0; i < 5; i++)
	{
		if (input[i] < 'a' || input[i] > 'z')
			return (false);
	}
	tmp = d->list;
	while (tmp != NULL)
	{
		if (tmp->str && !ft_strncmp(input, tmp->str, 5))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	ft_print_input(t_data *d, char *input)
{
	int32_t	i;
	char	c;

	i = 0;
	while (i < 5)
	{
		if (input[i] == '_')
			write(1, &input[i], 1);
		else if (input[i] == d->sol[i])
		{
			ft_putstr_fd(GREEN, 1);
			c = input[i] - 32;
			write(1, &c, 1);
			ft_putstr_fd(RESET, 1);
		}
		else if (ft_check_yellow(d, input, i))
		{
			ft_putstr_fd(YELLOW, 1);
			c = input[i] - 32;
			write(1, &c, 1);
			ft_putstr_fd(RESET, 1);
		}
		else
		{
			c = input[i] - 32;
			write(1, &c, 1);
		}
		if (i < 5)
			write(1, " ", 1);
		i++;
	}
}

void	ft_save_input(t_data *d, char *input)
{
	for (int i = 0; i < 5; i++)
		d->matrix[d->guess][i] = input[i];
	d->guess += 1;
	for (int i = 0; i < 6; i++)
	{
		ft_print_input(d, d->matrix[i]);
		write(1, "\n", 1);
	}
}

void	ft_get_guess(t_data *d)
{
	char	*input;

	while (true)
	{
		ft_putstr_fd("Guess: ", 1);
		input = get_next_line(1);
		if (input == NULL)
			ft_clean_exit(d, "Bye!\n", 0);
		if (ft_check_input(d, input))
		{
			ft_save_input(d, input);
			if (!ft_strncmp(input, d->sol, 5))
			{
				ft_putstr_fd(GREEN, 1);
				ft_putstr_fd("You won!\n", 1);
				ft_putstr_fd(RESET, 1);
				break ;
			}
			else if (d->guess == 6)
			{
				ft_putstr_fd(RED, 1);
				ft_putstr_fd("You lost!\n", 1);
				ft_putstr_fd(RESET, 1);
				break ;
			}
		}
		else
			ft_putstr_fd("Not Valid!\n", 1);
		free(input);
		input = NULL;
	}
	if (input)
		free(input);
}

void	ft_new_or_exit(t_data *d)
{
	char	*input;

	while (true)
	{
		ft_putstr_fd("Type New(n) or Exit(e)\n", 1);
		input = get_next_line(1);
		if (input == NULL)
			ft_clean_exit(d, "Bye!\n", 0);
		if (!ft_strncmp(input, "n", 1))
		{
			ft_init_data(d);
			ft_putstr_fd(d->sol, 1);
			free(input);
			break ;
		}
		else if (!ft_strncmp(input, "e", 1))
		{
			free(input);
			ft_clean_exit(d, "Bye!\n", 0);
		}
		else
			ft_putstr_fd("Not Valid!\n", 1);
		free(input);
		input = NULL;
	}
}

void	ft_game_loop(t_data *d)
{
	ft_putstr_fd(GREEN, 1);
	ft_putstr_fd("Welcome to Wordle\n", 1);
	ft_putstr_fd(RESET, 1);
	while (true)
	{
		ft_new_or_exit(d);
		ft_get_guess(d);
	}
}

int	main(void)
{
	t_data	*d;

	d = malloc(sizeof(t_data));
	if (!d)
		return (printf("Error: Bad alloc"), 0);
	d->size = 0;
	d->sol = NULL;
	ft_create_w_list(d);
	ft_init_data(d);
	ft_game_loop(d);
	ft_clean_exit(d, "Bye!\n", 0);
	return (0);
}
