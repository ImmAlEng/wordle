
#include "wordle.h"

void    ft_create_w_list(t_data *d)
{
    t_slist *new;
    char *buffer;
    int32_t fd;

    d->list = NULL;
    if (access("wordlist.txt", R_OK) == -1)
        ft_clean_exit(d, "Can not create List!\n", 1);
    fd = open("wordlist.txt", O_RDONLY);
    if (fd == -1) 
        ft_clean_exit(d, "Can not create List!\n", 1);
    while (true)
    {
        buffer = get_next_line(fd);
        if (!buffer)
        {
			break;
        }
        if (!buffer)
            ft_clean_exit(d, "Can not create List!\n", 1);
        new = ft_slstnew(buffer);
        if (!new)
            ft_clean_exit(d, "Can not create List!\n", 1);
        ft_slstadd_back(&d->list, new);
        buffer = NULL;
        d->size += 1;
    }
}

/*
	This function takes a string and returns a new node for a singly-linked list,
	containing a trimmed copy of the string.
*/

t_slist	*ft_slstnew(char *str)
{
	t_slist	*new;

	new = malloc(sizeof(t_slist));
	if (!new)
		return (NULL);
	new->str = ft_strtrim(str, " \n");
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
    free(str);
	new->next = NULL;
	return (new);
}

/*
	This function takes a pointer to a pointer to a singly-linked 
	list and a new node to be added to the list. 
	It adds the new node to the end of the list and returns 0 on success,
	or an error code on failure.
*/

int	ft_slstadd_back(t_slist **lst, t_slist *new_l)
{
	t_slist	*last;

	if (!lst)
		return (0);
	if (!*lst)
	{
		*lst = new_l;
		return (1);
	}
	last = ft_listlast(*lst);
	last->next = new_l;
	return (1);
}

/*
	This function prints the strings stored in a singly-linked list,
	separated by newlines. 
	It takes a pointer to the first node in the list.
*/

void	ft_print_slst(t_slist *lst)
{
	while (lst)
	{
		if (lst->str)
			ft_putstr_fd(lst->str, 1);
		ft_putstr_fd("\n", 1);
		lst = lst->next;
	}
}

/*
	This function takes the first node of a singly-linked list 
	and returns the last node.
*/

t_slist	*ft_listlast(t_slist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
